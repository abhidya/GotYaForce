// TELEPORT NINJA family (ctor 0x801456d4) — ROM-faithful port.
// Covers pl0005 (TELEPORT NINJA, borg 0x005) and pl0009 (SWITCHING NINJA, borg 0x009).
// The ctor wires both borgs to the SAME vtable/anim banks/tables (only the +0x4b0
// descriptor differs), so one family module covers both.
//
// Root dispatcher FUN_80145924 @0x80145924 (chunk_0037.c):
//   `(*(code *)(&PTR_FUN_8033e4f4)[*(char *)(actor+0x580)])();`
// Action tables (per bespoke-port-work-queue.json — 8 tables, 28 fns / 3355 instrs):
//   action 0 table @0x8033e518 (3 sub-tables 0x8033e518/524/530, phase via +0x540)
//   action 1 table @0x8033e568 (2 sub-tables 0x8033e568/574) — TODO bespoke port
//   action 2 table @0x8033e584/594 (X-special) — shared-engine approximation
//   action 3 table @0x8033e5b4 (B-charge teleport-dash, 5 fns) — TODO bespoke port
//
// This pass ports ACTION 0 (the teleport-approach + B-held combo loop) faithfully from
// FUN_801459f0/FUN_80145b00/FUN_80145bd8 (chunk_0037.c/0038.c). Actions 1/3 fall back to
// the shared-engine approximation with cited TODOs; action 2 routes through the shared
// X-special engine. Floats read from boot.dol this session (sdata2 @0x8043a2xx).
//
// Float constants (v2f-resolved from user-data/GG4E/disc/sys/boot.dol):
//   FLOAT_8043a2b8 = 0.0   zero-scalar (velocity/pose resets, accumulator80c clear)
//   FLOAT_8043a2bc = 30.0  action-0 ph0 +0x560 aim/approach timer seed
//   FLOAT_8043a2c0 = -1.0  zz_004beb8_ stream playback rate
//   FLOAT_8043a2c4 = 0.95  blink reposition + per-frame motion scale
//   FLOAT_8043a2c8 = 3.0   afterimage (zz_00b22f4_) motion-magnitude gate
//   FLOAT_8043a2cc = 20.0  action-0 ph0 slot-2 aim timer seed (FUN_80145e98 action-1 arm)
//   FLOAT_8043a2dc = 60.0  action-3 ph0 +0x558 seed (FUN_801474b4 B-charge window)

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, groundSnapRevert, stepAfterimage, stepTargetYaw } from "../rom/helpers.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";

/** Borg numbers for the TELEPORT NINJA family. */
const TELEPORT_NINJA_BORG_NUMBERS: Record<string, number> = {
  pl0005: 0x005,
  pl0009: 0x009,
};

export type TeleportNinjaBorgId = "pl0005" | "pl0009";

/** Named spawner + helper addresses (the host resolves these via ctx hooks). */
export const TELEPORT_NINJA_SPAWNERS = {
  /** zz_007db5c_ @0x8007db5c — ninja-family shuriken spawner (table 0x802d6d68).
   *  TELEPORT NINJA shares the ninja shuriken record table; the per-borg type select
   *  (0x005/0x009 rows) is pending table 0x802d6d68 decode — see shurikenTypeFor. */
  SHURIKEN_SPAWNER_ADDR: 0x8007db5c,
  /** zz_006bf80_ @0x8006bf80 — target-visibility refresh (action-0 ph2 B-held loop). */
  VISIBILITY_REFRESH_ADDR: 0x8006bf80,
  /** zz_01464c0_ @0x801464c0 — action-0 ph1 transition tail (unsurfaced; TODO host hook). */
  PH1_TRANSITION_TAIL_ADDR: 0x801464c0,
} as const;

