// PHOENIX DRAGON (pl0502, borgNumber 0x502) + PHOENIX DRAGON II (pl050e, borgNumber
// 0x50e) family — bespoke multi-action phase-machine port.
//
// ctor 0x80142674. Source: research/decomp/ghidra-export/chunk_0037.c:2888-3399.
//
// Root action router FUN_80142af4 (chunk_0037.c:2888) indexes PTR_FUN_8033b490 by
// actionIndex (+0x580). Each action sub-router dispatches its own phase table
// (indexed by +0x540) and applies a shared motion post-step:
//
//   action 0 variant 0 (FUN_80142b6c) table @0x8033b4b0 — 3-phase diving claw
//     [FUN_80142bf0, FUN_80142c9c, FUN_80142d00]  (aim 0xc1, stream slot 0)
//   action 0 variant 1 (FUN_80142dd4) table @0x8033b4bc — 3-phase alt dive
//     [FUN_80142e58, FUN_80142ee0, FUN_80142d00]  (aim 0x81, stream slot 1; shares spawn)
//   action 1          (FUN_80143270) table @0x8033b4dc — 5-phase ground dash
//     [FUN_801432c0, FUN_801433f4, FUN_80143498, FUN_80143538, FUN_8014367c]
//
// TRUE table lengths confirmed by address arithmetic (the work-queue overread 8
// entries for action 0 — it bled into the adjacent variant table @0x8033b4bc):
//   0x8033b4bc - 0x8033b4b0 = 0xC  → action-0 main   = 3 pointers
//   0x8033b4c8 - 0x8033b4bc = 0xC  → action-0 variant = 3 pointers
//   0x8033b4dc - 0x8033b4c8 = 0x14 → variant-dispatch table 2
//   action-1 @0x8033b4dc            = 5 pointers (next table outside text section)
//
// Borg-switched orbiting-orb deploy: FUN_80142794 (chunk_0037.c:2743) calls the
// spawner FUN_80143750 twice with a borg-switched record type — 0 for pl0502,
// 1 for pl050e — selecting the dragon's two orb children.
//
// Float constants read from user-data/GG4E/disc/sys/boot.dol (cited per const).
//
// PARTIAL PORT NOTE: the phase sequencing, timer drains, contact/ammo gates,
// motion post-step, afterimage, velocity drag (zz_006ed8c_) and the borg-switched
// orb deploy are ported 1:1. The physics integrator FUN_80067310 and the collision
// stepper zz_00677b0_ are applied as best-effort documented formulas (the full
// clamp/collision response isn't surfaced on RomActor); the land/shot transition
// helpers zz_006a474_/zz_006a5a4_/zz_006a668_ (next-state selectors) are marked
// TODO. None of these affect the testable phase transitions.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  allocateWeapon,
  groundSnapRevert,
  stepAfterimage,
  stepPartTargetPitch,
  stepTargetYaw,
} from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

// ----------------------------------------------------------------------------
// Identity.
// ----------------------------------------------------------------------------
const PHOENIX_DRAGON_BORG_NUMBERS: Record<string, number> = {
  pl0502: 0x502, // PHOENIX DRAGON
  pl050e: 0x50e, // PHOENIX DRAGON II
};

export type PhoenixDragonBorgId = keyof typeof PHOENIX_DRAGON_BORG_NUMBERS;

// ----------------------------------------------------------------------------
// Spawner addresses.
// ----------------------------------------------------------------------------
/** FUN_80143750 @0x80143750 — orbiting-orb deploy spawner. Borg-switched record
 *  type: 0 for pl0502, 1 for pl050e. Port (0/1) selects the two orb slots. */
export const PHOENIX_ORB_SPAWNER = 0x80143750;

