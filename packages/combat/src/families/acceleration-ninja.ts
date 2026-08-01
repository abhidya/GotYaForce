// ACCELERATION NINJA (pl0004, ctor 0x80162128) acceleration-ninja family — bespoke port.
//
// A movement/contact-gated melee + dash family. The ctor wires FUN_80162418 as the
// family rootAction (+0x4b4 virtual) → PTR_FUN_8034c72c[+0x580] (actionIndex). Three
// actions route to bespoke phase tables (each indexed by +0x540 = fbPhaseSlots[0]):
//
//   action 0 @0x8034c750 = [FUN_801624d8, FUN_80162598, FUN_80162638]  (3 phases;
//              work-queue overread 8 — the next object @0x8034c75c is action-2's
//              variantIndex table, NOT action-0 phases. 0x8034c75c − 0x8034c750 = 0xc
//              = 3 pointers. Confirmed by decomp: ph2 never increments +0x540.)
//   action 2 @0x8034c770 = [FUN_80162804, zz_01628d4_, FUN_80162ae4]   (3 phases)
//   action 3 @0x8034c7a8 = [FUN_80162c6c, FUN_80162d40, FUN_80162e9c]  (3 phases)
//
// Sub-router shape:
//   action 0 → FUN_8016249c → phase table directly.
//   action 2 → FUN_80162780 (+0x18dc >>= 1 per frame) → variant table @0x8034c75c
//              [+0x581] → (variant 0) FUN_801627c8 → phase table @0x8034c770. Only
//              pl0004 is registered, so variantIndex is always 0; the variant layer
//              is collapsed here (the per-frame +0x18dc decay is preserved).
//   action 3 → FUN_80162bf4 → variant table @0x8034c794[+0x581] → (variant 0)
//              FUN_80162c30 → phase table @0x8034c7a8. Variant layer collapsed.
//
// Source: research/decomp/ghidra-export/chunk_0042.c:582-1025.
//
// This family is NOT an ammo-gated projectile family (unlike victory-jet/vehicle-borg).
// The phase machine contains NO zz_006dbe0_ calls — transitions are governed by the
// part-0 contact flag (+0x1cef), the wall-contact flag (+0x1cee), status-word bits
// (+0x5bc & 0x100/0x400), and handler-local timers. The only ammo gate in the family
// is FUN_801623c0 (chunk_0042.c:565) — the likely B-charge indirect callback (+0x4d8),
// NOT a phase-table entry; it is surfaced below as accelerationNinjaChargeArm. Effect
// "spawns" are zz_0099e70_(actor, byte) triggers (action-3 dash FX 0x23/0x24; charge
// cues 0x21/0x22), routed through ctx.onFamilyProjectile for observability.
//
// HONEST PARTIAL: the phase transitions, timer seeds, contact/status gates, stream
// (de)arms, sound cues, and effect triggers are ported 1:1. The following are host-
// renderer / unsurfaced deps, marked TODO and left as no-ops (faithful behavior with
// no host bound):
//   FUN_80067310  — scalar-speed physics integrator (actor.ts describes; not callable)
//   zz_00677b0_   — step-height ground snap; its int return is modelled via the
//                   scratch flag grounded77b0 (host sets; defaults false)
//   zz_006d144_   — lock-yaw rebuild from +0x5ac (distinct from helpers' stepTargetYaw)
//   zz_0066ac0_ / zz_0066e40_ / zz_006ed8c_ — aim helpers
//   zz_00b2544_ / zz_00f0104_ / zz_00b2190_ / FUN_800061a8 — trail / afterimage-arm
//   gnt4_PSVEC* / PSMTX* / PSQUAT* — renderer vector math
//   zz_006a5a4_ / zz_006a474_ / zz_0069210_ / zz_0069038_ — post-exit state redirects
//        (the inline +0x73f=0 / +0x5e0&=~3 / +0x694 seed BEFORE these IS ported)
//
// Float constants read from boot.dol (sdata2 @0x8043a8xx), cited per constant.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { allocateWeapon, stepAfterimage, stepPartTargetPitch, toS16 } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Borg number for ACCELERATION NINJA (the only registered member). */
const ACCELERATION_NINJA_BORG_NUMBER = 0x004;

// ----------------------------------------------------------------------------
// Spawner / effect-trigger addresses.
// ----------------------------------------------------------------------------
/** zz_0099e70_ @0x80099e70 — shared-engine effect/event trigger (dash FX + charge
 *  cues). Not a record-table projectile spawner; routed through onFamilyProjectile
 *  for observability (no dedicated effect hook exists on StreamContext). */
const EFFECT_TRIGGER = 0x80099e70;