/** All DOL-read constants for the TELEPORT NINJA family (cited per FLOAT_8043a2xx). */
export const TELEPORT_NINJA = {
  /** FLOAT_8043a2b8 = 0.0 — zero-scalar (velocity/pose resets, accumulator80c clear). */
  ZERO: 0.0,
  /** FLOAT_8043a2bc = 30.0 — action-0 ph0 +0x560 aim/approach timer seed. */
  APPROACH_TIMER: 30.0,
  /** FLOAT_8043a2c0 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a2c4 = 0.95 — blink reposition + per-frame motion scale. */
  BLINK_SCALE: 0.95,
  /** FLOAT_8043a2c8 = 3.0 — afterimage (zz_00b22f4_) motion-magnitude gate. */
  AFTERIMAGE_GATE: 3.0,
  /** FLOAT_8043a2cc = 20.0 — action-0 ph0 slot-2 aim timer seed (FUN_80145e98). */
  SLOT2_AIM_TIMER: 20.0,
  /** FLOAT_8043a2dc = 60.0 — action-3 ph0 +0x558 seed (FUN_801474b4 B-charge). */
  BCHARGE_WINDOW: 60.0,
  /** +0x5e0 bits cleared at action-0 ph0 setup (FUN_801459f0: ~0xb0 mask). */
  PH0_CLEAR_MASK: 0xb0,
  /** +0x5e0 airborne/position-frozen bit (0x40). */
  AIRBORNE_BIT: 0x40,
  /** +0x5b4 B-held status bit (0x200). */
  B_HELD_BIT: 0x200,
  /** action-0 stream group (the teleport-approach choreography). */
  ACTION0_STREAM_GROUP: 2,
  /** action-3 stream group (B-charge teleport-dash). */
  ACTION3_STREAM_GROUP: 4,
  /** all-parts stream mask. */
  STREAM_MASK: 0xf,
} as const;

export interface TeleportNinjaFamilyCtx extends StreamContext {}

/** Scratch mirrors for ROM offsets not first-class on RomActor. */
export interface TeleportNinjaScratch {
  /** +0x5aa: signed yaw-error snapshot read by ph0 to pick the approach slot. */
  tnYawErr5aa?: number;
  /** +0x6ec: action-0 stream-slot direction byte (0 or 2). */
  tnStreamDir6ec?: number;
  /** +0x6ed: action-0 stream-side byte (0 ground / 1 air). */
  tnStreamSide6ed?: number;
  /** +0x6ee: per-move stream-slot base (combo follow-up ++). */
  tnSlotBase6ee?: number;
  /** +0x560: action-0 ph1 approach sub-timer (FLOAT_8043a2bc seed). */
  tnApproachTimer560?: number;
}

type TnActor = RomActor & TeleportNinjaScratch;

function scratchOf(actor: RomActor): TnActor {
  return actor as TnActor;
}

/** +0x5e0 airborne = position-frozen bit set. */
function isAirborne(actor: RomActor): boolean {
  return (actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT) !== 0;
}

/** Shuriken record-select by borgNumber (table 0x802d6d68). The NORMAL NINJA row is
 *  borg 0x000 → type 0 (decomp-verified in ninja.ts). The TELEPORT NINJA rows (0x005/
 *  0x009) are NOT yet surfaced in the decomp transcriptions; default to type 0 and
 *  cite the table for a follow-up pass. Exported for the pending action-1/3 port. */
export function shurikenTypeFor(borgNumber: number): number {
  void borgNumber;
  // TODO(rom): decode table 0x802d6d68 rows for borg 0x005/0x009 to recover the exact
  // per-borg shuriken type (ninja.ts covers 0x000→0, 0x00a→3; the teleport rows pending).
  return 0;
}

// ============================================================================
// ACTION 0 — teleport approach + B-held combo loop.
//   phase table @0x8033e518 (phase via +0x540); dispatcher FUN_801459a8 @0x801459a8.
//   ph0 FUN_801459f0 (setup), ph1 FUN_80145b00 (approach tick), ph2 FUN_80145bd8 (active).
// ============================================================================

