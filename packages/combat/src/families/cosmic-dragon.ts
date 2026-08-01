// COSMIC DRAGON (pl0504, borgNumber 0x504) + COSMIC DRAGON II (pl0510, borgNumber
// 0x510) family — bespoke multi-action phase-machine port.
//
// ctor 0x80108954. Source: research/decomp/ghidra-export/chunk_0029.c:3354-3684
// (root + action-0 phase fns) + chunk_0030.c:1-579 (action-2/3 phase fns).
//
// Root action router FUN_80108f80 (chunk_0029.c:3356) indexes PTR_FUN_803253d0 by
// actionIndex (+0x580) — 4 slots (0x803253e0 - 0x803253d0 = 0x10). Actions 0, 2, 3
// are bespoke; action 1 is not reached by these borgs (no table in boot.dol) and
// falls through. Each bespoke action sub-router dispatches its own variant table
// (indexed by +0x581), and each variant dispatches its own phase table (indexed by
// +0x540):
//
//   action 0 variant-x (FUN_80108fbc → PTR_FUN_803253e0[+0x581], 3 entries):
//     variant 0 FUN_80108ff8 table @0x803253ec — 3-phase stream claw
//       [FUN_80109048, FUN_801090bc, FUN_80109190]  (aim 0xc1, stream slot 0x2a→0/1)
//     variant 1 FUN_80109230 table @0x803253f8 — 3-phase alt claw + motion post-step
//       [FUN_801092a8, FUN_80109354, FUN_80109428]  (aim 0x81, stream slot 0xf→2/3)
//     variant 2 FUN_801094f4 table @0x804344e8 — 2-phase charge-gated claw + physics
//       [FUN_80109558, FUN_80109638]  (gate +0x5dd==0x11, stream slot 4/5)
//   action 2 variant-x (FUN_8010992c → PTR_FUN_8032541c[+0x581], 3 entries):
//     variant 0 FUN_80109968 table @0x80325428 — 3-phase stream strike
//       [FUN_801099a4, FUN_80109a30, FUN_80109ac8]
//     variant 1 FUN_80109b20 table @0x80325434 — 3-phase alt strike + drag/physics
//       [FUN_80109b8c, FUN_80109bfc, FUN_80109cac]
//     variant 2 FUN_80109d04 table @0x80325440 — 3-phase charge-gated strike + physics
//       [FUN_80109d64, FUN_80109df4, FUN_80109e94]
//   action 3 variant-x (FUN_80109ff8 → PTR_FUN_8032544c[+0x581], 3 entries):
//     variant 0 FUN_8010a034 table @0x804344f0 — 2-phase contact spawn
//       [FUN_8010a06c, FUN_8010a0d4]
//     variant 1 FUN_8010a170 table @0x804344f8 — 2-phase alt spawn + motion post-step
//       [FUN_8010a1dc, FUN_8010a264]
//     variant 2 FUN_8010a300 table @0x80434500 — 2-phase charge-gated spawn + physics
//       [FUN_8010a35c, FUN_8010a3c0]
//
// TRUE table lengths confirmed by address arithmetic (the work-queue overread several
// entries — e.g. it claimed action-0 @0x803253ec held 6 pointers; in fact
// 0x803253f8 - 0x803253ec = 0xC → 3 pointers, and 0x80325404 - 0x803253f8 = 0xC → 3
// pointers; 0x80325404 begins a float data array, NOT a function table). The three
// 0x804344xx tables are each 2 pointers (0x804344f0-0x804344e8 = 0x8, etc.).
//
// Borg-switched contact spawns (one per action):
//   action 0 FUN_80109710 → zz_01deb68_(actor, 5 for pl0504 / 6 for pl0510, ...)
//   action 2 FUN_80109ef0 → ammo gate zz_006dbe0_(2,1,1) → zz_00e19a8_(actor, 6 / 0x12)
//   action 3 FUN_8010a468 → zz_008672c_(actor, 0 / 1)   (NO ammo gate)
//
// Float constants read from user-data/GG4E/disc/sys/boot.dol (cited per const).
//
// PARTIAL PORT NOTE: the phase sequencing, timer drains, contact/ammo gates, the
// motion/physics post-steps, the velocity drag (zz_006ed8c_) and the borg-switched
// spawns are ported 1:1. The physics integrator FUN_80067310 is applied via the
// shared integratePhysics; the collision stepper zz_00677b0_ is a best-effort
// grounded-flag probe. The land/air exit helpers zz_006a474_/zz_006a5a4_ route to
// romGroundIdleReturn/romAirKnockoutReturn; zz_006a750_ → dispatchUpperBodyCue. The
// trail-child vec3 transform in FUN_801097ac (borg-switched DAT_80325404/80325410
// offsets, rel data not in boot.dol) and the cancel helper zz_006a3d0_ are marked
// TODO(host). None of these affect the testable phase transitions.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  allocateWeapon,
  resetPoseHousekeeping,
  stepTargetYaw,
} from "../rom/helpers.js";
import { integratePhysics } from "../rom/physics.js";
import {
  romAirKnockoutReturn,
  romGroundIdleReturn,
} from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

// ----------------------------------------------------------------------------
// Identity.
// ----------------------------------------------------------------------------
const COSMIC_DRAGON_BORG_NUMBERS: Record<string, number> = {
  pl0504: 0x504, // COSMIC DRAGON
  pl0510: 0x510, // COSMIC DRAGON II
};

export type CosmicDragonBorgId = keyof typeof COSMIC_DRAGON_BORG_NUMBERS;

// ----------------------------------------------------------------------------
// Spawner addresses (family-local borg-switched contact spawners).
// ----------------------------------------------------------------------------
/** zz_01deb68_ @0x801deb68 — action-0 contact spawn. Borg-switched record type:
 *  5 for pl0504, 6 for pl0510. */
export const COSMIC_A0_SPAWNER = 0x801deb68;
/** zz_00e19a8_ @0x800e19a8 — action-2 contact spawn (ammo-gated). Borg-switched:
 *  6 for pl0504, 0x12 for pl0510. */
export const COSMIC_A2_SPAWNER = 0x800e19a8;
/** zz_008672c_ @0x8008672c — action-3 contact spawn (NO ammo gate). Borg-switched:
 *  0 for pl0504, 1 for pl0510. */
export const COSMIC_A3_SPAWNER = 0x8008672c;