// ----------------------------------------------------------------------------
// Float constants (DOL-read this session; sdata2 @0x8043a8xx). The DOUBLE_ values
// 8043a8e0 / 8043a8f8 are read as 8-byte doubles (see decomp CONCAT pattern).
// ----------------------------------------------------------------------------
const AN = {
  /** FLOAT_8043a8cc = 0.0 — universal zero (speed/timer reset, thresholds). */
  ZERO: 0.0,
  /** FLOAT_8043a8d0 = 1.0 — FUN_80067310 physics rate; exit stateTimer base (a0/a3). */
  PHYSICS_RATE: 1.0,
  /** FLOAT_8043a8d4 = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a8d8 = 0.9 — a0 ph2 +0x18da yaw-magnitude decay factor. */
  A0_YAW_DECAY: 0.8999999761581421,
  /** FLOAT_8043a8dc = 0.97 — zz_006ed8c_ aim rate (a0 ph2). */
  A0_AIM_RATE: 0.9700000286102295,
  /** FLOAT_8043a8e8 = 3600.0 — a2 ph0 +0x558 main-timer seed (the dash cap). */
  A2_MAIN_TIMER: 3600.0,
  /** FLOAT_8043a8ec = 20.0 — a2 ph0 +0x55c cooldown seed. */
  A2_COOLDOWN: 20.0,
  /** FLOAT_8043a8f0 = 3.0 — a2 ph0 +0x38 speed scale (× descriptor maxHSpeed); also
   *  the a2 ph1 "slow enough" threshold and a3 trail-speed gate. */
  A2_SPEED_SCALE: 3.0,
  /** DOUBLE_8043a8f8 = 0.5 — a2 ph1 distance-gate scale (+0x5f8 × 0.5 × +0x44 × +0x5f4). */
  A2_DIST_SCALE: 0.5,
  /** FLOAT_8043a900 = 10.0 — a2 ph1 +0x560 approach-timer cap; a3 ph0 +0x48 yVel seed. */
  A2_APPROACH_CAP: 10.0,
  /** FLOAT_8043a904 = 8.0 — a2 exit +0x694 stateTimer seed. */
  EXIT_STATE_TIMER: 8.0,
  /** FLOAT_8043a908 = 0.95 — PSQUATScale factor + zz_006ed8c_ rate (a3). */
  A3_QUAT_SCALE: 0.949999988079071,
  /** FLOAT_8043a90c = 4.0 — a3 ph0 +0x558 seed; ph1 re-seed; ph2 exit +0x694 seed. */
  A3_MAIN_TIMER: 4.0,
  /** FLOAT_8043a910 = 12483.0 — a3 ph1 +0x18dc per-frame turn rate. */
  A3_TURN_RATE: 12483.0,
  /** FLOAT_8043a914 = 180.0 — a3 ph1→ph2 +0x558 seed. */
  A3_PH2_TIMER: 180.0,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface AccelerationNinjaScratch {
  /** +0x54a (short): overloaded — a0 ph0 stashes +0x5ae (lockYaw) here as the steer
   *  yaw; a3 ph0 seeds it to 5 and decrements per shot cycle. */
  ninjaScratch54a?: number;
  /** +0x746 (byte): stream/input flag latch (set 1 when +0x1d9 != 0). */
  ninjaStreamFlag746?: number;
  /** +0x18da (short): a0 ph2 yaw accumulator (decays × 0.9 per frame). */
  ninjaYaw18da?: number;
  /** +0x18dc (short): a2/a3 turn accumulator (a2 sub-router decays >>1 per frame). */
  ninjaTurn18dc?: number;
  /** +0x1d9 (byte): stream/input flag polled by a0 ph1/ph2 (host-set). */
  ninjaFlag1d9?: number;
  /** +0x1d0f (signed byte): stream-authored dash-strength byte (host-set). */
  dashStrength1d0f?: number;
  /** +0x38 (float, first slot of the motion vec3): a2 hSpeed stash (3.0 × maxHSpeed). */
  ninjaSpeed38?: number;
  /** +0x55c (float): handler-local cooldown timer (a2 ph0 seeds 20.0). */
  ninjaCooldown55c?: number;
  /** +0x560 (float): handler-local approach timer (a2 ph1; advances ph2 when > cap). */
  ninjaApproach560?: number;
  /** +0x5bc (uint): live status word; bits 0x100/0x400 gate a2 ph1 exit branches. */
  statusWord5bc?: number;
  /** Models the int return of zz_00677b0_ (step-height ground snap). Host sets true
   *  when the actor is grounded/colliding this frame; defaults false. */
  grounded77b0?: boolean;
}

type NinjaActor = RomActor & AccelerationNinjaScratch;

function scratchOf(actor: RomActor): NinjaActor {
  return actor as NinjaActor;
}

// ----------------------------------------------------------------------------
// Shared exit fragments. The ROM clears +0x73f / strips +0x5e0 action bits inline,
// THEN calls a state-redirect helper (zz_006a5a4_ / zz_006a474_ / zz_0069210_ /
// zz_0069038_) or the upper-body cue (zz_006a750_). The inline clears + stateTimer
// seeds are ported exactly; the redirect helpers are unsurfaced (TODO, no-op).
// ----------------------------------------------------------------------------

/** ph2 exit via zz_006a5a4_(actor) — clear housekeeping, strip action bits. The
 *  redirect itself (zz_006a5a4_ @ host state layer) is deferred. */
function exitClearActionMode(actor: NinjaActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  // TODO(host): zz_006a5a4_(actor) — post-exit state redirect (idle/land).
}

// ============================================================================
// Action 0 — dash strike (table @0x8034c750, 3 phases).
//   ph0 FUN_801624d8 (chunk_0042.c:616): setup — +0x540++; zero speeds (variant 0),
//        copy +0x5ae→+0x54a, aim, integrate, ground, startStream(0xf, g2, s0).
//   ph1 FUN_80162598 (:643): per-frame — aim, integrate, ground, tickStream(0xf);
//        on part-0 contact (+0x1cef != 0) +0x540++ and copy gravity.
//   ph2 FUN_80162638 (:665): strike/exit — +0x18da decays ×0.9; on grounded AND
//        negative contact → clear + dispatchUpperBodyCue(7) + +0x694 = 1.0 + dt;
//        else on contact-or-input (wall==0) → clear speeds + exitClearActionMode.
// ============================================================================
function action0(actor: NinjaActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_801624d8 — setup
      actor.fbPhaseSlots[0] = 1;                              // +0x540++
      if (actor.variantIndex === 0) {
        actor.hDecel = AN.ZERO;                               // +0x4c = 0.0
        actor.hSpeed = AN.ZERO;                               // +0x44 = 0.0
        actor.yVel = AN.ZERO;                                 // +0x48 = 0.0
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff; // +0x50 = desc+0x6c
      }
      actor.ninjaScratch54a = actor.lockYaw;                  // +0x54a = +0x5ae
      actor.ninjaStreamFlag746 = 0;                           // +0x746 = 0
      // zz_006d144_(actor, 0xc1) — lock-yaw rebuild; TODO(host) aim.
      stepPartTargetPitch(actor, 0xc1);                       // zz_006e1ac_(actor, 0xc1, 1)
      // FUN_80067310(1.0, actor, +0x54a) — TODO(host) physics integrator.
      // zz_00677b0_(actor) — TODO(host) ground snap.
      startStream(actor, 0xf, 2, 0, AN.STREAM_RATE);          // zz_004beb8_(-1, actor, 0xf, 2, 0)
      return;
    }
    case 1: { // FUN_80162598 — approach / contact wait
      if ((actor.ninjaFlag1d9 ?? 0) !== 0) actor.ninjaStreamFlag746 = 1;
      // zz_006d144_(actor, 0xc1) — TODO(host) aim.
      stepPartTargetPitch(actor, 0xc1);                       // zz_006e1ac_(actor, 0xc1, 1)
      // FUN_80067310(1.0, actor, +0x54a) — TODO.
      // zz_00677b0_(actor) — TODO.
      tickStream(actor, 0xf, ctx);                            // zz_004cd24_(actor, 0xf)
      if (actor.contactP0 !== 0) {                            // +0x1cef != 0
        actor.fbPhaseSlots[0] = 2;                            // +0x540++
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff; // +0x50 = desc+0x6c
      }
      return;
    }
    case 2: { // FUN_80162638 — strike + exit
      if ((actor.ninjaFlag1d9 ?? 0) !== 0) actor.ninjaStreamFlag746 = 1;
      // +0x18da = (short)(|+0x18da| × 0.9)  (the CONCAT44 pattern is int→double→fabs)
      const cur18da = toS16(actor.ninjaYaw18da ?? 0);
      actor.ninjaYaw18da = toS16(Math.trunc(Math.abs(cur18da) * AN.A0_YAW_DECAY));
      tickStream(actor, 0xf, ctx);                            // zz_004cd24_(actor, 0xf)
      // zz_006ed8c_(0.97, actor) — TODO(host) aim helper.
      // FUN_80067310(1.0, actor, +0x54a) — TODO.
      const grounded = actor.grounded77b0 ?? false;           // iVar2 = zz_00677b0_(actor)
      if (grounded && actor.contactP0 < 0) {                  // collision AND +0x1cef < 0
        actor.ninjaYaw18da = 0;                               // +0x18da = 0
        actor.housekeeping73f = 0;                            // +0x73f = 0
        actor.controlWord = actor.controlWord & ~0x3;         // +0x5e0 &= ~3
        dispatchUpperBodyCue(actor, 7);                       // zz_006a750_(actor, 7)
        actor.stateTimer = AN.PHYSICS_RATE + actor.dt;        // +0x694 = 1.0 + dt (FLOAT_8043a8d0)
        return;                                               // EXIT (upper-body)
      }
      // Advance gate: (no positive contact AND no stream flag) OR no direction input,
      // AND no wall contact → not yet, stay in ph2.
      const noPosContact = actor.contactP0 >= 0 && (actor.ninjaStreamFlag746 ?? 0) === 0;
      const noDirection = (actor.inputHeld5d8 & 0xf0) === 0;
      if (((noPosContact) || noDirection) && actor.wallContact === 0) {
        return;
      }
      actor.hDecel = AN.ZERO;                                 // +0x4c = 0.0
      actor.hSpeed = AN.ZERO;                                 // +0x44 = 0.0
      exitClearActionMode(actor);                             // +0x73f=0; +0x5e0&=~3; zz_006a5a4_
      return;                                                 // EXIT
    }
    default: return;
  }
}