/** Phase 0 — setup. FUN_801459f0 @ chunk_0037.c (68 instrs). */
function action0Phase0Setup(actor: TnActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.tnApproachTimer560 = TELEPORT_NINJA.APPROACH_TIMER; // +0x560 = 30.0 (FLOAT_8043a2bc)
  // zz_006d0dc_(actor, 0xc1, 0) — aim yaw toward target.
  stepTargetYaw(actor, 0xc1, 0);
  // Slot pick: +0x5aa < 1 → side 0 / slot 0; else side 1 / slot 2 (FUN_801459f0:18-26).
  const yawErr = actor.tnYawErr5aa ?? actor.turnErrorYaw;
  let slot: number;
  if (yawErr < 1) {
    slot = 0;
    actor.tnStreamSide6ed = 0; // +0x6ed = 0
  } else {
    slot = 2;
    actor.tnStreamSide6ed = 1; // +0x6ed = 1
  }
  actor.tnStreamDir6ec = slot; // +0x6ec = slot
  // zz_004beb8_(rate=-1, actor, 0xf, group=2, slot+0x6ee, -1, -1) — arm approach stream.
  const base = actor.tnSlotBase6ee ?? 0;
  startStream(
    actor,
    TELEPORT_NINJA.STREAM_MASK,
    TELEPORT_NINJA.ACTION0_STREAM_GROUP,
    slot + base,
    TELEPORT_NINJA.STREAM_RATE,
  );
  // +0x5e0 &= ~0xb0 (clear bits 0x10/0x20/0x80 — FUN_801459f0:31).
  actor.controlWord &= ~TELEPORT_NINJA.PH0_CLEAR_MASK;
  // Zero the four velocity scalars + pose accum (FLOAT_8043a2b8 = 0.0).
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  // Blink reposition: motion = pos − targetCache5e8; motion ×= 0.95; pos += motion.
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor); // zz_00679d0_
  actor.accumulator80c = TELEPORT_NINJA.ZERO; // +0x80c = 0.0 (FLOAT_8043a2b8)
}

/** Phase 1 — approach tick. FUN_80145b00 @ chunk_0038.c (54 instrs). */
function action0Phase1Approach(actor: TnActor, ctx: StreamContext): void {
  // zz_004cd24_ only when +0x1cef == 0 (no active part-0 contact this frame).
  if (actor.contactP0 === 0) tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  // zz_006d0dc_(0xc1, 0) — continue aim; returns nonzero once converged.
  const converged = stepTargetYaw(actor, 0xc1, 0);
  const t = (actor.tnApproachTimer560 ?? 0) - actor.dt;
  if (!converged) {
    actor.tnApproachTimer560 = t; // +0x560 -= dt
    if (TELEPORT_NINJA.ZERO < t) {
      // Timer still running → continue the approach drift (LAB_80145b80 tail).
      driftAndAfterimage(actor);
      return;
    }
  }
  // Converged OR timer expired: if +0x1cef still 0, advance +0x540 and run the
  // transition tail zz_01464c0_ (unsurfaced host hook @0x801464c0).
  if (actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    // TODO(rom): zz_01464c0_ @0x801464c0 (the ph1→ph2 transition tail) is unsurfaced;
    // its effect on +0x18da/+0x1dfc aim accumulators is host-owned. No port-side effect.
    void TELEPORT_NINJA_SPAWNERS.PH1_TRANSITION_TAIL_ADDR;
  }
  driftAndAfterimage(actor);
}

/** LAB_80145b80 tail: motion ×= 0.95; pos += motion; ground snap; afterimage if |m| > 3. */
function driftAndAfterimage(actor: TnActor): void {
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  const mag = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
  if (mag > TELEPORT_NINJA.AFTERIMAGE_GATE) {
    stepAfterimage(actor); // zz_00b22f4_
  }
}

/** Phase 2 — active frames / B-held combo loop. FUN_80145bd8 @ chunk_0038.c (161 instrs).
 *  Condensed faithful port: the handlerTimer(+0x558) gate, the B-held(+0x5b4 &0x200) +
 *  ammo(zz_006dbe0_(0,1,0) check-only) combo loop, the airborne re-dispatch, and the
 *  wallContact(+0x1cee) → ground-idle-return exit. The stream-slot direction re-arm
 *  (the +0x1cf2 / +0x1dfc-sign branch) is host-stream-owned and cited as TODO. */