// ----------------------------------------------------------------------------
// Config constants (DOL-read, cited).
// ----------------------------------------------------------------------------
export const COSMIC_DRAGON = {
  /** FLOAT_8043950c = 0.0 — universal zero / phase-1 wait threshold. */
  ZERO: 0.0,
  /** FLOAT_8043951c = 144.0 — action-0 handler timer seed (+0x560). */
  ACTION0_TIMER_SEED: 144.0,
  /** FLOAT_80439538 = 180.0 — action-2 handler timer seed (+0x560). */
  ACTION2_TIMER_SEED: 180.0,
  /** FLOAT_80439520 = -1.0 — startStream default playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80439524 = 0.95 — action-0/3 variant-1 motion post-step scale. */
  MOTION_SCALE: 0.95,
  /** FLOAT_80439528 = 1.0 — FUN_80067310 gravity coefficient (action 0/2/3 physics). */
  PHYSICS_RATE: 1.0,
  /** FLOAT_8043952c = 41.0 — action-0 contact +0x558 re-seed (FUN_80109710). */
  A0_CONTACT_TIMER: 41.0,
  /** FLOAT_80439530 = 20.0 — action-0 contact +0x55c re-seed / action-3 +0x694 seed. */
  A0_CONTACT_CD: 20.0,
  /** FLOAT_80439534 = 1.4 — action-0 contact +0x170 scale (× +0x764). */
  A0_CONTACT_SCALE: 1.4,
  /** FLOAT_80439564 = 1.0 — action-3 variant-2 FUN_80067310 gravity coefficient. */
  A3_PHYSICS_RATE: 1.0,
  /** FLOAT_8043955c = 0.95 — action-2 variant-1 velocity drag (zz_006ed8c_). */
  VELOCITY_DRAG: 0.95,
  /** +0x5e0 action-mode bits stripped at every exit. */
  ACTION_MODE_BITS: 0x3,
  /** zz_006d144_ aim masks: action-0 main 0xc1, alt 0x81. */
  AIM_MAIN: 0xc1,
  AIM_ALT: 0x81,
  /** zz_006a750_ upper-body cue dispatched at action-2 variant-2 / action-3 variant-2 exit. */
  EXIT_CUE_0x10: 0x10,
  /** +0x5dd charge-release state byte gating variant-2 entry (0x11 = state 17). */
  CHARGE_RELEASE_STATE: 0x11,
  /** +0x54e stream-cursor seed armed by action-2 phase-0 setup (0x78 = 120). */
  A2_CURSOR_SEED: 0x78,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not firstclass on RomActor.
// ----------------------------------------------------------------------------
export interface CosmicDragonScratch {
  /** +0x560: action-0/2/3 handler timer (FLOAT_8043951c=144 / FLOAT_80439538=180). */
  cdTimer560?: number;
  /** +0x55c: contact/trail cooldown sub-timer (seed 20.0 by FUN_80109710; drained by
   *  FUN_801097ac). */
  cdCooldown55c?: number;
  /** +0x6ec: action-0 per-move stream slot byte (0/1 v0, 2/3 v1, 4/5 v2). */
  cdStreamSlot6ec?: number;
  /** +0x6f7: contact/trail mode byte (2 while trail active; 0 on phase-1 advance). */
  cdContactMode6f7?: number;
  /** +0x1dfc: signed aim-roll accumulator (sign selects the stream slot at advance). */
  cdAimRoll1dfc?: number;
  /** +0x5dd: charge-release gate byte (== 0x11 permits variant-2 entry). */
  cdChargeRelease5dd?: number;
  /** +0x54e: action-2 stream cursor (seed 0x78; decremented by FUN_80109ef0). */
  cdStreamCursor54e?: number;
  /** +0x709: action-2 phase-1 advance sub-mode byte (set to 4 on advance). */
  cdSubMode709?: number;
}

type CdActor = RomActor & CosmicDragonScratch;

function scratchOf(actor: RomActor): CdActor {
  return actor as CdActor;
}

// ----------------------------------------------------------------------------
// Physics bridges. FUN_80067310 → integratePhysics (the shared port). zz_00677b0_
// owns clamp/collision not fully surfaced; the documented grounded-flag probe is
// applied so observable motion is faithful. Phase transitions never depend on these.
// ----------------------------------------------------------------------------

/** Best-effort port of zz_00677b0_(actor) — collision/step probe. Returns the
 *  scratch grounded flag (1 grounded, 0 airborne). TODO: real surface collision. */
function collisionStep(actor: RomActor): number {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  return grounded === true ? 1 : 0;
}

/** Port of zz_006ed8c_(factor, actor) — per-frame velocity drag (hSpeed/yVel ×= factor). */
function applyVelocityDrag(actor: RomActor, factor: number): void {
  actor.hSpeed *= factor;
  actor.yVel *= factor;
}

/** Port of FUN_8006e0ac(actor, mask) — stream/collision event poll. Returns >= 0 when
 *  a part-mask event fired this frame. No stream banks → returns -1 (no event), the
 *  exact ROM fallback. */
function pollStreamEvent(_actor: RomActor, _mask: number): number {
  return -1;
}

// ----------------------------------------------------------------------------
// Exit prelude + land/air selectors. The ROM call sites clear +0x73f and strip the
// +0x5e0 action-mode bits BEFORE calling zz_006a474_/zz_006a5a4_; the shared
// idle-return helpers expect that prelude.
// ----------------------------------------------------------------------------
function exitToGround(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~COSMIC_DRAGON.ACTION_MODE_BITS;
  romGroundIdleReturn(actor);
}

function exitToAir(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~COSMIC_DRAGON.ACTION_MODE_BITS;
  romAirKnockoutReturn(actor);
}

// ----------------------------------------------------------------------------
// Borg-switched contact handlers.
// ----------------------------------------------------------------------------

/** FUN_80109710 (chunk_0029.c:3653) — action-0 contact. +0x542++, seeds +0x558=41.0
 *  and +0x55c=20.0, then fires the borg-switched spawner zz_01deb68_ (5 / 6). */
function action0Contact(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[2] = (actor.fbPhaseSlots[2] ?? 0) + 1; // +0x542++
  actor.handlerTimer = COSMIC_DRAGON.A0_CONTACT_TIMER;      // +0x558 = 41.0
  actor.cdCooldown55c = COSMIC_DRAGON.A0_CONTACT_CD;        // +0x55c = 20.0
  // +0x170 = scale × +0x764 (or +0x814 when +0xd0&4==0) and the +0x14c/150/154 record
  // copies are projectile-buffer writes; surfaced via the spawn event only.
  const type = actor.borgNumber === 0x510 ? 6 : 5;
  ctx.onFamilyProjectile?.(actor, COSMIC_A0_SPAWNER, type); // zz_01deb68_(p, 5/6, ...)
}

/** FUN_801097ac (chunk_0030.c:3) — action-0 trail driver. While +0x542 > 0 it ticks
 *  the trail child each frame, draining +0x558; on +0x558 <= 0 it stamps +0x542=0xff
 *  (trail terminate). The borg-switched vec3 offset (DAT_80325404 / DAT_80325410) and
 *  the PSMTXMultVec child-position transform are renderer-side (rel data) and are
 *  marked TODO(host); the timer logic is ported 1:1. */
function action0Trail(actor: CdActor): void {
  if ((actor.fbPhaseSlots[2] ?? 0) > 0) { // +0x542 > 0
    actor.cdContactMode6f7 = 2;           // +0x6f7 = 2
    // TODO(host): borg-switched vec3 offset + PSMTXMultVec child positioning
    // (DAT_80325404 for pl0504, DAT_80325410 for pl0510 — rel data, not boot.dol).
    actor.cdCooldown55c = (actor.cdCooldown55c ?? 0) - actor.dt; // +0x55c -= dt
    actor.handlerTimer = actor.handlerTimer - actor.dt;          // +0x558 -= dt
    if (actor.handlerTimer <= COSMIC_DRAGON.ZERO) {
      actor.fbPhaseSlots[2] = 0xff; // +0x542 = 0xff (trail terminate)
    }
  }
}

/** FUN_80109ef0 (chunk_0030.c:340) — action-2 per-tick contact. Sets +0x6f7=2, ticks
 *  the stream, and on +0x1cef contact runs the ammo gate zz_006dbe0_(2,1,1) then the
 *  borg-switched spawner zz_00e19a8_ (6 / 0x12). */
function action2Contact(actor: CdActor, ctx: StreamContext): void {
  // Leading zz_006de44_(p, 0xf0f00) part-mask event drain — no banks → 0 events.
  actor.cdContactMode6f7 = 2; // +0x6f7 = 2
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  if (actor.contactP0 > 0) { // +0x1cef > 0
    actor.contactP0 = 0;
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(p, 2, 1, 1)
      const type = actor.borgNumber === 0x510 ? 0x12 : 6;
      ctx.onFamilyProjectile?.(actor, COSMIC_A2_SPAWNER, type); // zz_00e19a8_(p, 6/0x12, ...)
    }
  }
  // zz_0066ac0_(p, 0) — TODO(host): unknown post-contact helper (not ported).
}