// ============================================================================
// Action 2 — dash lunge (table @0x8034c770, 3 phases).
//   ph0 FUN_80162804 (:730): setup — +0x540++; +0x558=3600, +0x55c=20, +0x560=0;
//        +0x38 = 3.0 × desc maxHSpeed; zero speeds; +0x6ea 0→1;
//        startStream(0xf, g4, s0); afterimage arm; then inline zz_01628d4_ (one frame).
//   ph1 zz_01628d4_ (:769): approach solver — distance/timer gate; on gate fail
//        (close OR approach>cap) → +0x540++ + startStream(0xf, g4, slot=+0x6ea).
//        Within dash: drain +0x55c then +0x558; status bits 0x400/0x100 exit; main
//        timer expire → +0x540++.
//   ph2 FUN_80162ae4 (:847): recovery — tickStream; on wall contact (+0x1cee != 0)
//        clear + exit (+0x694 = 8.0 + dt); else trail while fast (vector-math TODO).
// ============================================================================
function action2(actor: NinjaActor, ctx: StreamContext): void {
  // Sub-router FUN_80162780: +0x18dc >>= 1 each frame before the phase dispatch.
  actor.ninjaTurn18dc = toS16(actor.ninjaTurn18dc ?? 0) >> 1;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80162804 — setup
      actor.fbPhaseSlots[0] = 1;                              // +0x540++
      actor.handlerTimer = AN.A2_MAIN_TIMER;                  // +0x558 = 3600 (FLOAT_8043a8e8)
      actor.ninjaCooldown55c = AN.A2_COOLDOWN;                // +0x55c = 20 (FLOAT_8043a8ec)
      actor.ninjaApproach560 = AN.ZERO;                       // +0x560 = 0
      actor.ninjaSpeed38 = AN.A2_SPEED_SCALE * (actor.descriptor?.maxHSpeed ?? 0); // +0x38 = 3.0 × desc+0x2c
      actor.hSpeed = AN.ZERO;                                 // +0x44 = 0.0
      actor.hDecel = AN.ZERO;                                 // +0x4c = 0.0
      actor.yVel = AN.ZERO;                                   // +0x48 = 0.0
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff; // +0x50 = desc+0x6c
      actor.streamSlot = 0;                                   // +0x6ea = 0
      const slot = actor.streamSlot;                          // cVar1 = +0x6ea (0)
      actor.streamSlot = slot + 1;                            // +0x6ea = 1
      startStream(actor, 0xf, 4, slot, AN.STREAM_RATE);       // zz_004beb8_(-1, actor, 0xf, 4, 0)
      actor.accumulator80c = AN.ZERO;                         // +0x80c = 0.0
      // zz_00b2190_(actor, 0) — afterimage-arm; TODO(host). accumulator reset above.
      // FUN_800061a8(actor, 0x10) — TODO(host).
      action2Phase1(actor, ctx);                              // inline zz_01628d4_ (one frame)
      return;
    }
    case 1: { // zz_01628d4_ — approach solver
      action2Phase1(actor, ctx);
      return;
    }
    case 2: { // FUN_80162ae4 — recovery / wall-contact exit
      tickStream(actor, 0xf, ctx);                            // zz_004cd24_(actor, 0xf)
      if ((actor.dashStrength1d0f ?? 0) > 0) {                // +0x1d0f > 0
        actor.dashStrength1d0f = 0;                           // +0x1d0f = 0
        actor.hDecel = AN.ZERO;                               // +0x4c = 0.0
        actor.hSpeed = AN.ZERO;                               // +0x44 = 0.0
      }
      // zz_006ed8c_(0.95, actor) — TODO(host) aim.
      // FUN_80067310(1.0, actor, +0x5ae) — TODO.
      if (actor.wallContact === 0) {                          // +0x1cee == 0
        if (AN.A2_SPEED_SCALE < actor.hSpeed) {               // 3.0 < +0x44 (still fast)
          // gnt4_PSMTXMultVec(+0x8d4, &DAT_8034c77c/_788, ...) + zz_00b2544_(actor, a, b)
          // — trail spawn; TODO(host) renderer vector math.
        }
      } else {                                                // wall contact → exit
        actor.housekeeping73f = 0;                            // +0x73f = 0
        actor.controlWord = actor.controlWord & ~0x3;         // +0x5e0 &= ~3
        const grounded = actor.grounded77b0 ?? false;         // iVar = zz_00677b0_(actor)
        if (!grounded) {
          // zz_006a5a4_(actor) — TODO(host) state redirect.
        } else {
          // zz_006a474_(actor) — TODO(host) state redirect.
        }
        actor.stateTimer = AN.EXIT_STATE_TIMER + actor.dt;    // +0x694 = 8.0 + dt (FLOAT_8043a904)
      }
      return;
    }
    default: return;
  }
}

