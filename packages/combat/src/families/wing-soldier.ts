// WING SOLDIER (pl0a00, borgNumber 0xa00) family — bespoke multi-action phase-machine
// port, ROM-faithful 1:1.
//
// ctor 0x80091824. Source: research/decomp/ghidra-export/chunk_0014.c:1802-2512 (ctor
// region + action-0 volley + action-1 dash) and chunk_0038.c:1440-1589 (shared
// action-1 X-special).
//
// Root action router FUN_80091a74 (chunk_0014.c:1857) indexes PTR_FUN_802db43c by
// actionIndex (+0x580). Action 0 routes through zz_0091e34_ (chunk_0014.c:2009) which
// runs a shared per-frame preamble (zz_0092480_) then dispatches the action-0 phase
// table @0x802db468 by +0x540. Action 1 is variant-dispatched (+0x581) between two
// 4-phase diving attacks:
//
//   action 0 (zz_0091e34_)  table @0x802db468 — 4-phase hover volley
//     [FUN_80091f2c, FUN_80091f94, FUN_80092030, FUN_80092174]
//   action 1 variant 0 (shared X-special) table @0x8033ecb8 — 4-phase aimed dive
//     [FUN_80147e90, FUN_80147f7c, FUN_80148014, FUN_801480fc]  (chunk_0038.c, shared
//      with pl0a01/pl0a03)
//   action 1 variant 1 (WING SOLDIER dash) table @0x802db48c — 4-phase steer dash
//     [FUN_8009268c, FUN_800927c0, FUN_8009287c, FUN_80092998]
//
// TRUE table lengths confirmed by address arithmetic + decomp (the work-queue overread
// 8 entries for table @0x802db468, bleeding past the intermediate @0x802db478 variant
// router into @0x802db48c):
//   0x802db478 - 0x802db468 = 0x10 -> action-0 phase table = 4 pointers
//   0x802db48c - 0x802db48c       -> action-1 dash table   = 4 pointers (4 distinct fns)
//   0x8033ecb8 X-special           = 4 pointers (4 distinct fns)
//
// Exit helper: unlike fighter/sirius (which dispatch cue 0x1b via zz_006a53c_), the
// wing family exits inline — clear +0x73f, strip +0x5e0 action bits, then a LAND
// transition (zz_006a4f4_ air / zz_006a474_ ground / zz_006a5a4_ air-variant). The land
// selectors are renderer-side next-state machines (TODO, same surface gap as
// phoenix-dragon). The action-0 ph2 abort additionally seeds +0x694 = +0x558 + dt.
//
// Float constants read from user-data/GG4E/disc/sys/boot.dol this session (cited per
// const). PARTIAL PORT NOTE: the +0x544/+0x545 pose/animation sub-tables dispatched by
// zz_0091e34_ (BSS tables PTR_FUN_80433968/70) are upper-body animation state machines
// and are ported as best-effort no-ops (like fighter-craft's bob-decay) — they do not
// affect the combat phase transitions or spawns. The physics integrator FUN_80067310,
// collision stepper zz_00677b0_, and target re-acquire zz_006bf80_ are applied as
// best-effort documented formulas; none affect the testable phase transitions.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, stepPartTargetPitch, stepTargetYaw } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

// ----------------------------------------------------------------------------
// Identity.
// ----------------------------------------------------------------------------
const WING_SOLDIER_BORG_NUMBERS: Record<string, number> = {
  pl0a00: 0xa00, // WING SOLDIER
};

export type WingSoldierBorgId = "pl0a00";

// ----------------------------------------------------------------------------
// Spawner addresses (family-local projectile spawner).
// ----------------------------------------------------------------------------
/** zz_0082824_ @0x80082824 — record-table projectile spawn (action-0 volley shot). */
const SHOT_HELPER = 0x80082824;