// ----------------------------------------------------------------------------
// Config constants (DOL-read, cited).
// ----------------------------------------------------------------------------
export const PHOENIX_DRAGON = {
  /** FLOAT_8043a22c = 144.0 — action-0 dive timer seed (+0x560). */
  ACTION0_TIMER_SEED: 144.0,
  /** FLOAT_8043a244 = 60.0 — action-1 dash timer seed (+0x558). */
  ACTION1_TIMER_SEED: 60.0,
  /** FLOAT_8043a248 = 40.0 — action-1 dash speed scalar (× trig(steerYaw)). */
  DASH_SPEED: 40.0,
  /** FLOAT_8043a228 = 0.99 — action-0 motion post-step scale (gnt4_PSQUATScale_bl). */
  MOTION_SCALE: 0.99,
  /** FLOAT_8043a218 = 0.9 — action-1 phase-4 steer-yaw decay. */
  STEER_DECAY: 0.9,
  /** FLOAT_8043a24c = 0.04 — action-1 phase-3 steer-yaw bounce coefficient. */
  STEER_BOUNCE_RATE: 0.04,
  /** FLOAT_8043a250 = 0.95 — action-1 phase-4 velocity drag (zz_006ed8c_). */
  VELOCITY_DRAG: 0.95,
  /** FLOAT_8043a20c = 0.0 — universal zero / phase-1 wait threshold. */
  ZERO: 0.0,
  /** FLOAT_8043a230 = -1.0 — startStream default playback rate. */
  STREAM_RATE: -1.0,
  /** zz_006d144_ aim masks: action-0 main 0xc1, alt 0x81, action-1 0xc0. */
  AIM_MAIN: 0xc1,
  AIM_ALT: 0x81,
  AIM_DASH: 0xc0,
  /** zz_00c74ec_ deploy sound cues (borg-switched). */
  DEPLOY_CUE_502: 0x11,
  DEPLOY_CUE_50e: 0x15,
  /** +0x5e0 control-word bits polled by the phase-2 exit branch. */
  CTRL_BIT6: 0x40,
  CTRL_BIT7: 0x80,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface PhoenixDragonScratch {
  /** +0x560: action-0 handler timer (seed FLOAT_8043a22c = 144.0). */
  pdAction0Timer?: number;
  /** +0x6f6: steer-active flag (1 during dive; cleared on contact). */
  pdSteerActive6f6?: number;
  /** +0x6f5: stream-mode byte (set to 3 on a connecting contact). */
  pdStreamMode6f5?: number;
  /** +0x6ea: per-move stream slot cursor (incremented per stream arm). */
  pdStreamSlot6ea?: number;
  /** +0x6f3: handler mode byte (2 during dash, 0xff on phase-3→4 arm). */
  pdHandlerMode6f3?: number;
  /** +0x152: steer yaw accumulator (FUN_80143094). */
  pdSteerYaw152?: number;
  /** +0x1b01: action-1 phase-3→4 advance gate byte. */
  pdDashGate1b01?: number;
  /** +0x14c: charge accumulator (deploy zeros it). */
  pdCharge14c?: number;
  /** +0x150: charge yaw accumulator (deploy zeros it). */
  pdChargeYaw150?: number;
}

type PdActor = RomActor & PhoenixDragonScratch;

function scratchOf(actor: RomActor): PdActor {
  return actor as PdActor;
}

const TAU = Math.PI * 2;

/** BAM16 → radians. */
function bamRad(bam: number): number {
  return bam * TAU / 0x10000;
}

// ----------------------------------------------------------------------------
// Physics bridges. The full FUN_80067310 integrator and zz_00677b0_ collision
// stepper own clamp/collision behavior not surfaced on RomActor; the documented
// scalar projection (actor.ts FUN_80067310 comment) is applied so observable
// motion is faithful. Phase transitions never depend on these.
// ----------------------------------------------------------------------------

/** Best-effort port of FUN_80067310(rate, actor, yaw) — the scalar-speed
 *  integrator (chunk_0008.c:3794-3828). TODO: maxHSpeed/maxRise/maxFall clamps
 *  and the gravity-param term require the full physics runtime. */
function integrateMotion(actor: RomActor, rate: number, yaw: number): void {
  const ts = actor.timescale * actor.tierScale;
  const yr = bamRad(yaw);
  actor.pos.x += ts * rate * actor.hSpeed * Math.cos(yr);
  actor.pos.y += ts * rate * actor.yVel;
  actor.pos.z += ts * rate * actor.hSpeed * Math.sin(yr);
  actor.hSpeed -= actor.hDecel * ts;
}

/** Best-effort port of zz_00677b0_(actor) — the collision/step-height probe
 *  (returns grounded/stepped). TODO: real surface collision. Returns the
 *  scratch grounded flag when a physics runtime is absent. */
function collisionStep(actor: RomActor): number {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  return grounded === true ? 1 : 0;
}

/** Port of zz_006ed8c_(factor, actor) — per-frame velocity drag. Confirmed by
 *  FLAME/CYBER-DRAGON selfchecks (hSpeed/yVel ×= factor pre-integration). */
function applyVelocityDrag(actor: RomActor, factor: number): void {
  actor.hSpeed *= factor;
  actor.yVel *= factor;
}

// ----------------------------------------------------------------------------
// Borg-switched orbiting-orb deploy — FUN_80142794 (chunk_0037.c:2743).
//   pl0502 → FUN_80141fdc + spawn(type 0, port 0) + spawn(type 0, port 1) + cue 0x11
//   pl050e → FUN_801421c0 + spawn(type 1, port 0) + spawn(type 1, port 1) + cue 0x15
// FUN_80143750(actor, type, port) is the spawner; the host fires one
// onFamilyProjectile per port with the borg-switched record type.
// ----------------------------------------------------------------------------
export function deployPhoenixDragonOrbs(actor: RomActor, ctx: StreamContext): void {
  if (actor.borgNumber === 0x502) {
    // FUN_80141fdc (camera-beam trace) is a renderer-side camera update, not
    // surfaced here; the observable game effect is the two orb spawns + cue.
    ctx.onFamilyProjectile?.(actor, PHOENIX_ORB_SPAWNER, 0); // port 0
    ctx.onFamilyProjectile?.(actor, PHOENIX_ORB_SPAWNER, 0); // port 1
    ctx.onPlayCue?.(actor, PHOENIX_DRAGON.DEPLOY_CUE_502); // zz_00c74ec_(0x11)
  } else if (actor.borgNumber === 0x50e) {
    // FUN_801421c0 allocates the camera-beam struct (renderer-side).
    ctx.onFamilyProjectile?.(actor, PHOENIX_ORB_SPAWNER, 1); // port 0
    ctx.onFamilyProjectile?.(actor, PHOENIX_ORB_SPAWNER, 1); // port 1
    ctx.onPlayCue?.(actor, PHOENIX_DRAGON.DEPLOY_CUE_50e); // zz_00c74ec_(0x15)
  }
  const a = scratchOf(actor);
  a.pdCharge14c = PHOENIX_DRAGON.ZERO; // +0x14c = 0.0
  a.pdChargeYaw150 = 0; // +0x150 = 0
}

// ----------------------------------------------------------------------------
// Action 0 — diving claw (3 phases, variant-dispatched).
//   ph0 FUN_80142bf0/4_2e58: setup — +0x540++, timer=144.0 (+0x560), steer on,
//                             zero velocity scalars + pose accums, aim, startStream,
//                             motion = pos − targetCache5e8, clear ctrl bit7.
//   ph1 FUN_80142c9c/4_2ee0: wait — drain +0x560 by dt; advance when <= 0.0 OR
//                             aim-ready (zz_006d144_).
//   ph2 FUN_80142d00 (shared): spawn — tickStream; on +0x1cef contact clear it +
//                             ammo gate (success → steer off, mode 3); on +0x1cee
//                             wall-contact exit (clear housekeeping, strip action
//                             bits, branch on ctrl bits 6/7).
// ----------------------------------------------------------------------------

/** Phase 0 — setup. aimMask is 0xc1 (main) or 0x81 (alt); streamSlot 0 or 1. */
function action0Phase0Setup(actor: PdActor, ctx: StreamContext, aimMask: number, streamSlot: number): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.pdAction0Timer = PHOENIX_DRAGON.ACTION0_TIMER_SEED; // +0x560 = 144.0
  actor.pdSteerActive6f6 = 1; // +0x6f6 = 1
  actor.gravityCoeff = PHOENIX_DRAGON.ZERO; // +0x50 = 0.0
  actor.yVel = PHOENIX_DRAGON.ZERO; // +0x48
  actor.hDecel = PHOENIX_DRAGON.ZERO; // +0x4c
  actor.hSpeed = PHOENIX_DRAGON.ZERO; // +0x44
  actor.poseAccum80 = 0; // +0x80
  actor.poseAccum7e = 0; // +0x7e
  actor.poseAccum7c = 0; // +0x7c
  stepTargetYaw(actor, aimMask); // zz_006d144_(p, aimMask)
  startStream(actor, 0xf, 2, streamSlot, PHOENIX_DRAGON.STREAM_RATE); // zz_004beb8_(rate -1, mask 0xf, group 2, slot)
  // motion = pos − targetCache5e8 (gnt4_PSVECSubtract_bl(pos, &+0x5e8, motion)).
  actor.motion.x = actor.pos.x - actor.targetCache5e8.x;
  actor.motion.y = actor.pos.y - actor.targetCache5e8.y;
  actor.motion.z = actor.pos.z - actor.targetCache5e8.z;
  actor.controlWord = actor.controlWord & ~PHOENIX_DRAGON.CTRL_BIT7; // +0x5e0 &= ~0x80
  void ctx;
}