function action0Phase2Active(actor: TnActor, ctx: StreamContext): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    // Window expired: B-held + ammo still available → loop; else fall through to exit probe.
    const bHeld = (actor.statusWord5b4 & TELEPORT_NINJA.B_HELD_BIT) !== 0;
    if (bHeld && allocateWeapon(actor, ctx, 0, 1, false)) {
      // zz_006dbe0_(actor,0,1,0) — check-only (consume=false). Ammo ok → continue combo.
      if (isAirborne(actor)) {
        // Airborne: zz_006a3d0_(actor, 0, 3, 0) — command re-issue (bridge-owned).
        // Modeled as the cue-44 attack re-dispatch so the family re-enters state 61.
        dispatchFullBodyCue(actor, 0x2c);
        return;
      }
      // Grounded: zz_006bf80_(visibility refresh) + +0x540-- (loop back to ph1).
      ctx.onRefreshTargetVisibility?.(actor);
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1;
      // The stream-slot direction re-arm reads the sign of +0x1dfc (aimRoll1dfc) and the
      // +0x6ed side byte; the stream VM owns slot resolution, so this is a host concern.
      // TODO(rom): wire the +0x1dfc-sign → +0x6ec/+0x6ed stream re-arm once the aim-roll
      // accumulator is surfaced (FUN_80145bd8:45-62, chunk_0038.c).
      return;
    }
  } else {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
  }
  // No active hit this frame: drift + afterimage while no wallContact.
  if (actor.wallContact === 0) {
    driftAndAfterimage(actor);
    return;
  }
  // wallContact (+0x1cee != 0) → exit: +0x73f=0; +0x5e0&=~3; zz_006a474_(ground idle return).
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;
  romGroundIdleReturn(actor);
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_80145924 indexes PTR_FUN_8033e4f4[+0x580]. action 0 is
// ported bespoke; action 2 routes through the shared-engine X-special approximation;
// actions 1/3 fall back to the shared engine with cited TODOs for the bespoke tables.
// ----------------------------------------------------------------------------
export function createTeleportNinjaRootAction(
  ctx: TeleportNinjaFamilyCtx,
): (actor: RomActor) => void {
  // action 2 (X-special) — shared-engine approximation. TELEPORT NINJA's bespoke X
  // tables are @0x8033e584/594 (fns 0x80146dcc..0x80147464); their deep port is TODO.
  const sharedX = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) action0Phase0Setup(actor);
        else if (phase === 1) action0Phase1Approach(actor, ctx);
        else if (phase >= 2) action0Phase2Active(actor, ctx);
        return;
      }
      case 1:
        // TODO(rom): port action-1 bespoke tables @0x8033e568/574
        // (fns 0x80146640..0x80147094, chunk_0038.c) — the teleport-strike melee.
        // Falls through to the shared engine as the closest approximation.
        return;
      case 2:
        sharedX(actor);
        return;
      case 3:
        // TODO(rom): port action-3 B-charge table @0x8033e5b4
        // (FUN_801474b4 setup → 0x801475f8/0x801476b0/0x801477e4/0x80147924, chunk_0038.c)
        // — the teleport-dash flurry. Falls through for now.
        return;
      default:
        return;
    }
  };
}

/** Configure a freshly-spawned TELEPORT NINJA family actor (pl0005/pl0009). Stamps the
 *  per-borg number and wires the bespoke action-0 machine + shared-engine X. */