// ----------------------------------------------------------------------------
// Config constants (DOL-read, cited).
// ----------------------------------------------------------------------------
export const WING_SOLDIER = {
  // ---- action-0 hover volley (chunk_0014.c, r2 base 0x8043ea20 -> 0x80437c**) ----
  /** FLOAT_80437c80 = 0.0 — universal drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_80437c84 = -1.0 — startStream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80437c8c = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
  /** FLOAT_80437c90 = 30.0 — action-0 dive/approach timer seed (+0x560); dash ph2 speed. */
  A0_DIVE_TIMER_SEED: 30.0,
  /** FLOAT_80437c94 = 60.0 — action-0 handler-timer seed (+0x558) / cooldown reseed. */
  A0_HANDLER_TIMER_SEED: 60.0,
  /** FLOAT_80437c98 = 0.95 — dash motion scale (gnt4_PSQUATScale_bl of +0x38). */
  DASH_MOTION_SCALE: 0.95,
  /** FLOAT_80437ca0 = 4.0 — action-0 inter-shot handler-timer reseed (zz_0092534_). */
  A0_SHOT_INTERVAL: 4.0,
  /** FLOAT_80437c70 = 0.9 — dash ph3 steerYaw decay + velocity drag. */
  DASH_DECAY: 0.9,
  /** zz_0092518_ volley counter seed (+0x6ec = 5 -> 5 shots per volley). */
  VOLLEY_SHOT_CAP: 5,
  /** zz_0082824_(actor, 10) — action-0 volley shot record type. */
  VOLLEY_SHOT_TYPE: 10,
  /** +0x5d4 input bit gating the charged flag (sets +0x745). */
  CHARGE_INPUT_BIT: 0x40,
  /** +0x5d8 input mask gating the action-0 ph2 abort (any of 0xf0). */
  ABORT_INPUT_MASK: 0xf0,
  /** +0x5e0 action-mode bits stripped at every exit. */
  ACTION_MODE_BITS: 0x3,
  /** aim masks: zz_006d0dc_(0x81) yaw, zz_006e1ac_(0xc1) part-pitch, zz_006d144_(0xc0) dive. */
  AIM_YAW: 0x81,
  AIM_PART_PITCH: 0xc1,
  AIM_DIVE: 0xc0,
  // ---- action-1 shared X-special (chunk_0038.c, r2 -> 0x8043a3**) ----
  /** FLOAT_8043a328 = 60.0 — X-special ph0 handler-timer seed (+0x558). */
  XSPEC_TIMER_SEED: 60.0,
  /** FLOAT_8043a32c = -1.0 — X-special startStream rate. */
  XSPEC_STREAM_RATE: -1.0,
  /** FLOAT_8043a330 = 0.0 — X-special drain threshold. */
  XSPEC_THRESHOLD: 0.0,
  /** FLOAT_8043a334 = 20.0 — X-special ph1 advance timer reseed / speed divisor. */
  XSPEC_RESEED: 20.0,
  /** FLOAT_8043a338 = 1.0 — X-special FUN_80067310 integrate rate. */
  XSPEC_INTEGRATE_RATE: 1.0,
  /** FLOAT_8043a33c = 0.9 — X-special ph3 velocity drag. */
  XSPEC_DRAG: 0.9,
  /** FLOAT_8043a340 = 0.5 — X-special ph3 extra drag when +0x760 < +0x3c. */
  XSPEC_DRAG_FAST: 0.5,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface WingSoldierScratch {
  /** +0x54a (s16): aim-settled flag from zz_006d0dc_ (0 = settled). */
  wsAimFlag54a?: number;
  /** +0x54c (s16): action-0 stream-slot cursor (5 in ph1/ph2, 10 in ph3). */
  wsStreamSlot54c?: number;
  /** +0x54e (s16): action-1 dive yaw used by the sin/cos speed projection. */
  wsDiveYaw54e?: number;
  /** +0x560 (float): action-0 dive/approach timer (seed 30.0, drained by zz_0092480_). */
  wsDiveTimer560?: number;
  /** +0x55c (float): action-0 ph3 cooldown / exit timer (seed 60.0). */
  wsCooldown55c?: number;
  /** +0x6ea (byte): per-move stream slot cursor (incremented per stream arm). */
  wsStreamSlot6ea?: number;
  /** +0x6eb (byte): stream/anim slot class derived from aim yaw error (cosmetic). */
  wsStreamClass6eb?: number;
  /** +0x6ec (byte): action-0 volley shot countdown (seed 5, --per zz_0092534_). */
  wsVolleyCount6ec?: number;
  /** +0x745 (byte): action-0 charged latch (set when +0x5d4 & 0x40). */
  wsCharged745?: number;
  /** +0x746 (byte): action-1 X-special charged latch (set when +0x5d4 & 0x40). */
  wsCharged746?: number;
  /** +0x1b01 (byte): action-1 dash ph2->3 advance gate. */
  wsDashGate1b01?: number;
  /** +0x1d9 (byte): action-1 dash ph2 input latch (sets +0x541 = 0xff). */
  wsFlag1d9?: number;
  /** +0x3c (float): action-1 X-special dive speed magnitude (DAT_8033ecc8[borgIdx]). */
  wsDiveSpeed3c?: number;
  /** +0x760 (float): action-1 X-special reference speed for the fast-drag branch. */
  wsSpeed760?: number;
  /** +0x5d4: live edge input word. */
  inputEdge5d4?: number;
  /** +0x5d8: live held input word. */
  inputHeld5d8?: number;
}

type WingActor = RomActor & WingSoldierScratch;

function scratchOf(actor: RomActor): WingActor {
  return actor as WingActor;
}

const TAU = Math.PI * 2;
function bamRad(bam: number): number {
  return bam * TAU / 0x10000;
}

// ----------------------------------------------------------------------------
// Best-effort physics bridges. The full FUN_80067310 integrator and zz_00677b0_
// collision stepper own clamp/collision behavior not surfaced on RomActor; the
// documented scalar projection (actor.ts FUN_80067310 comment) is applied so observable
// motion is faithful. Phase transitions never depend on these.
// ----------------------------------------------------------------------------

/** Best-effort port of FUN_80067310(rate, actor, yaw) — scalar-speed integrator
 *  (chunk_0008.c:3794-3828). TODO: maxHSpeed/maxRise/maxFall clamps require the full
 *  physics runtime. */
function integrateMotion(actor: RomActor, rate: number, yaw: number): void {
  const ts = actor.timescale * actor.tierScale;
  const yr = bamRad(yaw);
  actor.pos.x += ts * rate * actor.hSpeed * Math.cos(yr);
  actor.pos.y += ts * rate * actor.yVel;
  actor.pos.z += ts * rate * actor.hSpeed * Math.sin(yr);
  actor.hSpeed -= actor.hDecel * ts;
}

/** Best-effort port of zz_00677b0_(actor) — collision/step-height probe. Returns the
 *  scratch grounded flag (0 = air, 1 = grounded) which selects the land transition. */
function collisionStep(actor: RomActor): number {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  return grounded === true ? 1 : 0;
}

/** Port of zz_006ed8c_(factor, actor) — per-frame velocity drag (hSpeed/yVel *= factor). */
function applyVelocityDrag(actor: RomActor, factor: number): void {
  actor.hSpeed *= factor;
  actor.yVel *= factor;
}

// ----------------------------------------------------------------------------
// Action-exit helper. The wing family exits inline (NOT via zz_006a53c_/cue 0x1b):
// clear +0x73f, strip +0x5e0 action bits, then a LAND transition selected by the
// collision probe (zz_006a4f4_ air / zz_006a474_ ground / zz_006a5a4_ air-variant). The
// land selectors are renderer-side next-state machines (TODO). seedHandlerTimer ports
// the action-0 ph2-abort path that writes +0x694 = +0x558 + dt.
// ----------------------------------------------------------------------------
function exitAction(actor: WingActor, seedHandlerTimer: boolean): number {
  if (seedHandlerTimer) {
    actor.stateTimer = actor.handlerTimer + actor.dt; // +0x694 = +0x558 + dt
  }
  actor.housekeeping73f = 0; // +0x73f = 0
  actor.controlWord = actor.controlWord & ~WING_SOLDIER.ACTION_MODE_BITS; // +0x5e0 &= ~3
  const grounded = collisionStep(actor); // zz_00677b0_
  // TODO: zz_006a4f4_ (air) / zz_006a474_ (ground) / zz_006a5a4_ (air-variant) land
  // transition — unsurfaced next-state selectors (same gap as phoenix-dragon).
  return grounded;
}

// ----------------------------------------------------------------------------
// zz_0092480_ — action-0 shared per-frame preamble (chunk_0014.c:2259). Drains the
// dive timer +0x560, runs the dual-axis aim, and computes the cosmetic stream-slot
// class +0x6eb from the yaw error. Runs every frame before the +0x540 phase dispatch.
// ----------------------------------------------------------------------------
function action0Preamble(actor: WingActor): void {
  actor.wsDiveTimer560 = (actor.wsDiveTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  // zz_006d0dc_(actor, 0x81, 0) — aim yaw; +0x54a = settled ? 0 : 1 (the ROM stores the
  // ready word; ph1 polls +0x54a != 0 for "not yet settled").
  const ready = stepTargetYaw(actor, WING_SOLDIER.AIM_YAW, 0);
  actor.wsAimFlag54a = ready ? 0 : 1; // +0x54a
  stepPartTargetPitch(actor, WING_SOLDIER.AIM_PART_PITCH); // zz_006e1ac_(actor, 0xc1, 1)
  // zz_0066ac0_(actor, 0) target-visibility check -> +0x6eb stream-slot class.
  const hasTarget = actor.visibilityTarget !== null ? 1 : 0; // iVar1
  const err = hasTarget !== 0 ? -1 : 0; // iVar3
  if (err !== 0) {
    // ((short)+0x5aa + 0x2000) >> 14) & 3) + 1 — buckets the yaw error into 4 slots.
    actor.wsStreamClass6eb = ((((actor.turnErrorYaw + 0x2000) >>> 14) & 3) + 1) & 0xff;
  } else {
    actor.wsStreamClass6eb = 0;
  }
}

// ----------------------------------------------------------------------------
// zz_0092518_ (chunk_0014.c:2288) — action-0 volley (re)arm. Resets the charged latch,
// seeds the volley counter (+0x6ec = 5) and the handler timer (+0x558 = 60.0).
// ----------------------------------------------------------------------------
function armVolley(actor: WingActor): void {
  actor.wsCharged745 = 0; // +0x745 = 0
  actor.wsVolleyCount6ec = WING_SOLDIER.VOLLEY_SHOT_CAP; // +0x6ec = 5
  actor.handlerTimer = WING_SOLDIER.A0_HANDLER_TIMER_SEED; // +0x558 = 60.0
}

// ----------------------------------------------------------------------------
// zz_0092534_ (chunk_0014.c:2304) — action-0 per-shot fire. Decrements the volley
// counter, reseeds the inter-shot timer (+0x558 = 4.0), clears latches, then
// ammo-gates (zz_006dbe0_(actor, 0, 1, 1) — consume) the projectile spawn
// zz_0082824_(actor, 10).
// ----------------------------------------------------------------------------
function fireVolleyShot(actor: WingActor, ctx: StreamContext): void {
  actor.wsVolleyCount6ec = (actor.wsVolleyCount6ec ?? 0) - 1; // +0x6ec -= 1
  actor.handlerTimer = WING_SOLDIER.A0_SHOT_INTERVAL; // +0x558 = 4.0 (FLOAT_80437ca0)
  actor.wsCharged745 = 0; // +0x745 = 0
  actor.cmdChargedRanged = 0; // +0x587 = 0
  if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(actor, 0, 1, 1)
    ctx.onFamilyProjectile?.(actor, SHOT_HELPER, WING_SOLDIER.VOLLEY_SHOT_TYPE); // zz_0082824_(10)
  }
}

// ============================================================================
// Action 0 — hover volley (table @0x802db468, 4 phases). Handler zz_0091e34_.
//   ph0 FUN_80091f2c: setup — +0x540=1, +0x560=30.0, +0x54c=0, armVolley, startStream.
//   ph1 FUN_80091f94: wait   — advance when +0x560 < 0.0 OR (wallContact && aim unsettled);
//                             on advance fire shot 1 (fireVolleyShot), +0x54c=5, startStream.
//   ph2 FUN_80092030: volley — drain +0x558; when <= 0.0 either fire next shot
//                             (fireVolleyShot while +0x6ec >= 1) or advance to ph3
//                             (+0x55c=60.0, +0x54c=10). Abort on +0x5d8 & 0xf0.
//   ph3 FUN_80092174: cooldown — drain +0x55c; if charged (+0x745) AND ammo available
//                             (non-consuming gate) loop back to ph2 (re-arm + fire);
//                             else exit when +0x55c <= 0.0 OR wallContact OR abort.
// ============================================================================
function action0(actor: WingActor, ctx: StreamContext): void {
  action0Preamble(actor); // zz_0092480_ (drains +0x560, aim)
  // The +0x544/+0x545 pose/anim sub-tables (PTR_FUN_80433968/70) are upper-body
  // animation state machines — best-effort no-op (do not affect combat transitions).
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80091f2c — setup
      actor.fbPhaseSlots[0] = 1; // +0x540 = 1
      actor.wsDiveTimer560 = WING_SOLDIER.A0_DIVE_TIMER_SEED; // +0x560 = 30.0
      actor.wsStreamSlot54c = 0; // +0x54c = 0
      armVolley(actor); // zz_0092518_
      // zz_004beb8_(-1, actor, 1, 2, +0x6ea, 4, 2) — startStream (no-op without banks).
      return;
    }
    case 1: { // FUN_80091f94 — wait
      actor.wsStreamSlot54c = 0; // +0x54c = 0
      if ((actor.wsDiveTimer560 ?? 0) < WING_SOLDIER.THRESHOLD ||
          (actor.wallContact !== 0 && (actor.wsAimFlag54a ?? 0) !== 0)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        fireVolleyShot(actor, ctx); // zz_0092534_ — shot 1 (+0x6ec 5->4)
        actor.wsStreamSlot54c = 5; // +0x54c = 5
        // zz_004beb8_(-1, actor, 1, 2, +0x6ea+5, -1, -1) — startStream (no-op).
      }
      return;
    }
    case 2: { // FUN_80092030 — volley
      if (((actor.inputEdge5d4 ?? 0) & WING_SOLDIER.CHARGE_INPUT_BIT) !== 0) {
        actor.wsCharged745 = 1; // +0x745 = 1
      }
      actor.wsStreamSlot54c = 5; // +0x54c = 5
      if (actor.handlerTimer <= WING_SOLDIER.THRESHOLD) { // +0x558 <= 0.0
        if ((actor.wsVolleyCount6ec ?? 0) < 1) {
          // Volley exhausted -> advance to cooldown.
          actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
          actor.wsCooldown55c = WING_SOLDIER.A0_HANDLER_TIMER_SEED; // +0x55c = 60.0
          actor.wsStreamSlot54c = 10; // +0x54c = 10
          // zz_004beb8_(-1, actor, 7, 2, +0x6ea+10, 4, 2) — startStream (no-op).
        } else {
          // zz_006bf80_(actor) — target re-acquire (renderer-side, TODO no-op).
          fireVolleyShot(actor, ctx); // zz_0092534_
          // zz_004beb8_(-1, actor, 1, 2, +0x6ea+5, -1, -1) — startStream (no-op).
        }
      } else {
        actor.handlerTimer -= actor.dt; // +0x558 -= dt
      }
      if (((actor.inputHeld5d8 ?? 0) & WING_SOLDIER.ABORT_INPUT_MASK) !== 0) {
        // Abort: clear + strip + land transition + seed +0x694 = +0x558 + dt.
        exitAction(actor, true);
      }
      return;
    }
    case 3: { // FUN_80092174 — cooldown
      if (((actor.inputEdge5d4 ?? 0) & WING_SOLDIER.CHARGE_INPUT_BIT) !== 0) {
        actor.wsCharged745 = 1; // +0x745 = 1
      }
      actor.wsStreamSlot54c = 10; // +0x54c = 10
      // Charged re-volley: non-consuming ammo gate zz_006dbe0_(actor, 0, 1, 0).
      if ((actor.wsCharged745 ?? 0) !== 0 && allocateWeapon(actor, ctx, 0, 1, false)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- (back to ph2)
        armVolley(actor); // zz_0092518_
        // zz_006bf80_(actor) — target re-acquire (TODO no-op).
        fireVolleyShot(actor, ctx); // zz_0092534_
        // zz_004beb8_(-1, actor, 1, 2, +0x6ea+5, -1, -1) — startStream (no-op).
        return;
      }
      // Hold while the cooldown timer drains and no abort/contact.
      if (((actor.inputHeld5d8 ?? 0) & WING_SOLDIER.ABORT_INPUT_MASK) === 0 &&
          (actor.wsCooldown55c = (actor.wsCooldown55c ?? 0) - actor.dt, // +0x55c -= dt
            (actor.wsCooldown55c ?? 0) > WING_SOLDIER.THRESHOLD) &&
          actor.wallContact === 0) {
        return;
      }
      exitAction(actor, false); // clear + strip + land transition
      return;
    }
    default: return;
  }
}