/** Phase 1 — wait. */
function action0Phase1Wait(actor: PdActor, aimMask: number): void {
  actor.pdAction0Timer = (actor.pdAction0Timer ?? 0) - actor.dt; // +0x560 -= dt
  const aimReady = stepTargetYaw(actor, aimMask); // zz_006d144_(p, aimMask) != 0
  if (actor.pdAction0Timer <= PHOENIX_DRAGON.ZERO || aimReady) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  }
}

/** Phase 2 — contact + ammo gate + wall-contact exit. Shared by both variants. */
function action0Phase2Spawn(actor: PdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  if (actor.contactP0 > 0) { // +0x1cef > 0
    actor.contactP0 = 0;
    if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(p, 0, 1, 1)
      actor.pdSteerActive6f6 = 0; // +0x6f6 = 0
      actor.pdStreamMode6f5 = 3; // +0x6f5 = 3
    }
  }
  if (actor.wallContact !== 0) { // +0x1cee != 0
    actor.housekeeping73f = 0; // +0x73f = 0
    actor.controlWord = actor.controlWord & ~PHOENIX_DRAGON.ACTION_MODE_BITS; // +0x5e0 &= ~3
    if ((actor.controlWord & PHOENIX_DRAGON.CTRL_BIT6) === 0) {
      // TODO: zz_006a474_(actor) — land transition A (next-state selector, not ported).
    } else if ((actor.controlWord & PHOENIX_DRAGON.CTRL_BIT7) === 0) {
      // TODO: zz_006a5a4_(actor) — land transition B (next-state selector, not ported).
    } else {
      dispatchUpperBodyCue(actor, 0x21); // zz_006a750_(actor, 0x21)
      // TODO: zz_006a668_(actor, 0x14) — shot-channel dispatch (not ported).
    }
  }
}