/** FUN_8010a468 (chunk_0030.c:567) — action-3 contact. NO ammo gate. Fires the
 *  borg-switched spawner zz_008672c_ (0 / 1). */
function action3Contact(actor: CdActor, ctx: StreamContext): void {
  const type = actor.borgNumber === 0x510 ? 1 : 0;
  ctx.onFamilyProjectile?.(actor, COSMIC_A3_SPAWNER, type); // zz_008672c_(p, 0/1)
}

// ============================================================================
// Action 0 — stream claw (3 variants). Variant dispatch FUN_80108fbc indexes
// PTR_FUN_803253e0[+0x581]. Each variant has its own phase table + post-step.
// ============================================================================

/** Action-0 variant 0 phase 0 — setup. FUN_80109048. */
function a0v0Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.cdTimer560 = COSMIC_DRAGON.ACTION0_TIMER_SEED;      // +0x560 = 144.0
  actor.gravityCoeff = COSMIC_DRAGON.ZERO;                  // +0x50
  actor.yVel = COSMIC_DRAGON.ZERO;                          // +0x48
  actor.hDecel = COSMIC_DRAGON.ZERO;                        // +0x4c
  actor.hSpeed = COSMIC_DRAGON.ZERO;                        // +0x44
  resetPoseHousekeeping(actor);                             // +0x80/7e/7c = 0
  actor.cdAimRoll1dfc = 0;                                  // +0x1dfc = 0
  startStream(actor, 0xf, 0, 0x2a, COSMIC_DRAGON.STREAM_RATE); // zz_004beb8_(rate -1, mask 0xf, group 0, slot 0x2a)
  void ctx;
}

/** Action-0 variant 0 phase 1 — wait. FUN_801090bc. */
function a0v0Phase1Wait(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  const event = pollStreamEvent(actor, 0x2000); // FUN_8006e0ac(p, 0x2000)
  actor.cdTimer560 = (actor.cdTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  const aimReady = stepTargetYaw(actor, COSMIC_DRAGON.AIM_MAIN); // zz_006d144_(p, 0xc1)
  if (actor.cdTimer560 <= COSMIC_DRAGON.ZERO || aimReady || event >= 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.cdStreamSlot6ec = (actor.cdAimRoll1dfc ?? 0) < 0 ? 1 : 0; // +0x6ec
    startStream(actor, 0xf, 2, actor.cdStreamSlot6ec ?? 0, COSMIC_DRAGON.STREAM_RATE);
  }
}

/** Action-0 variant 0 phase 2 — contact + trail + wall exit. FUN_80109190. */
function a0v0Phase2(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  if (actor.contactP0 > 0) { // +0x1cef > 0
    actor.contactP0 = 0;
    if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(p, 0, 1, 1)
      action0Contact(actor, ctx); // FUN_80109710(p, p+0x144)
    }
  }
  action0Trail(actor); // FUN_801097ac(p, p+0x144)
  if (actor.wallContact !== 0) { // +0x1cee != 0
    exitToGround(actor); // zz_006a474_(p)
  }
}

/** Action-0 variant 1 phase 0 — setup. FUN_801092a8. */
function a0v1Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.cdTimer560 = COSMIC_DRAGON.ACTION0_TIMER_SEED;
  actor.gravityCoeff = COSMIC_DRAGON.ZERO;
  actor.yVel = COSMIC_DRAGON.ZERO;
  actor.hDecel = COSMIC_DRAGON.ZERO;
  actor.hSpeed = COSMIC_DRAGON.ZERO;
  resetPoseHousekeeping(actor);
  actor.cdAimRoll1dfc = 0;
  // motion = pos − targetCache5e8.
  actor.motion.x = actor.pos.x - actor.targetCache5e8.x;
  actor.motion.y = actor.pos.y - actor.targetCache5e8.y;
  actor.motion.z = actor.pos.z - actor.targetCache5e8.z;
  // The stream start is gated on the descriptor anim rows (+0x1d0c/+0x1d0d != 0xf);
  // the common case fires it.
  startStream(actor, 0xf, 0, 0xf, COSMIC_DRAGON.STREAM_RATE);
  void ctx;
}