/** zz_01628d4_ — action-2 phase-1 approach solver (also called inline from ph0). */
function action2Phase1(actor: NinjaActor, ctx: StreamContext): void {
  // gnt4_PSVECSubtract(+0x20, +0x5e8, delta) + PSVECMag — distance to cached target.
  const dx = actor.pos.x - actor.targetCache5e8.x;
  const dy = actor.pos.y - actor.targetCache5e8.y;
  const dz = actor.pos.z - actor.targetCache5e8.z;
  const distance = Math.hypot(dx, dy, dz);
  // Outer gate: (threshold <= distance) || (approach += dt; approach <= 10.0).
  const threshold =
    actor.tierScale * AN.A2_DIST_SCALE * actor.hSpeed * actor.timescale;
  const farEnough = threshold <= distance;
  let approach;
  let gate;
  if (farEnough) {
    approach = actor.ninjaApproach560 ?? 0;                   // B short-circuited (no += dt)
    gate = true;
  } else {
    approach = (actor.ninjaApproach560 ?? 0) + actor.dt;      // +0x560 += dt
    actor.ninjaApproach560 = approach;
    gate = approach <= AN.A2_APPROACH_CAP;                    // <= 10.0
  }
  // PTR_DAT_80433934[0x1f] global flag — treated as 0 (cleared) on the host.
  if (gate) {
    // Dash body.
    tickStream(actor, 0xf, ctx);                              // zz_004cd24_(actor, 0xf)
    // zz_0066ac0_(actor, 0) / zz_0066e40_(actor, 2) — TODO(host) aim.
    actor.lockYaw = actor.heading;                            // +0x5ae = +0x72
    actor.hSpeed = actor.ninjaSpeed38 ?? 0;                   // +0x44 = +0x38
    // FUN_80067310(1.0, actor, +0x5ae) — TODO.
    const grounded = actor.grounded77b0 ?? false;             // iVar4 = zz_00677b0_(actor)
    if (grounded) actor.yVel = AN.ZERO;                       // +0x48 = 0.0
    if (AN.ZERO < (actor.ninjaCooldown55c ?? 0)) {            // 0.0 < +0x55c
      actor.ninjaCooldown55c = (actor.ninjaCooldown55c ?? 0) - actor.dt; // +0x55c -= dt
    }
    if ((actor.ninjaCooldown55c ?? 0) <= AN.ZERO) {           // +0x55c <= 0.0
      if (((actor.statusWord5bc ?? 0) & 0x400) !== 0) {
        advanceAction2ToPhase2(actor);                        // goto LAB_80162a6c
        return;
      }
      if (((actor.statusWord5bc ?? 0) & 0x100) !== 0) {
        actor.housekeeping73f = 0;                            // +0x73f = 0
        actor.controlWord = actor.controlWord & ~0x3;         // +0x5e0 &= ~3
        actor.stateTimer = AN.EXIT_STATE_TIMER + actor.dt;    // +0x694 = 8.0 + dt
        // iVar4 = grounded ? zz_0069038_ : zz_0069210_ — TODO(host) state redirect.
        return;                                               // EXIT (status-gated)
      }
    }
    const mainRem = actor.handlerTimer - actor.dt;            // fVar3 = +0x558 - dt
    actor.handlerTimer = mainRem;                             // +0x558 -= dt
    if (AN.ZERO < mainRem) {                                  // 0.0 < +0x558
      if (actor.hSpeed <= AN.A2_SPEED_SCALE) return;          // +0x44 <= 3.0 → too slow, wait
      stepAfterimage(actor);                                  // zz_00b22f4_(actor)
      // zz_00f0104_(actor, 0x18, 2) — TODO(host) trail/sound.
      return;
    }
    // main timer expired → fall through to advance.
  }
  advanceAction2ToPhase2(actor);                              // LAB_80162a6c
}