/** Action-0 sub-handler (FUN_80142b6c main / FUN_80142dd4 alt). Runs the
 *  steer-gate, the phase dispatch, then the shared motion post-step:
 *  motion *= 0.99; pos += motion; ground snap. */
function action0(actor: PdActor, ctx: StreamContext): void {
  if ((actor.pdSteerActive6f6 ?? 0) > 0) {
    // FUN_80143094 steer update — TODO: full dual-axis aim requires the renderer
    // aim-anchor rows (+0x938..+0x960). Skipped; does not affect phase transitions.
  }
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (actor.variantIndex === 1) {
    switch (phase) {
      case 0: action0Phase0Setup(actor, ctx, PHOENIX_DRAGON.AIM_ALT, 1); break;
      case 1: action0Phase1Wait(actor, PHOENIX_DRAGON.AIM_ALT); break;
      case 2: action0Phase2Spawn(actor, ctx); break;
      default: break;
    }
  } else {
    switch (phase) {
      case 0: action0Phase0Setup(actor, ctx, PHOENIX_DRAGON.AIM_MAIN, 0); break;
      case 1: action0Phase1Wait(actor, PHOENIX_DRAGON.AIM_MAIN); break;
      case 2: action0Phase2Spawn(actor, ctx); break;
      default: break;
    }
  }
  // Post-step (FUN_80142b6c:2919-2921): motion *= 0.99; pos += motion; ground snap.
  actor.motion.x *= PHOENIX_DRAGON.MOTION_SCALE;
  actor.motion.y *= PHOENIX_DRAGON.MOTION_SCALE;
  actor.motion.z *= PHOENIX_DRAGON.MOTION_SCALE;
  actor.pos.x += actor.motion.x;
  actor.pos.y += actor.motion.y;
  actor.pos.z += actor.motion.z;
  groundSnapRevert(actor); // zz_00679d0_
}

// ----------------------------------------------------------------------------
// Action 1 — ground dash (5 phases, table @0x8033b4dc). FUN_80143270 clears
// +0xcc when +0x541 != 0, then dispatches the phase.
//   ph0 FUN_801432c0: setup — +0x540++, slot=0, action-speed gate, timer=60.0,
//                     aim 0xc0, motion = pos − target, pos += motion, collision,
//                     startStream(group 3, slot), +0x80c = 0.
//   ph1 FUN_801433f4: wait — conditional tickStream, pos += motion, aim, drain
//                     +0x558; advance when <= 0 OR aim-ready.
//   ph2 FUN_80143498: contact — tickStream + aim + pos; on +0x1cef → +0x540++,
//                     +0x542 = 0, timer = 60.0, mode 2.
//   ph3 FUN_80143538: steer-dash — mode 2; hSpeed/yVel = 40 × trig(steerYaw);
//                     integrate; collision bounce of steerYaw; tickStream; drain
//                     +0x558; when <= 0 AND +0x1b01 → +0x540++, timer=60, slot++,
//                     startStream(group 3), mode 0xff.
//   ph4 FUN_8014367c: exit — steerYaw *= 0.9; tickStream; drag 0.95; integrate;
//                     collision; on +0x1cee exit (clear housekeeping + action bits,
//                     branch on collision); afterimage step.
// ----------------------------------------------------------------------------