/** Action-0 variant 1 phase 1 — wait. FUN_80109354. */
function a0v1Phase1Wait(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  const event = pollStreamEvent(actor, 0x2000);
  actor.cdTimer560 = (actor.cdTimer560 ?? 0) - actor.dt;
  const aimReady = stepTargetYaw(actor, COSMIC_DRAGON.AIM_ALT); // zz_006d144_(p, 0x81)
  if (actor.cdTimer560 <= COSMIC_DRAGON.ZERO || aimReady || event >= 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdStreamSlot6ec = (actor.cdAimRoll1dfc ?? 0) < 0 ? 3 : 2;
    startStream(actor, 0x3, 2, actor.cdStreamSlot6ec ?? 0, COSMIC_DRAGON.STREAM_RATE);
  }
}

/** Action-0 variant 1 phase 2 — contact + trail + wall exit. FUN_80109428. */
function a0v1Phase2(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    if (allocateWeapon(actor, ctx, 0, 1, true)) {
      action0Contact(actor, ctx);
    }
  }
  action0Trail(actor);
  if (actor.contactP1 !== 0) { // +0x1cf0 != 0 (reseek event)
    if (pollStreamEvent(actor, 0x2000) < 0) {
      stepTargetYaw(actor, COSMIC_DRAGON.AIM_MAIN); // zz_006d144_(p, 0xc1)
    }
  }
  if (actor.wallContact !== 0) {
    exitToAir(actor); // zz_006a5a4_(p)
  }
}

/** Action-0 variant 2 phase 0 — charge gate + setup. FUN_80109558. */
function a0v2Phase0Gate(actor: CdActor, ctx: StreamContext): void {
  if (actor.cdChargeRelease5dd === COSMIC_DRAGON.CHARGE_RELEASE_STATE) { // +0x5dd == 0x11
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdAimRoll1dfc = 0;
    pollStreamEvent(actor, 0x4000); // FUN_8006e0ac(p, 0x4000)
    actor.cdStreamSlot6ec = (actor.cdAimRoll1dfc ?? 0) < 0 ? 5 : 4;
    startStream(actor, 0x1, 2, actor.cdStreamSlot6ec ?? 0, COSMIC_DRAGON.STREAM_RATE);
    // Conditional secondary stream (gated on +0x1d0c/+0x1d0d != 0xb); common case fires.
    startStream(actor, 0x6, 0, 0xb, COSMIC_DRAGON.STREAM_RATE);
  } else {
    // zz_006a3d0_(p, 0, 3, 0) — cancel/restart (TODO(host): command-record re-dispatch).
  }
  void ctx;
}

/** Action-0 variant 2 phase 1 — contact + trail + wall exit. FUN_80109638. */
function a0v2Phase1(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if ((actor.fbPhaseSlots[2] ?? 0) === 0) { // +0x542 == 0
    pollStreamEvent(actor, 0x4000);
  }
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    if (allocateWeapon(actor, ctx, 0, 1, true)) {
      action0Contact(actor, ctx);
    }
  }
  action0Trail(actor);
  // zz_0066ac0_(p, 0) + zz_0066e40_(p, 2) — TODO(host): anim/part helpers (not ported).
  actor.lockYaw = actor.heading; // +0x5ae = +0x72
  if (actor.wallContact !== 0) {
    exitToAir(actor); // zz_006a5a4_(p)
  }
}

/** Action-0 sub-handler (FUN_80108fbc). Dispatches PTR_FUN_803253e0[+0x581]. */
function action0(actor: CdActor, ctx: StreamContext): void {
  const variant = actor.variantIndex;
  if (variant === 1) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a0v1Phase0Setup(actor, ctx); break;
      case 1: a0v1Phase1Wait(actor, ctx); break;
      case 2: a0v1Phase2(actor, ctx); break;
      default: break;
    }
    // FUN_80109230 post-step: motion *= 0.95; pos += motion; collision.
    actor.motion.x *= COSMIC_DRAGON.MOTION_SCALE;
    actor.motion.y *= COSMIC_DRAGON.MOTION_SCALE;
    actor.motion.z *= COSMIC_DRAGON.MOTION_SCALE;
    actor.pos.x += actor.motion.x;
    actor.pos.y += actor.motion.y;
    actor.pos.z += actor.motion.z;
    collisionStep(actor);
    return;
  }
  if (variant === 2) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a0v2Phase0Gate(actor, ctx); break;
      case 1: a0v2Phase1(actor, ctx); break;
      default: break;
    }
    // FUN_801094f4 post-step: FUN_80067310(1.0, p, lockYaw); collision.
    integratePhysics(COSMIC_DRAGON.PHYSICS_RATE, actor, actor.lockYaw);
    collisionStep(actor);
    return;
  }
  // variant 0
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a0v0Phase0Setup(actor, ctx); break;
    case 1: a0v0Phase1Wait(actor, ctx); break;
    case 2: a0v0Phase2(actor, ctx); break;
    default: break;
  }
}

// ============================================================================
// Action 2 — stream strike (3 variants). Variant dispatch FUN_8010992c indexes
// PTR_FUN_8032541c[+0x581]. Each variant has its own phase table + post-step.
// ============================================================================

/** Action-2 variant 0 phase 0 — setup. FUN_801099a4. */
function a2v0Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.cdTimer560 = COSMIC_DRAGON.ACTION2_TIMER_SEED; // +0x560 = 180.0
  actor.cdStreamCursor54e = COSMIC_DRAGON.A2_CURSOR_SEED; // +0x54e = 0x78
  actor.streamSlot = 0;                                 // +0x6ea = 0
  actor.cdContactMode6f7 = 0;                           // +0x6f7 = 0
  actor.gravityCoeff = COSMIC_DRAGON.ZERO;
  actor.yVel = COSMIC_DRAGON.ZERO;
  actor.hDecel = COSMIC_DRAGON.ZERO;
  actor.hSpeed = COSMIC_DRAGON.ZERO;
  resetPoseHousekeeping(actor);
  const slot = actor.streamSlot; // +0x6ea (pre-increment)
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  void ctx;
}

/** Action-2 variant 0 phase 1 — wait. FUN_80109a30. */
function a2v0Phase1Wait(actor: CdActor, ctx: StreamContext): void {
  action2Contact(actor, ctx); // FUN_80109ef0(p)
  // zz_0066e40_(p, 0) — TODO(host): anim helper (not ported).
  actor.cdTimer560 = (actor.cdTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  if (actor.cdTimer560 <= COSMIC_DRAGON.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdContactMode6f7 = 0;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  }
}

/** Action-2 variant 0 phase 2 — wall exit. FUN_80109ac8. */
function a2ExitGround(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    exitToGround(actor); // zz_006a474_(p)
  }
}

/** Action-2 variant 1 phase 0 — setup. FUN_80109b8c. */
function a2v1Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.cdTimer560 = COSMIC_DRAGON.ACTION2_TIMER_SEED;
  actor.cdStreamCursor54e = COSMIC_DRAGON.A2_CURSOR_SEED;
  actor.streamSlot = 2; // +0x6ea = 2
  actor.cdContactMode6f7 = 0;
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  void ctx;
}