/** LAB_80162a6c — advance action 2 from ph1 to ph2 + arm next stream slot. */
function advanceAction2ToPhase2(actor: NinjaActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;   // +0x540++
  const slot = actor.streamSlot;                              // cVar1 = +0x6ea
  actor.streamSlot = slot + 1;                                // +0x6ea = cVar1 + 1
  startStream(actor, 0xf, 4, slot, AN.STREAM_RATE);           // zz_004beb8_(-1, actor, 0xf, 4, slot)
}

// ============================================================================
// Action 3 — hover dash strike (table @0x8034c7a8, 3 phases).
//   ph0 FUN_80162c6c (:912): setup — +0x540++; +0x558=4, +0x54a=5; zero speeds
//        (+0x48=10 unless position-frozen); position lerp toward +0x5e8; ground;
//        startStream(0xf, g2, s1).
//   ph1 FUN_80162d40 (:946): hover — tickStream; if contactP0 >= 1 decay turn +
//        drain +0x558, on expire re-seed 4 + cue 10 + decrement +0x54a + FX
//        0x23/0x24 (while +0x54a > 0); on contactP0 < 0 → +0x540++ + +0x558=180.
//   ph2 FUN_80162e9c (:995): exit — tickStream; if (not grounded OR no neg contact)
//        drain +0x558, on <= 0 clear + exit (+0x694 = 4.0 + dt); else clear +
//        dispatchUpperBodyCue(7) + +0x694 = 1.0 + dt.
// ============================================================================
function action3(actor: NinjaActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80162c6c — setup
      actor.fbPhaseSlots[0] = 1;                              // +0x540++
      actor.handlerTimer = AN.A3_MAIN_TIMER;                  // +0x558 = 4 (FLOAT_8043a90c)
      actor.ninjaScratch54a = 5;                              // +0x54a = 5
      actor.gravityCoeff = AN.ZERO;                           // +0x50 = 0.0
      actor.yVel = AN.ZERO;                                   // +0x48 = 0.0
      actor.hDecel = AN.ZERO;                                 // +0x4c = 0.0
      actor.hSpeed = AN.ZERO;                                 // +0x44 = 0.0
      actor.poseAccum80 = 0;                                  // +0x80 = 0
      actor.poseAccum7e = 0;                                  // +0x7e = 0
      actor.poseAccum7c = 0;                                  // +0x7c = 0
      if ((actor.controlWord & 0x40) === 0) {                 // not position-frozen
        actor.yVel = AN.A2_APPROACH_CAP;                      // +0x48 = 10.0 (FLOAT_8043a900)
      }
      // gnt4_PSVECSubtract(+0x20, +0x5e8, +0x38) + PSQUATScale(0.95) + PSVECAdd →
      // position lerp toward cached target; TODO(host) renderer vector math.
      // zz_00677b0_(actor) — TODO(host) ground snap.
      startStream(actor, 0xf, 2, 1, AN.STREAM_RATE);          // zz_004beb8_(-1, actor, 0xf, 2, 1)
      return;
    }
    case 1: { // FUN_80162d40 — hover + strike window
      tickStream(actor, 0xf, ctx);                            // zz_004cd24_(actor, 0xf)
      if (actor.contactP0 < 1) {                              // +0x1cef < 1
        actor.ninjaTurn18dc = 0;                              // +0x18dc = 0
      } else {                                                // +0x1cef >= 1
        // +0x18dc = -(12483 × dt − |+0x18dc|)  (the CONCAT pattern resolves to fabs)
        const decayed = -(AN.A3_TURN_RATE * actor.dt - Math.abs(toS16(actor.ninjaTurn18dc ?? 0)));
        actor.ninjaTurn18dc = toS16(decayed);
        const mainRem = actor.handlerTimer - actor.dt;        // fVar1 = +0x558 - dt
        actor.handlerTimer = mainRem;                         // +0x558 -= dt
        if (mainRem <= AN.ZERO) {                             // +0x558 <= 0.0
          actor.handlerTimer = AN.A3_MAIN_TIMER;              // +0x558 = 4 (FLOAT_8043a90c)
          ctx.onPlayCue?.(actor, 10);                         // zz_00f036c_(actor, 10)
          if ((actor.ninjaScratch54a ?? 0) > 0) {             // 0 < +0x54a
            actor.ninjaScratch54a = (actor.ninjaScratch54a ?? 0) - 1; // +0x54a--
            ctx.onFamilyProjectile?.(actor, EFFECT_TRIGGER, 0x23); // zz_0099e70_(actor, 0x23)
            ctx.onFamilyProjectile?.(actor, EFFECT_TRIGGER, 0x24); // zz_0099e70_(actor, 0x24)
          }
        }
      }
      if ((actor.dashStrength1d0f ?? 0) < 0) {                // +0x1d0f < 0
        actor.dashStrength1d0f = 0;                           // +0x1d0f = 0
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff; // +0x50 = desc+0x6c
      }
      // FUN_80067310(1.0, actor, +0x5ac) — TODO.
      // PSQUATScale(0.95, +0x38, +0x38) + PSVECAdd(+0x20, +0x38, +0x20) — TODO vector math.
      // zz_00677b0_(actor) — TODO.
      if (actor.contactP0 < 0) {                              // +0x1cef < 0 → advance
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.handlerTimer = AN.A3_PH2_TIMER;                 // +0x558 = 180 (FLOAT_8043a914)
      }
      return;
    }
    case 2: { // FUN_80162e9c — exit
      tickStream(actor, 0xf, ctx);                            // zz_004cd24_(actor, 0xf)
      // FUN_80067310(1.0, actor, +0x5ac) — TODO.
      const grounded = actor.grounded77b0 ?? false;           // iVar3 = zz_00677b0_(actor)
      if (!grounded || actor.contactP0 >= 0) {                // !grounded OR +0x1cef >= 0
        const mainRem = actor.handlerTimer - actor.dt;        // fVar1 = +0x558 - dt
        actor.handlerTimer = mainRem;                         // +0x558 -= dt
        if (mainRem <= AN.ZERO) {                             // +0x558 <= 0.0
          actor.housekeeping73f = 0;                          // +0x73f = 0
          actor.controlWord = actor.controlWord & ~0x3;       // +0x5e0 &= ~3
          // zz_006a5a4_(actor) — TODO(host) state redirect.
          actor.stateTimer = AN.A3_MAIN_TIMER + actor.dt;     // +0x694 = 4.0 + dt (FLOAT_8043a90c)
        }
      } else {                                                // grounded AND neg contact
        actor.housekeeping73f = 0;                            // +0x73f = 0
        actor.controlWord = actor.controlWord & ~0x3;         // +0x5e0 &= ~3
        dispatchUpperBodyCue(actor, 7);                       // zz_006a750_(actor, 7)
        actor.stateTimer = AN.PHYSICS_RATE + actor.dt;        // +0x694 = 1.0 + dt (FLOAT_8043a8d0)
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_80162418 indexes PTR_FUN_8034c72c[+0x580].
// ----------------------------------------------------------------------------
export function createAccelerationNinjaRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: action0(actor, ctx); return;
      case 2: action2(actor, ctx); return;
      case 3: action3(actor, ctx); return;
      default: return; // action 1 (and others) not surfaced in this port
    }
  };
}