/** Action-1 phase 0 — setup. */
function action1Phase0Setup(actor: PdActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.pdStreamSlot6ea = 0; // +0x6ea = 0
  // FUN_80066838(actionSpeedRows[prevActionIndex % 3], actor) — action-speed gate.
  // TODO: FUN_80066838 is a speed-vs-threshold query not fully surfaced; the
  // common case (speed >= 1) skips the +0x541/+0xcc clear. Modeled as a no-op.
  actor.handlerTimer = PHOENIX_DRAGON.ACTION1_TIMER_SEED; // +0x558 = 60.0
  stepTargetYaw(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006d144_(p, 0xc0)
  stepPartTargetPitch(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006e1ac_(p, 0xc0, 1)
  // motion = pos − targetCache5e8; pos += motion (the setup applies it directly).
  actor.motion.x = actor.pos.x - actor.targetCache5e8.x;
  actor.motion.y = actor.pos.y - actor.targetCache5e8.y;
  actor.motion.z = actor.pos.z - actor.targetCache5e8.z;
  actor.pos.x += actor.motion.x;
  actor.pos.y += actor.motion.y;
  actor.pos.z += actor.motion.z;
  collisionStep(actor); // zz_00677b0_
  const slot = actor.pdStreamSlot6ea ?? 0; // +0x6ea (pre-increment)
  actor.pdStreamSlot6ea = slot + 1;
  startStream(actor, 0xf, 3, slot, PHOENIX_DRAGON.STREAM_RATE); // zz_004beb8_(rate -1, mask 0xf, group 3, slot)
  actor.accumulator80c = PHOENIX_DRAGON.ZERO; // +0x80c = 0.0
  // TODO: zz_0092dcc_(actor, 0) — unknown VFX/sound helper (not ported).
  void ctx;
}

/** Action-1 phase 1 — wait. */
function action1Phase1Wait(actor: PdActor, ctx: StreamContext): void {
  if (actor.streamHold1b03 !== 0) { // +0x1b03 != 0
    tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  }
  actor.pos.x += actor.motion.x; // pos += motion
  actor.pos.y += actor.motion.y;
  actor.pos.z += actor.motion.z;
  collisionStep(actor); // zz_00677b0_
  stepPartTargetPitch(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006e1ac_(p, 0xc0, 1)
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  const aimReady = stepTargetYaw(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006d144_(p, 0xc0)
  if (actor.handlerTimer <= PHOENIX_DRAGON.ZERO || aimReady) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  }
}

/** Action-1 phase 2 — contact. */
function action1Phase2Contact(actor: PdActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  stepTargetYaw(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006d144_(p, 0xc0)
  stepPartTargetPitch(actor, PHOENIX_DRAGON.AIM_DASH); // zz_006e1ac_(p, 0xc0, 1)
  actor.pos.x += actor.motion.x; // pos += motion
  actor.pos.y += actor.motion.y;
  actor.pos.z += actor.motion.z;
  collisionStep(actor); // zz_00677b0_
  if (actor.contactP0 !== 0) { // +0x1cef != 0
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.fbPhaseSlots[2] = 0; // +0x542 = 0
    actor.handlerTimer = PHOENIX_DRAGON.ACTION1_TIMER_SEED; // +0x558 = 60.0
    // TODO: FUN_80155c10(actor, 0) — unknown contact handler (not ported).
    actor.pdHandlerMode6f3 = 2; // +0x6f3 = 2
  }
}

/** Action-1 phase 3 — steer-dash. */
function action1Phase3Dash(actor: PdActor, ctx: StreamContext): void {
  actor.pdHandlerMode6f3 = 2; // +0x6f3 = 2
  // hSpeed = 40 × cos(steerYaw); yVel = 40 × −sin(steerYaw). zz_0045238_/zz_0045204_
  // are the ROM BAM16 cos/sin (the dash projects along the steer yaw).
  const steer = actor.steerYaw; // +0x18da
  actor.hSpeed = PHOENIX_DRAGON.DASH_SPEED * Math.cos(bamRad(steer)); // FLOAT_8043a248 × zz_0045238_
  actor.yVel = PHOENIX_DRAGON.DASH_SPEED * -Math.sin(bamRad(steer)); // FLOAT_8043a248 × −zz_0045204_
  integrateMotion(actor, 1.0, actor.lockYaw); // FUN_80067310(FLOAT_8043a224=1.0, p, lockYaw)
  if (collisionStep(actor) !== 0) { // zz_00677b0_ != 0
    // steerYaw *= −(0.04 × dt − 1.0)
    actor.steerYaw = Math.trunc(actor.steerYaw * -(PHOENIX_DRAGON.STEER_BOUNCE_RATE * actor.dt - 1.0));
  }
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  if (actor.handlerTimer <= PHOENIX_DRAGON.ZERO) {
    actor.handlerTimer = PHOENIX_DRAGON.ZERO; // +0x558 = 0.0
    if ((actor.pdDashGate1b01 ?? 0) !== 0) { // +0x1b01 != 0
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.handlerTimer = PHOENIX_DRAGON.ACTION1_TIMER_SEED; // +0x558 = 60.0
      const slot = actor.pdStreamSlot6ea ?? 0; // +0x6ea (pre-increment)
      actor.pdStreamSlot6ea = slot + 1;
      startStream(actor, 0xf, 3, slot, PHOENIX_DRAGON.STREAM_RATE); // zz_004beb8_(rate -1, group 3, slot)
      actor.pdHandlerMode6f3 = 0xff; // +0x6f3 = 0xff
    }
  }
}

/** Action-1 phase 4 — exit. */
function action1Phase4Exit(actor: PdActor, ctx: StreamContext): void {
  // steerYaw *= 0.9 (the GCC int→double coercion base is DOUBLE_8043a210, the
  // 0x43300000 sentinel, NOT a game offset; the real factor is FLOAT_8043a218).
  actor.steerYaw = Math.trunc(actor.steerYaw * PHOENIX_DRAGON.STEER_DECAY);
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  applyVelocityDrag(actor, PHOENIX_DRAGON.VELOCITY_DRAG); // zz_006ed8c_(FLOAT_8043a250=0.95)
  integrateMotion(actor, 1.0, actor.lockYaw); // FUN_80067310(FLOAT_8043a224=1.0, p, lockYaw)
  const stepped = collisionStep(actor); // zz_00677b0_
  if (actor.wallContact !== 0) { // +0x1cee != 0
    actor.housekeeping73f = 0; // +0x73f = 0
    actor.controlWord = actor.controlWord & ~PHOENIX_DRAGON.ACTION_MODE_BITS; // +0x5e0 &= ~3
    if (stepped === 0) {
      // TODO: zz_006a5a4_(actor) — air-land transition (not ported).
    } else {
      // TODO: zz_006a474_(actor) — ground-land transition (not ported).
    }
  }
  stepAfterimage(actor); // zz_00b22f4_
}

/** Action-1 handler — FUN_80143270 (clears +0xcc when +0x541 != 0) + phase dispatch. */
function action1(actor: PdActor, ctx: StreamContext): void {
  if ((actor.fbPhaseSlots[1] ?? 0) !== 0) { // +0x541 != 0
    // +0xcc = 0 (visibility/target pointer clear — bridge-owned, no-op here).
    (actor as RomActor & { cc?: number }).cc = 0;
  }
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: action1Phase0Setup(actor, ctx); return;
    case 1: action1Phase1Wait(actor, ctx); return;
    case 2: action1Phase2Contact(actor, ctx); return;
    case 3: action1Phase3Dash(actor, ctx); return;
    case 4: action1Phase4Exit(actor, ctx); return;
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_80142af4 (PTR_FUN_8033b490[+0x580]). Action 0
// routes through the variant dispatcher FUN_80142b30 (PTR_FUN_8033b49c[+0x581]).
// ----------------------------------------------------------------------------
export function createPhoenixDragonRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: action0(actor, ctx); return;
      case 1: action1(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned PHOENIX DRAGON member. Stamps the borg number and
 *  wires the bespoke action dispatcher. */
export function configurePhoenixDragonFamily(
  actor: RomActor,
  borgId: PhoenixDragonBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = PHOENIX_DRAGON_BORG_NUMBERS[borgId] ?? 0x502;
  actor.rootAction = createPhoenixDragonRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — phase transitions, borg-switched orb deploy, ammo-gate failure.
// Mirrors the assert pattern of rom.selfcheck.ts (Death Borg Nu / fighter-craft).
// ============================================================================
export function runPhoenixDragonSelfTests(assert: (cond: boolean, msg: string) => void): void {
  function approxEq(a: number, b: number, eps = 1e-4): boolean {
    return Math.abs(a - b) <= eps;
  }

  // ---- Action 0 main: phase 0 setup --------------------------------------
  console.log("[phoenix-dragon] action 0 main — phase 0 setup (FUN_80142bf0):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    assert(a.borgNumber === 0x502, "borgNumber stamped 0x502 (PHOENIX DRAGON)");
    a.actionIndex = 0; a.variantIndex = 0;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 7;
    a.pos.x = 100; a.targetCache5e8.x = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++)");
    const s = a as RomActor & PhoenixDragonScratch;
    assert(approxEq(s.pdAction0Timer!, PHOENIX_DRAGON.ACTION0_TIMER_SEED),
      "+0x560 == 144.0 (FLOAT_8043a22c dive timer seed)");
    assert(s.pdSteerActive6f6 === 1, "+0x6f6 == 1 (steer active armed)");
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0) && approxEq(a.gravityCoeff, 0),
      "velocity scalars zeroed (FLOAT_8043a20c)");
    // motion = pos − target = (100,0,0); ×0.99 = (99,0,0); pos += motion → x = 199.
    assert(approxEq(a.pos.x, 199.0), "pos.x == 199 (motion × FLOAT_8043a228=0.99 added)");
  }

  // ---- Action 0 main: phase 1 timer drain → phase 2 -----------------------
  console.log("[phoenix-dragon] action 0 main — phase 1 timer drain (FUN_80142c9c):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    // A distant lockTarget + heading mismatch ⇒ stepTargetYaw not ready, so the
    // timer (not aim) gates the advance.
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 1000, y: 0, z: 0 };
    a.aimOrigin518.x = 0; a.aimOrigin518.y = 0; a.aimOrigin518.z = 0;
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    const s = a as RomActor & PhoenixDragonScratch;
    s.pdAction0Timer = 1.0; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2");
  }

  // ---- Action 0 main: phase 2 contact + ammo SUCCESS ----------------------
  console.log("[phoenix-dragon] action 0 — phase 2 contact + ammo success (FUN_80142d00):");
  {
    const a = createRomActor();
    const ctx: StreamContext = { onAllocateResource: () => true };
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    const s = a as RomActor & PhoenixDragonScratch;
    s.pdSteerActive6f6 = 1; s.pdStreamMode6f5 = 0;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(a.contactP0 === 0, "+0x1cef cleared after contact");
    assert(s.pdSteerActive6f6 === 0, "ammo success → +0x6f6 = 0 (steer off)");
    assert(s.pdStreamMode6f5 === 3, "ammo success → +0x6f5 = 3");
  }

  // ---- Action 0 main: phase 2 contact + ammo FAILURE ----------------------
  console.log("[phoenix-dragon] action 0 — phase 2 ammo-gate failure:");
  {
    const a = createRomActor();
    let allocArgs = null as { slot: number; count: number; mode: number | undefined } | null;
    const ctx: StreamContext = {
      onAllocateResource: (_actor, slot, count, mode) => {
        allocArgs = { slot, count, mode };
        return false;
      },
    };
    configurePhoenixDragonFamily(a, "pl050e", ctx);
    assert(a.borgNumber === 0x50e, "borgNumber stamped 0x50e (PHOENIX DRAGON II)");
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    const s = a as RomActor & PhoenixDragonScratch;
    s.pdSteerActive6f6 = 1; s.pdStreamMode6f5 = 0;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(allocArgs !== null && allocArgs!.slot === 0 && allocArgs!.count === 1 && allocArgs!.mode === 1,
      "zz_006dbe0_(actor, 0, 1, 1) exact arguments");
    assert(a.contactP0 === 0, "+0x1cef still cleared (contact consumed regardless of ammo)");
    assert(s.pdSteerActive6f6 === 1, "ammo denied → +0x6f6 stays 1 (steer NOT disabled)");
    assert(s.pdStreamMode6f5 === 0, "ammo denied → +0x6f5 stays 0 (mode NOT set to 3)");
  }

  // ---- Action 0 main: phase 2 wall-contact exit ---------------------------
  console.log("[phoenix-dragon] action 0 — phase 2 wall-contact exit:");
  {
    const a = createRomActor();
    let ubCue = -1;
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0x21 * 2 + 1] = 9; // upper-body cue 0x21 → ubState 9
    a.actionIndex = 0; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.controlWord = 0xc3; // action bits + bit6 + bit7 set
    a.wallContact = 1; a.dt = 1;
    a.rootAction!(a);
    ubCue = a.ubCue;
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
    assert(a.housekeeping73f === 0, "+0x73f cleared on wall-contact exit");
    assert(ubCue === 0x21, "ctrl bit7 set → zz_006a750_(0x21) dispatched (ubCue)");
  }

  // ---- Action 0 variant 1: phase 0 + 1 + 2 transitions --------------------
  console.log("[phoenix-dragon] action 0 variant 1 — phase sequence (FUN_80142dd4):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 0; a.variantIndex = 1; // alt dive (aim 0x81, stream slot 1)
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "variant 1 phase 0 → 1");
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 0, y: 0, z: 1000 };
    const s = a as RomActor & PhoenixDragonScratch;
    s.pdAction0Timer = 0.5; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "variant 1 phase 1 → 2 (timer gate, aim 0x81)");
  }

  // ---- Action 1: phase 0 setup -------------------------------------------
  console.log("[phoenix-dragon] action 1 — phase 0 setup (FUN_801432c0):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 1; a.variantIndex = 0;
    a.pos.x = 50; a.targetCache5e8.x = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++)");
    const s = a as RomActor & PhoenixDragonScratch;
    assert(approxEq(a.handlerTimer, PHOENIX_DRAGON.ACTION1_TIMER_SEED),
      "+0x558 == 60.0 (FLOAT_8043a244 dash timer seed)");
    assert(s.pdStreamSlot6ea === 1, "+0x6ea == 1 (slot cursor incremented past ground slot 0)");
    // setup applies pos += (pos − target) directly: 50 + (50 − 0) = 100.
    assert(approxEq(a.pos.x, 100.0), "pos.x == 100 (motion = pos − target added)");
  }

  // ---- Action 1: phase 1 timer drain → phase 2 ---------------------------
  console.log("[phoenix-dragon] action 1 — phase 1 timer drain (FUN_801433f4):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 1000, y: 0, z: 0 };
    a.actionIndex = 1; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2");
  }

  // ---- Action 1: phase 2 contact → phase 3 -------------------------------
  console.log("[phoenix-dragon] action 1 — phase 2 contact (FUN_80143498):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 1; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 2;
    a.contactP0 = 1; a.dt = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3, "contact advances phase 2 → 3");
    assert(approxEq(a.handlerTimer, PHOENIX_DRAGON.ACTION1_TIMER_SEED), "+0x558 re-seeded 60.0");
    const s = a as RomActor & PhoenixDragonScratch;
    assert(s.pdHandlerMode6f3 === 2, "+0x6f3 == 2 (dash mode armed)");
  }

  // ---- Action 1: phase 3 dash formula + gate → phase 4 -------------------
  console.log("[phoenix-dragon] action 1 — phase 3 dash + gate (FUN_80143538):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 1; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 3;
    a.handlerTimer = 1.0; a.dt = 1;
    a.steerYaw = 0; a.lockYaw = 0; a.heading = 0;
    (a as RomActor & PhoenixDragonScratch).pdDashGate1b01 = 1;
    a.rootAction!(a);
    // steerYaw 0 → cos=1, sin=0: hSpeed = 40, yVel = 0 (FLOAT_8043a248 × trig).
    assert(approxEq(a.hSpeed, PHOENIX_DRAGON.DASH_SPEED), "hSpeed == 40 (FLOAT_8043a248 × cos(0))");
    assert(approxEq(a.yVel, 0.0), "yVel == 0 (40 × −sin(0))");
    assert(a.fbPhaseSlots[0] === 4, "timer ≤ 0 AND +0x1b01 → phase 3 → 4");
  }

  // ---- Action 1: phase 4 exit — steerYaw decay + drag + bit clear --------
  console.log("[phoenix-dragon] action 1 — phase 4 exit (FUN_8014367c):");
  {
    const a = createRomActor();
    const ctx: StreamContext = {};
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    a.actionIndex = 1; a.variantIndex = 0;
    a.fbPhaseSlots[0] = 4;
    a.steerYaw = 1000; a.hSpeed = 10.0; a.yVel = 20.0;
    a.controlWord = 0x3; // action-mode bits set
    a.wallContact = 1; a.dt = 1; a.timescale = 1; a.tierScale = 1;
    a.rootAction!(a);
    assert(approxEq(a.steerYaw, 900.0), "steerYaw *= FLOAT_8043a218 (0.9)");
    assert(approxEq(a.hSpeed, 10.0 * PHOENIX_DRAGON.VELOCITY_DRAG), "hSpeed *= 0.95 (zz_006ed8c_ FLOAT_8043a250)");
    assert(approxEq(a.yVel, 20.0 * PHOENIX_DRAGON.VELOCITY_DRAG), "yVel *= 0.95 (velocity drag)");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared on exit");
    assert(a.housekeeping73f === 0, "+0x73f cleared on wall-contact exit");
  }

  // ---- Borg-switched orbiting-orb deploy ---------------------------------
  console.log("[phoenix-dragon] deploy — borg-switched orb spawn (FUN_80143750):");
  {
    const a = createRomActor();
    const spawns: Array<{ addr: number; type: number }> = [];
    let cue = -1;
    const ctx: StreamContext = {
      onFamilyProjectile: (_actor, addr, type) => { spawns.push({ addr, type }); },
      onPlayCue: (_actor, c) => { cue = c; },
    };
    configurePhoenixDragonFamily(a, "pl0502", ctx);
    deployPhoenixDragonOrbs(a, ctx);
    assert(spawns.length === 2, "pl0502 deploys 2 orbs (ports 0 and 1)");
    assert(spawns.every((sp) => sp.addr === PHOENIX_ORB_SPAWNER && sp.type === 0),
      "pl0502 → orb record type 0 (FUN_80143750 borg-switched)");
    assert(cue === PHOENIX_DRAGON.DEPLOY_CUE_502, "pl0502 → zz_00c74ec_(0x11)");

    // pl050e → type 1 + cue 0x15.
    const b = createRomActor();
    const spawnsB: Array<{ addr: number; type: number }> = [];
    let cueB = -1;
    const ctxB: StreamContext = {
      onFamilyProjectile: (_actor, addr, type) => { spawnsB.push({ addr, type }); },
      onPlayCue: (_actor, c) => { cueB = c; },
    };
    configurePhoenixDragonFamily(b, "pl050e", ctxB);
    deployPhoenixDragonOrbs(b, ctxB);
    assert(spawnsB.length === 2 && spawnsB.every((sp) => sp.type === 1),
      "pl050e → orb record type 1 (borg-switched spawn type)");
    assert(cueB === PHOENIX_DRAGON.DEPLOY_CUE_50e, "pl050e → zz_00c74ec_(0x15)");
  }
}