// ============================================================================
// Action 1 variant 1 — WING SOLDIER steer dash (table @0x802db48c, 4 phases).
//   Handler FUN_8009263c clears +0xcc when +0x541 != 0, then dispatches +0x540.
//   ph0 FUN_8009268c: setup — +0x540++, +0x54e=+0x5ae, +0x6ea=3, speed gate, +0x558=60,
//                     aim 0xc0, motion = (pos - target)*0.95, pos += motion, collision,
//                     +0x6ea++, startStream, +0x80c=0.
//   ph1 FUN_800927c0: wait — motion*0.95 + pos + collision + aim; drain +0x558; advance
//                     when <= 0.0 OR aim-ready (0xc0); reseed +0x558=60.
//   ph2 FUN_8009287c: dash — hSpeed/yVel = 30 * trig(steerYaw); integrate; collision;
//                     drain +0x558; when <= 0.0 AND +0x1b01 -> +0x540++, reseed 60.
//   ph3 FUN_80092998: exit — steerYaw *= 0.9; drag 0.9; integrate; collision; on
//                     wallContact exit (clear + strip + land transition); afterimage.
// ============================================================================
function action1Dash(actor: WingActor, ctx: StreamContext): void {
  // FUN_8009263c preamble: clear +0xcc (target pointer) when +0x541 != 0.
  if ((actor.fbPhaseSlots[1] ?? 0) !== 0) {
    actor.visibilityTarget = null; // +0xcc = 0
  }
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_8009268c — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wsDiveYaw54e = actor.lockYaw; // +0x54e = +0x5ae (s16)
      actor.wsStreamSlot6ea = 3; // +0x6ea = 3
      // FUN_80066838(actionSpeedRows[prevActionIndex % 3], actor) — speed gate. TODO:
      // unsurfaced speed-vs-threshold query; the slow branch arms +0x541=1, +0xcc=0,
      // +0x5ac=+0x5ae. The common case (speed >= 1) skips it. Modeled as a no-op.
      actor.handlerTimer = WING_SOLDIER.A0_HANDLER_TIMER_SEED; // +0x558 = 60.0 (FLOAT_80437c94)
      stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true); // zz_006d144_(actor, 0xc0)
      stepPartTargetPitch(actor, WING_SOLDIER.AIM_DIVE); // zz_006e1ac_(actor, 0xc0, 1)
      // motion = (pos - targetCache5e8) * 0.95; pos += motion (gnt4_PSVECSubtract +
      // PSQUATScale_bl(0.95) + PSVECAdd_bl).
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * WING_SOLDIER.DASH_MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * WING_SOLDIER.DASH_MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * WING_SOLDIER.DASH_MOTION_SCALE;
      actor.pos.x += actor.motion.x;
      actor.pos.y += actor.motion.y;
      actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_00677b0_
      actor.wsStreamSlot6ea = (actor.wsStreamSlot6ea ?? 0) + 1; // +0x6ea++
      // zz_004beb8_(-1, actor, 0xf, 3, +0x6ea, -1, -1) — startStream (no-op).
      actor.accumulator80c = WING_SOLDIER.THRESHOLD; // +0x80c = 0.0
      // zz_0092dcc_(actor, 0) — unknown VFX/sound helper (TODO, not ported).
      void ctx;
      return;
    }
    case 1: { // FUN_800927c0 — wait
      if (actor.streamHold1b03 !== 0) {
        // zz_004cd24_(actor, 0xf) — tickStream (no-op without banks).
      }
      actor.motion.x *= WING_SOLDIER.DASH_MOTION_SCALE; // motion *= 0.95
      actor.motion.y *= WING_SOLDIER.DASH_MOTION_SCALE;
      actor.motion.z *= WING_SOLDIER.DASH_MOTION_SCALE;
      actor.pos.x += actor.motion.x;
      actor.pos.y += actor.motion.y;
      actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_00677b0_
      stepPartTargetPitch(actor, WING_SOLDIER.AIM_DIVE); // zz_006e1ac_(0xc0, 1)
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= WING_SOLDIER.THRESHOLD ||
          stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true)) { // zz_006d144_(0xc0) != 0
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.handlerTimer = WING_SOLDIER.A0_HANDLER_TIMER_SEED; // +0x558 = 60.0
      }
      return;
    }
    case 2: { // FUN_8009287c — steer dash
      if ((actor.wsFlag1d9 ?? 0) !== 0) {
        actor.fbPhaseSlots[1] = 0xff; // +0x541 = 0xff
      }
      stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, WING_SOLDIER.AIM_DIVE); // zz_006e1ac_(0xc0, 1)
      // hSpeed = 30 * cos(steerYaw); yVel = 30 * -sin(steerYaw) (FLOAT_80437c90 x trig).
      const steer = actor.steerYaw; // +0x18da
      actor.hSpeed = WING_SOLDIER.A0_DIVE_TIMER_SEED * Math.cos(bamRad(steer));
      actor.yVel = WING_SOLDIER.A0_DIVE_TIMER_SEED * -Math.sin(bamRad(steer));
      integrateMotion(actor, WING_SOLDIER.INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      collisionStep(actor); // zz_00677b0_
      // zz_004cd24_(actor, 0xf) — tickStream (no-op).
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= WING_SOLDIER.THRESHOLD) {
        actor.handlerTimer = WING_SOLDIER.THRESHOLD; // +0x558 = 0.0
        if ((actor.wsDashGate1b01 ?? 0) !== 0) { // +0x1b01 != 0
          actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = desc +0x6c
          actor.wsStreamSlot6ea = (actor.wsStreamSlot6ea ?? 0) + 1; // +0x6ea++
          // zz_004beb8_(-1, actor, 0xf, 3, +0x6ea, -1, -1) — startStream (no-op).
        }
      }
      return;
    }
    case 3: { // FUN_80092998 — exit
      // steerYaw *= 0.9 (the GCC int->double coercion base is DOUBLE_80437c78, the
      // 0x43300000 sentinel; the real factor is FLOAT_80437c70 = 0.9).
      actor.steerYaw = Math.trunc(actor.steerYaw * WING_SOLDIER.DASH_DECAY);
      // zz_004cd24_(actor, 0xf) — tickStream (no-op).
      applyVelocityDrag(actor, WING_SOLDIER.DASH_DECAY); // zz_006ed8c_(FLOAT_80437c70=0.9)
      integrateMotion(actor, WING_SOLDIER.INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      collisionStep(actor); // zz_00677b0_
      if (actor.wallContact !== 0) { // +0x1cee != 0
        exitAction(actor, false); // clear + strip + land transition (air/ground variant)
      }
      // zz_00b22f4_(actor) — afterimage step (omitted; renderer-side emission).
      return;
    }
    default: return;
  }
}