/** Configure a freshly-spawned ACCELERATION NINJA (pl0004). Stamps the borg number
 *  and wires the bespoke 3-action root dispatcher. */
export function configureAccelerationNinjaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = ACCELERATION_NINJA_BORG_NUMBER;
  actor.rootAction = createAccelerationNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ----------------------------------------------------------------------------
// FUN_801623c0 (chunk_0042.c:565) — the family's only ammo gate. NOT a phase-table
//  entry; the likely B-charge indirect callback (+0x4d8). On weapon slot 0 available,
//  fires effect triggers 0x21 + 0x24. Surfaced for completeness; not wired by the
//  phase machine (its call site is in the unexported ctor / indirect table).
// ----------------------------------------------------------------------------
export function accelerationNinjaChargeArm(actor: RomActor, ctx: StreamContext): boolean {
  if (allocateWeapon(actor, ctx, 0, 1, true)) {               // zz_006dbe0_(actor, 0, 1, 1)
    ctx.onFamilyProjectile?.(actor, EFFECT_TRIGGER, 0x21);    // zz_0099e70_(actor, 0x21)
    ctx.onFamilyProjectile?.(actor, EFFECT_TRIGGER, 0x22);    // zz_0099e70_(actor, 0x22)
    return true;
  }
  return false;
}

export const ACCELERATION_NINJA_CONSTANTS = AN;
export const ACCELERATION_NINJA_EFFECT_TRIGGER = EFFECT_TRIGGER;
export type AccelerationNinjaCtx = StreamContext;