/** Action-2 variant 1 phase 1 — wait. FUN_80109bfc (3× zz_0066e40_). */
function a2v1Phase1Wait(actor: CdActor, ctx: StreamContext): void {
  action2Contact(actor, ctx);
  // zz_0066e40_(p, 0) ×3 — TODO(host): anim helper (not ported).
  actor.cdTimer560 = (actor.cdTimer560 ?? 0) - actor.dt;
  if (actor.cdTimer560 <= COSMIC_DRAGON.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdContactMode6f7 = 0;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  }
}

/** Action-2 variant 1 phase 2 — wall exit. FUN_80109cac. */
function a2ExitAir(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    exitToAir(actor); // zz_006a5a4_(p)
  }
}

/** Action-2 variant 2 phase 0 — charge gate + setup. FUN_80109d64. */
function a2v2Phase0Gate(actor: CdActor, ctx: StreamContext): void {
  if (actor.cdChargeRelease5dd === COSMIC_DRAGON.CHARGE_RELEASE_STATE) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdTimer560 = COSMIC_DRAGON.ACTION2_TIMER_SEED;
    actor.cdStreamCursor54e = COSMIC_DRAGON.A2_CURSOR_SEED;
    actor.streamSlot = 4; // +0x6ea = 4
    actor.cdContactMode6f7 = 0;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  } else {
    // zz_006a3d0_(p, 2, 3, 0) — cancel/restart (TODO(host)).
  }
  void ctx;
}

/** Action-2 variant 2 phase 1 — wait. FUN_80109df4. */
function a2v2Phase1Wait(actor: CdActor, ctx: StreamContext): void {
  action2Contact(actor, ctx);
  // zz_0066e40_(p, 2) — TODO(host).
  actor.lockYaw = actor.heading; // +0x5ae = +0x72
  actor.cdTimer560 = (actor.cdTimer560 ?? 0) - actor.dt;
  if (actor.cdTimer560 <= COSMIC_DRAGON.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.cdContactMode6f7 = 0;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, COSMIC_DRAGON.STREAM_RATE);
  }
}

/** Action-2 variant 2 phase 2 — wall exit via zz_006a750_(0x10). FUN_80109e94. */
function a2v2Phase2(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~COSMIC_DRAGON.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, COSMIC_DRAGON.EXIT_CUE_0x10); // zz_006a750_(p, 0x10)
  }
}

/** Action-2 sub-handler (FUN_8010992c). Dispatches PTR_FUN_8032541c[+0x581]. */
function action2(actor: CdActor, ctx: StreamContext): void {
  const variant = actor.variantIndex;
  if (variant === 1) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a2v1Phase0Setup(actor, ctx); break;
      case 1: a2v1Phase1Wait(actor, ctx); break;
      case 2: a2ExitAir(actor, ctx); break;
      default: break;
    }
    // FUN_80109b20 post-step: drag 0.95; zz_0067458_(1.0, p, lockYaw); collision.
    applyVelocityDrag(actor, COSMIC_DRAGON.VELOCITY_DRAG);
    integratePhysics(COSMIC_DRAGON.PHYSICS_RATE, actor, actor.lockYaw);
    collisionStep(actor);
    return;
  }
  if (variant === 2) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a2v2Phase0Gate(actor, ctx); break;
      case 1: a2v2Phase1Wait(actor, ctx); break;
      case 2: a2v2Phase2(actor, ctx); break;
      default: break;
    }
    // FUN_80109d04 post-step: FUN_80067310(1.0, p, lockYaw); collision.
    integratePhysics(COSMIC_DRAGON.PHYSICS_RATE, actor, actor.lockYaw);
    collisionStep(actor);
    return;
  }
  // variant 0
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a2v0Phase0Setup(actor, ctx); break;
    case 1: a2v0Phase1Wait(actor, ctx); break;
    case 2: a2ExitGround(actor, ctx); break;
    default: break;
  }
}

// ============================================================================
// Action 3 — contact spawn (3 variants, 2 phases each). Variant dispatch
// FUN_80109ff8 indexes PTR_FUN_8032544c[+0x581].
// ============================================================================

/** Action-3 variant 0 phase 0 — setup. FUN_8010a06c. */
function a3v0Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.gravityCoeff = COSMIC_DRAGON.ZERO;
  actor.yVel = COSMIC_DRAGON.ZERO;
  actor.hDecel = COSMIC_DRAGON.ZERO;
  actor.hSpeed = COSMIC_DRAGON.ZERO;
  resetPoseHousekeeping(actor);
  startStream(actor, 0xf, 4, 6, COSMIC_DRAGON.STREAM_RATE); // slot 6
  void ctx;
}

/** Shared action-3 exit +0x694 = FLOAT_80439530(20.0) + dt. */
function seedA3StateTimer(actor: CdActor): void {
  actor.stateTimer = COSMIC_DRAGON.A0_CONTACT_CD + actor.dt; // +0x694 = 20.0 + dt
}

/** Action-3 variant 0 phase 1 — contact spawn + ground exit. FUN_8010a0d4. */
function a3v0Phase1(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) { // +0x1cef > 0 (NO ammo gate on action 3)
    actor.contactP0 = 0;
    action3Contact(actor, ctx); // FUN_8010a468(p)
  }
  // zz_0066ac0_(p, 0) + zz_0066e40_(p, 0) — TODO(host): anim helpers.
  if (actor.wallContact !== 0) {
    exitToGround(actor); // zz_006a474_(p)
    seedA3StateTimer(actor);
  }
}

/** Action-3 variant 1 phase 0 — setup. FUN_8010a1dc. */
function a3v1Phase0Setup(actor: CdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.gravityCoeff = COSMIC_DRAGON.ZERO;
  actor.yVel = COSMIC_DRAGON.ZERO;
  actor.hDecel = COSMIC_DRAGON.ZERO;
  actor.hSpeed = COSMIC_DRAGON.ZERO;
  resetPoseHousekeeping(actor);
  actor.motion.x = actor.pos.x - actor.targetCache5e8.x;
  actor.motion.y = actor.pos.y - actor.targetCache5e8.y;
  actor.motion.z = actor.pos.z - actor.targetCache5e8.z;
  startStream(actor, 0xf, 4, 7, COSMIC_DRAGON.STREAM_RATE); // slot 7
  void ctx;
}