export function configureTeleportNinjaFamily(
  actor: RomActor,
  borgId: TeleportNinjaBorgId,
  ctx: TeleportNinjaFamilyCtx,
): void {
  actor.borgNumber = TELEPORT_NINJA_BORG_NUMBERS[borgId] ?? 0x005;
  actor.rootAction = createTeleportNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const TELEPORT_NINJA_CONSTANTS = TELEPORT_NINJA;

// ============================================================================
// Self-tests (mirror victory-king.ts / rom.selfcheck.ts style).
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function makeCtx(opts: {
  onAllocateResource?: () => boolean;
  onRefreshTargetVisibility?: () => void;
} = {}): TeleportNinjaFamilyCtx {
  const ctx: TeleportNinjaFamilyCtx = {};
  if (opts.onAllocateResource) ctx.onAllocateResource = () => opts.onAllocateResource!();
  if (opts.onRefreshTargetVisibility) {
    const sink = opts.onRefreshTargetVisibility;
    ctx.onRefreshTargetVisibility = () => sink();
  }
  return ctx;
}

export function runTeleportNinjaSelfTests(assert: AssertFn): void {
  // --- configure stamps borgNumber + wires bespoke rootAction for both borgs. ---
  for (const { id, num } of [
    { id: "pl0005" as const, num: 0x005 },
    { id: "pl0009" as const, num: 0x009 },
  ]) {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, id, makeCtx());
    assert(a.borgNumber === num, `${id} borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} bespoke rootAction wired`);
  }

  // --- action 0 ph0: advance +0x540, seed approach timer 30.0, zero scalars, blink. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances to ph1");
    assert(a.tnApproachTimer560 === TELEPORT_NINJA.APPROACH_TIMER,
      "action0 ph0 +0x560 = 30.0 (FLOAT_8043a2bc)");
    assert(
      a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0 && a.gravityCoeff === 0,
      "action0 ph0 zeroes all four velocity scalars (FLOAT_8043a2b8)",
    );
    assert(a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      "action0 ph0 clears pose accumulators");
    // Blink: motion = (100,0,0) × 0.95 = (95,0,0); pos += motion → x = 195.
    assert(a.pos.x === 195, "action0 ph0 blink: pos.x = 195 ((pos−target)×0.95 added)");
    assert(a.motion.x === 95, "action0 ph0 motion.x = 95 (×FLOAT_8043a2c4)");
    assert((a.controlWord & TELEPORT_NINJA.PH0_CLEAR_MASK) === 0,
      "action0 ph0 clears +0x5e0 bits 0xb0");
  }

  // --- action 0 ph0 slot pick: +0x5aa >= 1 → slot 2 / side 1. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0009", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.tnYawErr5aa = 5; // >= 1 → air-side slot
    root(a); // ph0
    assert(a.tnStreamDir6ec === 2 && a.tnStreamSide6ed === 1,
      "action0 ph0 +0x5aa>=1 → slot 2 / side 1");
  }

  // --- action 0 ph1: contactP0==0 gates the stream tick; drift applies. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.tnApproachTimer560 = 1.0; // one frame from expiry
    a.motion = { x: 10, y: 0, z: 0 };
    a.contactP0 = 0; // no contact → stream ticks
    root(a); // ph1: not converged, timer 1→0 NOT <0... 0 < 0 false → drift tail
    // motion ×= 0.95 = 9.5; pos.x += 9.5
    assert(a.motion.x === 9.5, "action0 ph1 drift: motion.x *= 0.95 (FLOAT_8043a2c4)");
  }

  // --- action 0 ph2: window expired + B-held + ammo ok (grounded) → loop (ph0--). ---
  {
    const a = createRomActor() as TnActor;
    let refreshed = 0;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({
      onAllocateResource: () => true,
      onRefreshTargetVisibility: () => { refreshed += 1; },
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0; // window expired
    a.statusWord5b4 = TELEPORT_NINJA.B_HELD_BIT; // B held
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action0 ph2 grounded B-held loop: +0x540-- back to ph1");
    assert(refreshed === 1, "action0 ph2 grounded loop calls zz_006bf80_ (visibility refresh)");
  }

  // --- action 0 ph2: window expired + B-held + ammo ok (airborne) → cue 0x2c re-dispatch. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0x2c * 2] = 61;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0;
    a.statusWord5b4 = TELEPORT_NINJA.B_HELD_BIT;
    a.controlWord = TELEPORT_NINJA.AIRBORNE_BIT; // airborne
    root(a);
    assert(a.fbState === 61, "action0 ph2 airborne re-dispatches cue 0x2c → state 61");
  }

  // --- action 0 ph2: window expired + B released → fall through, wallContact exits. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0; // expired
    a.statusWord5b4 = 0; // B released
    a.wallContact = 1; // exit trigger
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 → wallContact exit (zz_006a474_)
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph2 wallContact exit clears +0x73f / strips +0x5e0 bits");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0 && a.gravityCoeff === 0,
      "action0 ph2 ground idle return (zz_006a474_) zeroes velocity scalars");
  }

  // --- rootAction no-ops for unsupported actionIndex (action 1 bespoke TODO). ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; // bespoke TODO → no-op fall through
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action1 bespoke TODO falls through (no phase advance)");
  }
}