// ============================================================================
// Self-tests — mirrors rom.selfcheck.ts / vehicle-borg.ts style. Covers each
// action's phase transitions, contact/status gates, effect spawns (zz_0099e70_),
// the charge-arm ammo gate, and the no-op fallthrough. Note: this family has NO
// ammo gate inside the phase machine (movement/contact-gated, not projectile).
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runAccelerationNinjaSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // ------------------------------------------------------------------------
  console.log("[acceleration-ninja.selfcheck] ACTION 0 — dash strike (3-phase):");

  // --- a0 ph0: setup → ph1. Variant 0 zeroes speeds, copies lockYaw→+0x54a, arms stream(2,0). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    assert(a.borgNumber === 0x004, "pl0004 borgNumber stamped 0x004");
    assert(a.rootAction !== null, "acceleration-ninja bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.lockYaw = 0x1234; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "a0 ph0 advances +0x540 to ph1");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0, "a0 ph0 zeroes +0x44/+0x48/+0x4c (variant 0)");
    assert(a.ninjaScratch54a === 0x1234, "a0 ph0 copies +0x5ae→+0x54a");
    assert(a.ninjaStreamFlag746 === 0, "a0 ph0 clears +0x746");
    // NOTE: a0 ph0 does NOT inline ph1 (only a2 ph0 does), so no drain here.
  }

  // --- a0 ph1: no contact stays; contactP0 > 0 → ph2 + gravity copy. ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.descriptor = { handlerData6c: 7 } as never;
    root(a); // ph0 → ph1
    root(a); // ph1, no contact
    assert(a.fbPhaseSlots[0] === 1, "a0 ph1 stays at ph1 while contactP0 == 0");
    a.contactP0 = 1; // part-0 contact
    root(a); // ph1 → ph2
    assert(a.fbPhaseSlots[0] === 2, "a0 ph1 advances to ph2 on contactP0 != 0");
    assert(a.gravityCoeff === 7, "a0 ph1 copies desc+0x6c→+0x50 on contact");
  }

  // --- a0 ph2: grounded + negative contact → upper-body cue 7 exit (+0x694 = 1.0 + dt). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 2;
    a.grounded77b0 = true; a.contactP0 = -1; a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 upper-body exit
    assert(a.fbPhaseSlots[0] === 2, "a0 ph2 upper-body path does NOT advance +0x540");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "a0 ph2 clears +0x73f and strips +0x5e0 action bits");
    assert(a.stateTimer === AN.PHYSICS_RATE + 1, "a0 ph2 upper-body seeds +0x694 = 1.0 + dt (FLOAT_8043a8d0)");
  }

  // --- a0 ph2: gate false (positive contact + stream flag + direction input, wall==0)
  //     → clear speeds + exit (zz_006a5a4_ path). The ROM gate (line 693-696):
  //     ((contactP0>=0 && flag746==0) || inputDir==0) && wall==0 → stay. Negate to exit. ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 2;
    a.grounded77b0 = false; a.contactP0 = 1; a.ninjaStreamFlag746 = 1; // flag!=0 → noPosContact false
    a.inputHeld5d8 = 0x10; // direction held → noDirection false → gate false → exit
    a.hSpeed = 50;
    root(a); // ph2 contact exit
    assert(a.hSpeed === 0, "a0 ph2 clears +0x44 when gate is false (stream flag + direction input)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "a0 ph2 exit clears +0x73f and strips +0x5e0");
  }

  // ------------------------------------------------------------------------
  console.log("\n[acceleration-ninja.selfcheck] ACTION 2 — dash lunge (3-phase):");

  // --- a2 ph0: setup → seeds 3600/20/0, streamSlot 0→1, then inline ph1 (one frame). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.descriptor = { maxHSpeed: 10, handlerData6c: 5 } as never;
    a.tierScale = 1; a.timescale = 1;
    root(a); // ph0 (+ inline ph1 frame)
    // ph0 seeds 3600/20 then calls zz_01628d4_ inline, which drains both by one dt.
    assert(a.handlerTimer === AN.A2_MAIN_TIMER - a.dt, "a2 ph0 seeds +0x558 = 3600 (FLOAT_8043a8e8), drained one frame by inline zz_01628d4_");
    assert(a.ninjaCooldown55c === AN.A2_COOLDOWN - a.dt, "a2 ph0 seeds +0x55c = 20 (FLOAT_8043a8ec), drained one frame by inline zz_01628d4_");
    assert(a.ninjaApproach560 === 0, "a2 ph0 seeds +0x560 = 0");
    assert(a.ninjaSpeed38 === AN.A2_SPEED_SCALE * 10, "a2 ph0 seeds +0x38 = 3.0 × desc maxHSpeed");
    // ph0 sets streamSlot 0→1, then inline ph1 is the first dash frame.
    assert(a.fbPhaseSlots[0] === 1, "a2 ph0 advances +0x540 to ph1");
  }

  // --- a2 ph1: approach gate drains +0x560; close (distance 0 < threshold) → advance to ph2. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_x, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.descriptor = { maxHSpeed: 10, handlerData6c: 5 } as never;
    a.tierScale = 1; a.timescale = 1;
    root(a); // ph0 → ph1 (frame 1 of ph1: threshold 0, A true)
    // Frames 2..: threshold = tierScale*0.5*hSpeed*timescale. ph1 sets hSpeed = ninjaSpeed38 (30).
    // threshold = 1*0.5*30*1 = 15 > distance 0 → A false → approach += dt each frame.
    // approach starts 0; needs > 10 → 11 increments → advance on the 12th ph1 frame.
    for (let f = 0; f < 10; f += 1) root(a); // ph1 frames 2..11
    assert(a.fbPhaseSlots[0] === 1, "a2 ph1 stays at ph1 while approach <= 10");
    root(a); // ph1 frame 12 → approach 11 > 10 → advance to ph2
    assert(a.fbPhaseSlots[0] === 2, "a2 ph1 advances to ph2 when approach > cap (distance gate)");
    assert(a.streamSlot >= 2, "a2 ph1→ph2 increments +0x6ea and arms stream slot");
    assert(shots.length === 0, "a2 ph1 fires no effect triggers (cosmetic afterimage only)");
  }

  // --- a2 ph2: wall contact → exit (+0x694 = 8.0 + dt). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1; a.fbPhaseSlots[0] = 2;
    a.wallContact = 1; a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 wall exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "a2 ph2 wall-contact clears +0x73f and strips +0x5e0");
    assert(a.stateTimer === AN.EXIT_STATE_TIMER + 1, "a2 ph2 seeds +0x694 = 8.0 + dt (FLOAT_8043a904)");
  }

  // ------------------------------------------------------------------------
  console.log("\n[acceleration-ninja.selfcheck] ACTION 3 — hover dash strike (3-phase):");

  // --- a3 ph0: setup → ph1. +0x558=4, +0x54a=5, +0x48=10 (not frozen). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "a3 ph0 advances +0x540 to ph1");
    assert(a.handlerTimer === AN.A3_MAIN_TIMER, "a3 ph0 seeds +0x558 = 4 (FLOAT_8043a90c)");
    assert(a.ninjaScratch54a === 5, "a3 ph0 seeds +0x54a = 5");
    assert(a.yVel === AN.A2_APPROACH_CAP, "a3 ph0 seeds +0x48 = 10.0 when not position-frozen (FLOAT_8043a900)");
  }

  // --- a3 ph1: contactP0>=1 drains +0x558; on expire re-seed 4 + cue 10 + FX 0x23/0x24 (+0x54a--). ---
  {
    const shots: Shot[] = [];
    let cue = -1;
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_x, addr, type) => shots.push({ addr, type }),
      onPlayCue: (_x, c) => { cue = c; },
    };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    root(a); // ph0 → ph1
    a.contactP0 = 1; // >= 1 → enter strike/decay branch
    // +0x558 drains 4→3→2→1 over 3 frames (no fire); the 4th frame hits <=0 → re-seed + FX.
    for (let f = 0; f < 3; f += 1) root(a);
    assert(shots.length === 0 && a.handlerTimer > 0, "a3 ph1 drains +0x558 without firing while > 0");
    root(a); // 4th: +0x558 1→0 (<=0) → re-seed + cue + FX
    assert(a.handlerTimer === AN.A3_MAIN_TIMER, "a3 ph1 re-seeds +0x558 = 4 on expiry");
    assert(cue === 10, "a3 ph1 plays cue 10 (zz_00f036c_(actor, 10)) on expiry");
    assert(a.ninjaScratch54a === 4, "a3 ph1 decrements +0x54a 5→4");
    assert(shots.length === 2 && shots[0]!.addr === EFFECT_TRIGGER && shots[0]!.type === 0x23 && shots[1]!.type === 0x24,
      `a3 ph1 fires zz_0099e70_(0x23) + zz_0099e70_(0x24) (got ${JSON.stringify(shots)})`);
  }

  // --- a3 ph1: contactP0 < 0 → advance to ph2 + +0x558 = 180. ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    root(a); // ph0 → ph1
    a.contactP0 = -1; // < 0 → advance
    root(a); // ph1 → ph2
    assert(a.fbPhaseSlots[0] === 2, "a3 ph1 advances to ph2 on contactP0 < 0");
    assert(a.handlerTimer === AN.A3_PH2_TIMER, "a3 ph1 seeds +0x558 = 180 (FLOAT_8043a914) on advance");
  }

  // --- a3 ph2: grounded + neg contact → upper-body cue 7 exit (+0x694 = 1.0 + dt). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1; a.fbPhaseSlots[0] = 2;
    a.grounded77b0 = true; a.contactP0 = -1; a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 upper-body exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "a3 ph2 clears +0x73f and strips +0x5e0");
    assert(a.stateTimer === AN.PHYSICS_RATE + 1, "a3 ph2 grounded-exit seeds +0x694 = 1.0 + dt (FLOAT_8043a8d0)");
  }

  // --- a3 ph2: not grounded → drain +0x558 to 0 → exit (+0x694 = 4.0 + dt). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1; a.fbPhaseSlots[0] = 2; a.handlerTimer = 2;
    a.grounded77b0 = false; a.contactP0 = 0; a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // drain 2→1 (still waiting)
    assert(a.housekeeping73f === 1, "a3 ph2 waits while +0x558 > 0");
    root(a); // drain 1→0 → exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0, "a3 ph2 exits when +0x558 <= 0");
    assert(a.stateTimer === AN.A3_MAIN_TIMER + 1, "a3 ph2 timeout seeds +0x694 = 4.0 + dt (FLOAT_8043a90c)");
  }

  // ------------------------------------------------------------------------
  console.log("\n[acceleration-ninja.selfcheck] charge-arm ammo gate + fallthrough:");

  // --- charge-arm: ammo OK → effect triggers 0x21 + 0x22. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_x, slot, _c, _m) => { assert(slot === 0, "charge-arm gates zz_006dbe0_(actor,0,1,1)"); return true; },
      onFamilyProjectile: (_x, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor();
    const ok = accelerationNinjaChargeArm(a, sctx);
    assert(ok, "charge-arm returns true on ammo available");
    assert(shots.length === 2 && shots[0]!.type === 0x21 && shots[1]!.type === 0x22,
      `charge-arm fires zz_0099e70_(0x21) + zz_0099e70_(0x22) (got ${JSON.stringify(shots)})`);
  }

  // --- charge-arm: ammo denied → no effects, returns false. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_x, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor();
    const ok = accelerationNinjaChargeArm(a, sctx);
    assert(!ok, "charge-arm returns false on ammo denial");
    assert(shots.length === 0, "charge-arm suppresses effects on denial");
  }

  // --- Non-0/2/3 action indices fall through (no-op). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as NinjaActor;
    configureAccelerationNinjaFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 1; // not surfaced
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "rootAction no-ops for actionIndex 1 (not surfaced)");
  }
}