/** Action-3 variant 1 phase 1 — contact spawn + air exit. FUN_8010a264. */
function a3v1Phase1(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    action3Contact(actor, ctx);
  }
  // zz_0066ac0_(p, 0) + zz_0066e40_(p, 1) — TODO(host).
  if (actor.wallContact !== 0) {
    exitToAir(actor); // zz_006a5a4_(p)
    seedA3StateTimer(actor);
  }
}

/** Action-3 variant 2 phase 0 — charge gate + setup. FUN_8010a35c. */
function a3v2Phase0Gate(actor: CdActor, ctx: StreamContext): void {
  if (actor.cdChargeRelease5dd === COSMIC_DRAGON.CHARGE_RELEASE_STATE) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    startStream(actor, 0xf, 4, 8, COSMIC_DRAGON.STREAM_RATE); // slot 8
  } else {
    // zz_006a3d0_(p, 5, 3, 0) — cancel/restart (TODO(host)).
  }
  void ctx;
}

/** Action-3 variant 2 phase 1 — contact spawn + cue-0x10 exit. FUN_8010a3c0. */
function a3v2Phase1(actor: CdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    action3Contact(actor, ctx);
  }
  // zz_0066ac0_(p, 0) + zz_0066e40_(p, 2) — TODO(host).
  actor.lockYaw = actor.heading; // +0x5ae = +0x72
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~COSMIC_DRAGON.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, COSMIC_DRAGON.EXIT_CUE_0x10); // zz_006a750_(p, 0x10)
    seedA3StateTimer(actor);
  }
}

/** Action-3 sub-handler (FUN_80109ff8). Dispatches PTR_FUN_8032544c[+0x581]. */
function action3(actor: CdActor, ctx: StreamContext): void {
  const variant = actor.variantIndex;
  if (variant === 1) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a3v1Phase0Setup(actor, ctx); break;
      case 1: a3v1Phase1(actor, ctx); break;
      default: break;
    }
    // FUN_8010a170 post-step: motion *= 0.95; pos += motion; collision.
    actor.motion.x *= COSMIC_DRAGON.MOTION_SCALE;
    actor.motion.y *= COSMIC_DRAGON.MOTION_SCALE;
    actor.motion.z *= COSMIC_DRAGON.MOTION_SCALE;
    actor.pos.x += actor.motion.x;
    actor.pos.y += actor.motion.y;
    actor.pos.z += actor.motion.z;
    collisionStep(actor);
    return;
  }
  if (variant === 2) {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: a3v2Phase0Gate(actor, ctx); break;
      case 1: a3v2Phase1(actor, ctx); break;
      default: break;
    }
    // FUN_8010a300 post-step: FUN_80067310(1.0, p, lockYaw); collision.
    integratePhysics(COSMIC_DRAGON.PHYSICS_RATE, actor, actor.lockYaw);
    collisionStep(actor);
    return;
  }
  // variant 0
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a3v0Phase0Setup(actor, ctx); break;
    case 1: a3v0Phase1(actor, ctx); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_80108f80 (PTR_FUN_803253d0[+0x580]).
// ----------------------------------------------------------------------------
export function createCosmicDragonRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: action0(actor, ctx); return;
      case 2: action2(actor, ctx); return;
      case 3: action3(actor, ctx); return;
      default: return; // action 1 not reached by these borgs (no table in boot.dol)
    }
  };
}

/** Configure a freshly-spawned COSMIC DRAGON member. Stamps the borg number and
 *  wires the bespoke action dispatcher. */