// ============================================================================
// Action 1 variant 0 — shared X-special aimed dive (table @0x8033ecb8, 4 phases).
//   ph0 FUN_80147e90: setup — +0x540++, +0x746=0, +0x6ea=slot, speed gate, +0x558=60,
//                     +0x54e=0, +0x3c=DAT_8033ecc8[borgIdx], +0x6ea++, startStream.
//   ph1 FUN_80147f7c: wait — tickStream; drain +0x558; advance when <= 0.0 OR aim-ready;
//                     reseed +0x558=20, FUN_80148288 (speed build), afterimage arm.
//   ph2 FUN_80148014: dive — aim + part-pitch; hSpeed/yVel = +0x38 * trig(+0x54e);
//                     integrate; collision; drain +0x558; advance when <= 0.0 OR
//                     speed-threshold met (FUN_800668cc).
//   ph3 FUN_801480fc: exit — charged latch; tickStream; re-dive branch (+0x540-- when
//                     contact + charged); drag (0.9, or 0.5 when fast); integrate;
//                     collision; on wallContact exit.
// ============================================================================
function action1XSpecial(actor: WingActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80147e90 — setup (param_2 = initial stream slot)
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wsCharged746 = 0; // +0x746 = 0
      actor.wsStreamSlot6ea = 0; // +0x6ea = param_2 (default 0)
      // FUN_80066838 speed gate — TODO unsurfaced; slow branch arms +0x541/+0xcc/+0x5ae.
      actor.handlerTimer = WING_SOLDIER.XSPEC_TIMER_SEED; // +0x558 = 60.0 (FLOAT_8043a328)
      actor.wsDiveYaw54e = 0; // +0x54e = 0
      // +0x3c = DAT_8033ecc8[borgIndex +0x3e9] (per-borg dive speed; unsurfaced -> 0).
      actor.wsDiveSpeed3c = 0;
      actor.wsStreamSlot6ea = (actor.wsStreamSlot6ea ?? 0) + 1; // +0x6ea++
      // zz_004beb8_(-1, actor, 0xf, 3, +0x6ea, 5, 1) — startStream (no-op).
      void ctx;
      return;
    }
    case 1: { // FUN_80147f7c — wait
      if (actor.streamHold1b03 !== 0) {
        // zz_004cd24_(actor, 0xf) — tickStream (no-op).
      }
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= WING_SOLDIER.XSPEC_THRESHOLD ||
          stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true)) { // zz_006d144_(0xc0)
        actor.handlerTimer = WING_SOLDIER.XSPEC_RESEED; // +0x558 = 20.0 (FLOAT_8043a334)
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        xspecBuildSpeed(actor); // FUN_80148288 — build motion speed from +0x3c
        // zz_00b2190_(actor, 0) — afterimage sample reset (renderer-side, omitted).
      }
      return;
    }
    case 2: { // FUN_80148014 — dive
      stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true); // zz_006d144_(0xc0)
      // zz_006e514_(actor, 0xc0, &+0x54e) — part-pitch converge +0x54e (best-effort via
      // the part-pitch channel; the +0x54e yaw is steered by the dive pitch instead).
      stepPartTargetPitch(actor, WING_SOLDIER.AIM_DIVE);
      // hSpeed = motion.x * cos(+0x54e); yVel = motion.x * -sin(+0x54e).
      const mag = actor.motion.x; // +0x38 magnitude (set by FUN_80148288)
      actor.hSpeed = mag * Math.cos(bamRad(actor.wsDiveYaw54e ?? 0));
      actor.yVel = mag * -Math.sin(bamRad(actor.wsDiveYaw54e ?? 0));
      integrateMotion(actor, WING_SOLDIER.XSPEC_INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      collisionStep(actor); // zz_00677b0_
      if (actor.contactP0 === 0 || actor.streamHold1b03 !== 0) {
        // zz_004cd24_(actor, 0xf) — tickStream (no-op).
      }
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      // FUN_800668cc(+0x3c, actor) — speed-threshold met check (TODO unsurfaced -> 0,
      // so the timer gates the advance).
      if (actor.handlerTimer <= WING_SOLDIER.XSPEC_THRESHOLD) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      }
      return;
    }
    case 3: { // FUN_801480fc — exit
      if (((actor.inputEdge5d4 ?? 0) & WING_SOLDIER.CHARGE_INPUT_BIT) !== 0) {
        actor.wsCharged746 = 1; // +0x746 = 1
      }
      // zz_004cd24_(actor, 0xf) — tickStream (no-op).
      if ((actor.fbPhaseSlots[1] ?? 0) !== 0) {
        actor.visibilityTarget = null; // +0xcc = 0 (when +0x541 != 0)
      }
      // Re-dive branch: contact (+0x1cf0 < 0) AND charged -> back to ph2.
      if (actor.contactP1 < 0 && (actor.wsCharged746 ?? 0) !== 0) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540--
        actor.wsCharged746 = 0; // +0x746 = 0
        actor.handlerTimer = WING_SOLDIER.XSPEC_RESEED; // +0x558 = 20.0
        actor.wsStreamSlot6ea = (actor.wsStreamSlot6ea ?? 0) + 1; // +0x6ea++
        // zz_004beb8_(-1, actor, 0xf, 3, +0x6ea, -1, -1) — startStream (no-op).
        xspecBuildSpeed(actor); // FUN_80148288
        // zz_00b2190_(actor, 0) — afterimage reset (omitted).
        return;
      }
      // Steer/aim upkeep when the stream authoured +0x1d10/+0x1d0f bytes.
      if (actor.faceGate1d10 !== 0) {
        stepTargetYaw(actor, WING_SOLDIER.AIM_DIVE, 0, true); // zz_006d144_(0xc0)
        stepPartTargetPitch(actor, WING_SOLDIER.AIM_DIVE); // zz_006e514_
      }
      if (actor.dashStrength1d0f !== 0) {
        xspecBuildSpeed(actor); // FUN_80148288 (re-build when dash-strength set)
      }
      applyVelocityDrag(actor, WING_SOLDIER.XSPEC_DRAG); // zz_006ed8c_(FLOAT_8043a33c=0.9)
      if ((actor.wsSpeed760 ?? 0) < (actor.wsDiveSpeed3c ?? 0)) {
        applyVelocityDrag(actor, WING_SOLDIER.XSPEC_DRAG_FAST); // zz_006ed8c_(FLOAT_8043a340=0.5)
      }
      integrateMotion(actor, WING_SOLDIER.XSPEC_INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      collisionStep(actor); // zz_00677b0_
      if (actor.wallContact !== 0) { // +0x1cee != 0
        exitAction(actor, false); // clear + strip + land transition
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// FUN_80148288 (chunk_0038.c:1598) — X-special speed build. motion.x (+0x38) =
// speed / 20.0 (clamped to descriptor +0x54), then hSpeed/yVel = motion.x * trig(+0x54e).
// ----------------------------------------------------------------------------
function xspecBuildSpeed(actor: WingActor): void {
  let speed: number;
  if (actor.visibilityTarget === null) { // +0xcc == 0
    speed = actor.actionSpeedRows[(actor.prevActionIndex % 3 + 3) % 3] ?? 0; // row [+0x584%3]
  } else {
    // +0x760 * (double)(signed char)+0x1d0f * 0.0625 (FLOAT_8043a344); the int->double
    // coercion uses the 0x43300000 sentinel DOUBLE_8043a348 (== GCC (double)byte cast).
    speed = (actor.wsSpeed760 ?? 0) * actor.dashStrength1d0f * 0.0625;
  }
  let motion = speed / WING_SOLDIER.XSPEC_RESEED; // motion.x = speed / 20.0 (FLOAT_8043a334)
  // desc +0x54 max-motion clamp not surfaced on RomDescriptor (TODO); motion applied as-is.
  actor.motion.x = motion; // +0x38
  actor.hSpeed = motion * Math.cos(bamRad(actor.wsDiveYaw54e ?? 0));
  actor.yVel = motion * -Math.sin(bamRad(actor.wsDiveYaw54e ?? 0));
  actor.dashStrength1d0f = 0; // +0x1d0f = 0
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_80091a74 indexes PTR_FUN_802db43c[+0x580] (actionIndex).
// Action 0 -> zz_0091e34_ (hover volley). Action 1 -> variant-dispatched dive
// (variant 0 = shared X-special @0x8033ecb8, variant != 0 = WING SOLDIER dash
// @0x802db48c). Other indices fall through.
// ----------------------------------------------------------------------------
export function createWingSoldierRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: action0(actor, ctx); return;
      case 1:
        if (actor.variantIndex === 0) {
          action1XSpecial(actor, ctx); // table @0x8033ecb8
        } else {
          action1Dash(actor, ctx); // table @0x802db48c
        }
        return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned WING SOLDIER (pl0a00). Stamps the borg number and
 *  wires the bespoke action dispatcher. */
export function configureWingSoldierFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = WING_SOLDIER_BORG_NUMBERS.pl0a00 ?? 0xa00;
  actor.rootAction = createWingSoldierRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirrors rom.selfcheck.ts style. Covers action-0 phase transitions,
// the 5-shot volley spawn (zz_0082824_ type 10), the ammo-gate (consume + non-consume),
// the ph3 charged re-volley loop, and action-1 dash phase transitions + exit.
// ============================================================================
export function runWingSoldierSelfTests(assert: (cond: boolean, msg: string) => void): void {
  type Shot = { addr: number; type: number };

  // --- action 0: 4-phase hover volley, 5 shots, ph0 -> ph1 -> ph2 -> ph3 -> exit. ---
  {
    const shots: Shot[] = [];
    let allocCalls = 0;
    const sctx: StreamContext = {
      onAllocateResource: (_a, _slot, _count, mode) => { allocCalls += 1; return mode === 1 ? true : true; },
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureWingSoldierFamily(a, sctx);
    assert(a.borgNumber === 0xa00, "pl0a00 borgNumber stamped 0xa00");
    assert(a.rootAction !== null, "wing-soldier bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;

    // ph0 setup: +0x540 -> 1, +0x560 = 30, volley armed (+0x6ec = 5, +0x558 = 60).
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action 0 ph0 advances +0x540 0 -> 1");
    const s = a as RomActor & WingSoldierScratch;
    assert(s.wsDiveTimer560 === WING_SOLDIER.A0_DIVE_TIMER_SEED, "action 0 ph0 seeds +0x560 = 30.0");
    assert(s.wsVolleyCount6ec === WING_SOLDIER.VOLLEY_SHOT_CAP, "action 0 ph0 arms volley +0x6ec = 5");
    assert(a.handlerTimer === WING_SOLDIER.A0_HANDLER_TIMER_SEED, "action 0 ph0 seeds +0x558 = 60.0");

    // ph1 wait: drive the dive timer negative to force the advance (skips ~30 frames).
    s.wsDiveTimer560 = -1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action 0 ph1 advances 1 -> 2 when +0x560 < 0.0");
    assert(s.wsVolleyCount6ec === 4, "action 0 ph1 exit fired shot 1 (+0x6ec 5 -> 4)");
    assert(shots.length === 1 && shots[0]!.addr === SHOT_HELPER && shots[0]!.type === 10,
      `action 0 ph1 spawns zz_0082824_(10) (got ${JSON.stringify(shots)})`);

    // ph2 volley: +0x558 starts at 4.0 (reseeded by fireVolleyShot). Drive the remaining
    // 4 shots (+0x6ec 4 -> 0); each shot needs +0x558 to drain to <= 0 first, then one
    // more frame with +0x6ec == 0 advances to ph3.
    for (let i = 0; i < 20 && a.fbPhaseSlots[0] === 2; i += 1) {
      a.handlerTimer = 0; // force the <= 0.0 fire branch each frame
      root(a);
    }
    assert(a.fbPhaseSlots[0] === 3, "action 0 ph2 advances 2 -> 3 when volley exhausted");
    assert(s.wsVolleyCount6ec === 0, "action 0 ph2 drained volley +0x6ec to 0");
    assert(shots.length === 5, `action 0 volley fired 5 shots total (got ${shots.length})`);
    assert(shots.every((sp) => sp.addr === SHOT_HELPER && sp.type === 10),
      "all 5 volley shots route zz_0082824_(10)");
    assert(s.wsCooldown55c === WING_SOLDIER.A0_HANDLER_TIMER_SEED, "action 0 ph2->3 seeds +0x55c = 60.0");

    // ph3 cooldown: drain +0x55c to <= 0 then exit (clear +0x73f, strip +0x5e0).
    a.controlWord = 0x3; a.housekeeping73f = 1;
    s.wsCooldown55c = 0;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action 0 ph3 exits when +0x55c <= 0.0 (clears +0x73f, strips +0x5e0)");
    void allocCalls;
  }

  // --- action 0 ammo-gate failure: zz_006dbe0_ -> false suppresses the spawn but the
  //     volley counter still decrements and the phase still advances. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureWingSoldierFamily(a, sctx);
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0
    (a as RomActor & WingSoldierScratch).wsDiveTimer560 = -1;
    a.rootAction!(a); // ph1 -> ph2 (fireVolleyShot, ammo denied)
    assert(a.fbPhaseSlots[0] === 2, "ammo-fail still advances ph1 -> ph2");
    assert(shots.length === 0, "ammo-fail suppresses the volley spawn");
    assert((a as RomActor & WingSoldierScratch).wsVolleyCount6ec === 4,
      "ammo-fail still decrements volley +0x6ec (5 -> 4)");
  }

  // --- action 0 ph3 charged re-volley loop: charged (+0x745) + non-consuming ammo
  //     gate -> +0x540-- back to ph2, re-arm (+0x6ec = 5), fire shot 1 again. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, _slot, _count, mode) => mode === 0 ? true : true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureWingSoldierFamily(a, sctx);
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 3; // start in ph3
    a.inputEdge5d4 = WING_SOLDIER.CHARGE_INPUT_BIT; // +0x5d4 & 0x40 -> +0x745 = 1
    const s = a as RomActor & WingSoldierScratch;
    s.wsCooldown55c = 60; // not exhausted
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "charged + ammo -> ph3 loops back to ph2 (+0x540--)");
    assert(s.wsVolleyCount6ec === WING_SOLDIER.VOLLEY_SHOT_CAP - 1,
      "re-volley re-arms +0x6ec = 5 then fires shot 1 (-> 4)");
    assert(shots.length === 1, "re-volley fires shot 1 (zz_0082824_(10))");
  }

  // --- action 0 ph3 charged ammo-fail: non-consuming gate returns false -> no loop,
  //     falls through to the cooldown drain (holds, no exit while +0x55c > 0). ---
  {
    const sctx: StreamContext = {
      onAllocateResource: (_a, _slot, _count, mode) => mode === 0 ? false : false,
      onFamilyProjectile: () => {},
    };
    const a = scratchOf(createRomActor());
    configureWingSoldierFamily(a, sctx);
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 3;
    a.inputEdge5d4 = WING_SOLDIER.CHARGE_INPUT_BIT; // charged
    a.housekeeping73f = 1; a.controlWord = 0x3; // should NOT be cleared (held, no exit)
    const s = a as RomActor & WingSoldierScratch;
    s.wsCooldown55c = 5;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3,
      "charged ammo-fail holds in ph3 (no loop-back when gate returns false)");
    assert(a.housekeeping73f === 1 && (a.controlWord & 0x3) === 0x3,
      "charged ammo-fail does NOT exit while +0x55c > 0 (+0x73f/+0x5e0 untouched)");
  }

  // --- action 1 (dash, variant 1): 4-phase steer dash, timer-driven transitions. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureWingSoldierFamily(a, sctx);
    a.actionIndex = 1; a.variantIndex = 1; // -> action1Dash (table @0x802db48c)
    a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "dash ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === WING_SOLDIER.A0_HANDLER_TIMER_SEED, "dash ph0 seeds +0x558 = 60.0");
    const s = a as RomActor & WingSoldierScratch;
    assert(s.wsDiveYaw54e === a.lockYaw, "dash ph0 latches +0x54e = +0x5ae (lockYaw)");

    // ph1 wait: drain +0x558 to <= 0 to advance.
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "dash ph1 advances 1 -> 2 when +0x558 <= 0.0");
    assert(a.handlerTimer === WING_SOLDIER.A0_HANDLER_TIMER_SEED, "dash ph1 reseeds +0x558 = 60.0");

    // ph2 dash: drain +0x558 to <= 0 AND +0x1b01 gate -> advance.
    a.handlerTimer = 0; a.steerYaw = 0;
    s.wsDashGate1b01 = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3, "dash ph2 advances 2 -> 3 when +0x558 <= 0 AND +0x1b01");

    // ph3 exit: wallContact -> clear + strip + (land transition TODO).
    a.controlWord = 0x3; a.housekeeping73f = 1; a.wallContact = 1;
    a.rootAction!(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "dash ph3 exits on wallContact (clears +0x73f, strips +0x5e0)");
  }

  // --- action 1 (X-special, variant 0): ph0 setup + ph1 timer advance. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureWingSoldierFamily(a, sctx);
    a.actionIndex = 1; a.variantIndex = 0; // -> action1XSpecial (table @0x8033ecb8)
    a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "X-special ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === WING_SOLDIER.XSPEC_TIMER_SEED, "X-special ph0 seeds +0x558 = 60.0");
    const s = a as RomActor & WingSoldierScratch;
    assert(s.wsCharged746 === 0, "X-special ph0 clears +0x746");
    // ph1 wait: drain +0x558 to <= 0 -> advance, reseed 20.0.
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "X-special ph1 advances 1 -> 2 when +0x558 <= 0.0");
    assert(a.handlerTimer === WING_SOLDIER.XSPEC_RESEED, "X-special ph1 reseeds +0x558 = 20.0");
  }
}

// ----------------------------------------------------------------------------
// Named const exports for spawner addresses + floats (audit surface).
// ----------------------------------------------------------------------------
export const WING_SOLDIER_CONSTANTS = WING_SOLDIER;
export const WING_SOLDIER_SHOT_HELPER = SHOT_HELPER;