export function configureCosmicDragonFamily(
  actor: RomActor,
  borgId: CosmicDragonBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = COSMIC_DRAGON_BORG_NUMBERS[borgId] ?? 0x504;
  actor.rootAction = createCosmicDragonRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — phase transitions, borg-switched spawns, ammo-gates. Mirrors the
// assert pattern of rom.selfcheck.ts (phoenix-dragon / fighter-craft).
// ============================================================================
export function runCosmicDragonSelfTests(assert: (cond: boolean, msg: string) => void): void {
  function approxEq(a: number, b: number, eps = 1e-4): boolean {
    return Math.abs(a - b) <= eps;
  }

  // ---- Action 0 variant 0: phase 0 setup ---------------------------------
  console.log("[cosmic-dragon] action 0 v0 — phase 0 setup (FUN_80109048):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    assert(a.borgNumber === 0x504, "borgNumber stamped 0x504 (COSMIC DRAGON)");
    a.actionIndex = 0; a.variantIndex = 0;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 7;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++)");
    const s = a as RomActor & CosmicDragonScratch;
    assert(approxEq(s.cdTimer560!, COSMIC_DRAGON.ACTION0_TIMER_SEED),
      "+0x560 == 144.0 (FLOAT_8043951c action-0 timer seed)");
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0) && approxEq(a.gravityCoeff, 0),
      "velocity scalars zeroed (FLOAT_8043950c)");
  }

  // ---- Action 0 variant 0: phase 1 timer drain → phase 2 -----------------
  console.log("[cosmic-dragon] action 0 v0 — phase 1 timer drain (FUN_801090bc):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 1000, y: 0, z: 0 };
    a.aimOrigin518.x = 0; a.aimOrigin518.y = 0; a.aimOrigin518.z = 0;
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    const s = a as RomActor & CosmicDragonScratch;
    s.cdTimer560 = 1.0; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2");
    assert(s.cdStreamSlot6ec === 0, "+0x6ec == 0 (cdAimRoll1dfc >= 0 → slot 0)");
  }

  // ---- Action 0 variant 0: phase 2 contact + borg-switched spawn SUCCESS --
  console.log("[cosmic-dragon] action 0 v0 — phase 2 contact + spawn (FUN_80109190 + FUN_80109710):");
  {
    const a = createRomActor();
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
    };
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(a.contactP0 === 0, "+0x1cef cleared after contact");
    assert(spawns.length === 1 && spawns[0]!.addr === COSMIC_A0_SPAWNER && spawns[0]!.type === 5,
      "pl0504 → zz_01deb68_(5) on ammo success");
    assert(a.fbPhaseSlots[2] === 1, "+0x542 == 1 (FUN_80109710 increments)");
    // FUN_80109710 seeds +0x558=41.0, then FUN_801097ac drains it by dt the same frame.
    assert(approxEq(a.handlerTimer, COSMIC_DRAGON.A0_CONTACT_TIMER - a.dt),
      "+0x558 == 41.0 − dt (FLOAT_8043952c seeded, then trail-drained)");
  }

  // ---- Action 0 variant 0: phase 2 ammo-gate FAILURE ---------------------
  console.log("[cosmic-dragon] action 0 v0 — phase 2 ammo-gate failure:");
  {
    const a = createRomActor();
    let allocArgs = null as { slot: number; count: number; mode: number | undefined } | null;
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onAllocateResource: (_actor, slot, count, mode) => {
        allocArgs = { slot, count, mode };
        return false;
      },
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
    };
    configureCosmicDragonFamily(a, "pl0510", ctx);
    assert(a.borgNumber === 0x510, "borgNumber stamped 0x510 (COSMIC DRAGON II)");
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(allocArgs !== null && allocArgs!.slot === 0 && allocArgs!.count === 1 && allocArgs!.mode === 1,
      "zz_006dbe0_(actor, 0, 1, 1) exact arguments");
    assert(spawns.length === 0, "ammo denied → no zz_01deb68_ spawn");
    assert((a.fbPhaseSlots[2] ?? 0) === 0, "ammo denied → +0x542 NOT incremented");
  }

  // ---- Action 0 variant 0: phase 2 wall-contact exit ---------------------
  console.log("[cosmic-dragon] action 0 v0 — phase 2 wall-contact exit:");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0 * 2 + 1] = 9; // upper-body cue 0 → ubState 9 (ground idle return)
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.controlWord = 0x3; // action-mode bits set
    a.wallContact = 1; a.dt = 1;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
    assert(a.housekeeping73f === 0, "+0x73f cleared on wall-contact exit");
    assert(a.ubCue === 0, "ground exit → zz_006a474_ dispatches upper cue 0");
  }

  // ---- Action 0 variant 1: motion post-step + phase 1 → 2 ----------------
  console.log("[cosmic-dragon] action 0 v1 — motion post-step + phase 1 (FUN_80109230 + FUN_80109354):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 0; a.variantIndex = 1;
    a.pos.x = 100; a.targetCache5e8.x = 0;
    a.rootAction!(a);
    // setup: motion = pos − target = 100; post-step motion *= 0.95 = 95; pos += 95 → 195.
    assert(approxEq(a.pos.x, 195.0), "pos.x == 195 (motion × FLOAT_80439524=0.95 added)");
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1");
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 0, y: 0, z: 1000 };
    const s = a as RomActor & CosmicDragonScratch;
    s.cdTimer560 = 0.5; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2 (aim 0x81)");
    assert(s.cdStreamSlot6ec === 2, "+0x6ec == 2 (cdAimRoll1dfc >= 0 → alt slot 2)");
  }

  // ---- Action 0 variant 2: charge gate (blocked vs admitted) -------------
  console.log("[cosmic-dragon] action 0 v2 — charge gate (FUN_80109558):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 0; a.variantIndex = 2;
    (a as RomActor & CosmicDragonScratch).cdChargeRelease5dd = 0; // != 0x11 → blocked
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 0, "+0x5dd != 0x11 → phase NOT advanced (cancel path)");
    const b = createRomActor();
    configureCosmicDragonFamily(b, "pl0510", ctx);
    b.actionIndex = 0; b.variantIndex = 2;
    (b as RomActor & CosmicDragonScratch).cdChargeRelease5dd = COSMIC_DRAGON.CHARGE_RELEASE_STATE;
    b.rootAction!(b);
    assert(b.fbPhaseSlots[0] === 1, "+0x5dd == 0x11 → phase advanced 0 → 1");
  }

  // ---- Action 0 trail: +0x542 terminate on +0x558 drain ------------------
  console.log("[cosmic-dragon] action 0 — trail terminate (FUN_801097ac):");
  {
    const a = createRomActor();
    const ctx: StreamContext = { onAllocateResource: () => true };
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a); // contact seeds +0x542=1, +0x558=41
    // Tick the trail until +0x558 drains to <= 0.
    a.contactP0 = 0; a.wallContact = 0;
    for (let i = 0; i < 50; i++) a.rootAction!(a);
    assert(a.fbPhaseSlots[2] === 0xff, "+0x558 drained ≤ 0 → +0x542 == 0xff (trail terminate)");
  }

  // ---- Action 2 variant 0: phase 0 setup + slot cursor -------------------
  console.log("[cosmic-dragon] action 2 v0 — phase 0 setup (FUN_801099a4):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 2; a.variantIndex = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1");
    const s = a as RomActor & CosmicDragonScratch;
    assert(approxEq(s.cdTimer560!, COSMIC_DRAGON.ACTION2_TIMER_SEED),
      "+0x560 == 180.0 (FLOAT_80439538 action-2 timer seed)");
    assert(s.cdStreamCursor54e === COSMIC_DRAGON.A2_CURSOR_SEED, "+0x54e == 0x78");
    assert(a.streamSlot === 1, "+0x6ea == 1 (cursor incremented past slot 0)");
  }

  // ---- Action 2 variant 0: phase 1 timer drain → phase 2 -----------------
  console.log("[cosmic-dragon] action 2 v0 — phase 1 timer drain (FUN_80109a30):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 2; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    const s = a as RomActor & CosmicDragonScratch;
    s.cdTimer560 = 1.0; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2");
    assert(s.cdContactMode6f7 === 0, "+0x6f7 == 0 on advance");
  }

  // ---- Action 2 contact: ammo-gated borg-switched spawn ------------------
  console.log("[cosmic-dragon] action 2 — contact ammo gate + borg-switched spawn (FUN_80109ef0):");
  {
    const a = createRomActor();
    let allocArgs = null as { slot: number; count: number; mode: number | undefined } | null;
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onAllocateResource: (_actor, slot, count, mode) => {
        allocArgs = { slot, count, mode };
        return true;
      },
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
    };
    configureCosmicDragonFamily(a, "pl0510", ctx);
    a.actionIndex = 2; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; a.dt = 1;
    const s = a as RomActor & CosmicDragonScratch;
    s.cdTimer560 = 100.0; // large so no phase advance this tick
    a.rootAction!(a);
    assert(allocArgs !== null && allocArgs!.slot === 2 && allocArgs!.count === 1 && allocArgs!.mode === 1,
      "zz_006dbe0_(actor, 2, 1, 1) exact arguments");
    assert(spawns.length === 1 && spawns[0]!.addr === COSMIC_A2_SPAWNER && spawns[0]!.type === 0x12,
      "pl0510 → zz_00e19a8_(0x12) on ammo success");
    assert(a.contactP0 === 0, "+0x1cef cleared after contact");
    assert(s.cdContactMode6f7 === 2, "+0x6f7 == 2 (FUN_80109ef0 sets trail mode)");
  }

  // ---- Action 2 contact: ammo denial suppresses spawn -------------------
  console.log("[cosmic-dragon] action 2 — ammo denial suppresses spawn:");
  {
    const a = createRomActor();
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
    };
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 2; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; a.dt = 1;
    (a as RomActor & CosmicDragonScratch).cdTimer560 = 100.0;
    a.rootAction!(a);
    assert(spawns.length === 0, "ammo denied → no zz_00e19a8_ spawn");
    assert(a.contactP0 === 0, "+0x1cef still cleared (contact consumed regardless)");
  }

  // ---- Action 2 variant 1: drag + physics post-step ----------------------
  console.log("[cosmic-dragon] action 2 v1 — drag + physics post-step (FUN_80109b20):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 2; a.variantIndex = 1;
    a.hSpeed = 10.0; a.yVel = 20.0;
    a.timescale = 1; a.tierScale = 1; a.dt = 1;
    a.rootAction!(a); // ph0 setup zeros scalars, then post-step applies drag to the zeros (no-op) + integrate
    assert(a.streamSlot === 3, "+0x6ea == 3 (v1 starts at 2, incremented)");
    // Force a phase-2 exit to observe the drag on non-zero scalars.
    a.fbPhaseSlots[0] = 2; a.hSpeed = 10.0; a.yVel = 20.0; a.wallContact = 0;
    a.rootAction!(a);
    assert(approxEq(a.hSpeed, 10.0 * COSMIC_DRAGON.VELOCITY_DRAG), "hSpeed *= 0.95 (zz_006ed8c_ FLOAT_8043955c)");
    assert(approxEq(a.yVel, 20.0 * COSMIC_DRAGON.VELOCITY_DRAG), "yVel *= 0.95 (velocity drag)");
  }

  // ---- Action 2 variant 2: charge gate + cue-0x10 exit ------------------
  console.log("[cosmic-dragon] action 2 v2 — charge gate + cue-0x10 exit (FUN_80109d64 / FUN_80109e94):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 2; a.variantIndex = 2;
    (a as RomActor & CosmicDragonScratch).cdChargeRelease5dd = COSMIC_DRAGON.CHARGE_RELEASE_STATE;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "+0x5dd == 0x11 → phase advanced 0 → 1");
    assert(a.streamSlot === 5, "+0x6ea == 5 (v2 starts at 4, incremented)");
    // Jump to phase 2 and force the cue-0x10 exit.
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[COSMIC_DRAGON.EXIT_CUE_0x10 * 2 + 1] = 12; // cue 0x10 → ubState 12
    a.fbPhaseSlots[0] = 2; a.wallContact = 1; a.dt = 1;
    a.controlWord = 0x3;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared on cue-0x10 exit");
    assert(a.housekeeping73f === 0, "+0x73f cleared on exit");
    assert(a.ubCue === COSMIC_DRAGON.EXIT_CUE_0x10, "v2 wall exit → zz_006a750_(0x10)");
  }

  // ---- Action 3 variant 0: setup + contact spawn (NO ammo gate) ----------
  console.log("[cosmic-dragon] action 3 v0 — setup + contact spawn (FUN_8010a06c + FUN_8010a0d4):");
  {
    const a = createRomActor();
    const spawns: Array<{ addr: number; type: number }> = [];
    const allocCalls: unknown[] = [];
    const ctx: StreamContext = {
      onAllocateResource: (...args) => { allocCalls.push(args); return true; },
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
    };
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 3; a.variantIndex = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1");
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(allocCalls.length === 0, "action 3 has NO ammo gate (zz_006dbe0_ never called)");
    assert(spawns.length === 1 && spawns[0]!.addr === COSMIC_A3_SPAWNER && spawns[0]!.type === 0,
      "pl0504 → zz_008672c_(0) on contact");
    assert(a.contactP0 === 0, "+0x1cef cleared after contact");
  }

  // ---- Action 3 variant 0: ground exit seeds +0x694 ----------------------
  console.log("[cosmic-dragon] action 3 v0 — ground exit seeds +0x694 (FUN_8010a0d4):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0510", ctx);
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0 * 2 + 1] = 9;
    a.actionIndex = 3; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    a.wallContact = 1; a.dt = 1;
    a.rootAction!(a);
    assert(approxEq(a.stateTimer, COSMIC_DRAGON.A0_CONTACT_CD + 1),
      "+0x694 == FLOAT_80439530(20.0) + dt on action-3 exit");
    assert(a.ubCue === 0, "v0 wall exit → zz_006a474_ (ground idle return)");
  }

  // ---- Action 3 variant 1: motion post-step + air exit -------------------
  console.log("[cosmic-dragon] action 3 v1 — motion post-step + air exit (FUN_8010a170 + FUN_8010a264):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0504", ctx);
    a.actionIndex = 3; a.variantIndex = 1;
    a.pos.x = 40; a.targetCache5e8.x = 0;
    a.rootAction!(a);
    // setup: motion = 40; post-step motion *= 0.95 = 38; pos += 38 → 78.
    assert(approxEq(a.pos.x, 78.0), "pos.x == 78 (motion × FLOAT_80439524=0.95 added)");
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[6 * 2 + 1] = 14; // air-knockout cue 6 → ubState 14
    a.fbPhaseSlots[0] = 1; a.wallContact = 1; a.dt = 1;
    a.rootAction!(a);
    assert(a.ubCue === 6, "v1 wall exit → zz_006a5a4_ (air knockout, cue 6)");
  }

  // ---- Action 3 variant 2: charge gate + cue-0x10 exit ------------------
  console.log("[cosmic-dragon] action 3 v2 — charge gate + cue-0x10 exit (FUN_8010a35c + FUN_8010a3c0):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configureCosmicDragonFamily(a, "pl0510", ctx);
    a.actionIndex = 3; a.variantIndex = 2;
    (a as RomActor & CosmicDragonScratch).cdChargeRelease5dd = 0; // blocked
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 0, "+0x5dd != 0x11 → phase NOT advanced (cancel path)");
    (a as RomActor & CosmicDragonScratch).cdChargeRelease5dd = COSMIC_DRAGON.CHARGE_RELEASE_STATE;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "+0x5dd == 0x11 → phase advanced 0 → 1");
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[COSMIC_DRAGON.EXIT_CUE_0x10 * 2 + 1] = 12;
    a.wallContact = 1; a.dt = 1; a.controlWord = 0x3;
    const spawns: Array<{ addr: number; type: number }> = [];
    (ctx as StreamContext).onFamilyProjectile = (_actor, addr, type) => { spawns.push({ addr, type }); };
    a.contactP0 = 1;
    a.rootAction!(a);
    // contact fires before exit: pl0510 → zz_008672c_(1)
    assert(spawns.length === 1 && spawns[0]!.type === 1, "pl0510 → zz_008672c_(1) on contact");
    assert(a.ubCue === COSMIC_DRAGON.EXIT_CUE_0x10, "v2 wall exit → zz_006a750_(0x10)");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared on exit");
  }
}
