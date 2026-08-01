// Vehicle Borg family — BEAM SATELLITE (pl0e01) + DEATH SAUCER (pl0e02) + ANTARES (pl0e03).
//
// Three fortress-family vehicle borgs sharing one root-dispatch shape: a root router
// indexes actionIndex (+0x580) into per-borg action sub-routers, each of which
// dispatches its own phase table (indexed by +0x540). The three diverge in their
// action-0 implementation but share the action-2 ammo-gated spawn + cooldown shape.
//
// Root dispatchers (index PTR_FUN_<root>[+0x580]):
//   BEAM SAT  FUN_801d5928 → PTR_FUN_8038d218  (chunk_0057.c:795)
//   ANTARES   FUN_801d5e90 → PTR_FUN_8038dbc8  (chunk_0057.c:936)
//   DEATH SAU FUN_801d7564 → PTR_FUN_8038dff8  (chunk_0057.c:1825)
//
// Phase tables (length confirmed by next-table − this-table address arithmetic):
//   BEAM SAT  action 0 @0x8038d224 = [stub_59a0, FUN_801d59b0, FUN_801d5a28]  (3 ptrs;
//              0x8038d230 − 0x8038d224 = 0xc. Work-queue overread as 6, true len 3.)
//   BEAM SAT  action 2 @0x8038d230 = [stub_5ac4, FUN_801d5adc, FUN_801d5b5c]  (3 phases)
//   ANTARES   action 0 @0x8038dbd4 = [FUN_801d5f08, FUN_801d5fbc, FUN_801d6034, FUN_801d60d0]
//              (4 phases; 0x8038dbf4 − 0x8038dbd4 = 0x20 = action-0 (4) + action-1 (4) gap)
//   ANTARES   action 2 @0x8038dbf4 = [stub_6198, FUN_801d61a8, FUN_801d6224]   (3 phases)
//   DEATH SAU action 0 @0x8038e004 = [FUN_801d75dc, zz_01d773c_, FUN_801d7864] (3 ptrs;
//              0x8038e010 − 0x8038e004 = 0xc)
//   DEATH SAU action 2 @0x8038e010 = [stub_78fc, FUN_801d7914, FUN_801d7988]   (3 phases)
//
// Source: research/decomp/ghidra-export/chunk_0057.c:795-1105 (BEAM SAT + ANTARES) and
//         :1825-2016 (DEATH SAUCER). Floats read from boot.dol (cited per constant).
// Exit helper zz_006a53c_ @ chunk_0009.c:750 (clear +0x73f, strip +0x5e0 action bits,
// dispatch full-body cue 0x1b; seed +0x694 = param+dt when param > 0).

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Borg numbers for the three vehicle-family members. */
const VEHICLE_BORG_NUMBERS: Record<string, number> = {
  pl0e01: 0xe01, // BEAM SATELLITE
  pl0e02: 0xe02, // DEATH SAUCER
  pl0e03: 0xe03, // ANTARES
};

export type VehicleBorgId = keyof typeof VEHICLE_BORG_NUMBERS;

// ----------------------------------------------------------------------------
// Spawner addresses (family-local zz_01xxxxx_ / FUN_80xxxxx projectile+effect hooks).
// ----------------------------------------------------------------------------
/** zz_013212c_ @0x8013212c — BEAM SAT action-0 hardpoint spawn. */
export const VEHICLE_HARDPOINT_SPAWNER = 0x8013212c;
/** zz_01f23b0_ @0x801f23b0 — BEAM SAT + DEATH SAUCER action-2 port spawn. */
export const VEHICLE_DUAL_PORT_SPAWNER = 0x801f23b0;
/** zz_01f49c8_ @0x801f49c8 — ANTARES action-2 shot spawn. */
export const VEHICLE_ANTARES_SHOT_SPAWNER = 0x801f49c8;
/** FUN_801f3784 @0x801f3784 — ANTARES action-0 aimed spawn. */
export const VEHICLE_ANTARES_AIMED_SPAWNER = 0x801f3784;
/** zz_01deb68_ @0x801deb68 — DEATH SAUCER action-0 deploy arm. */
export const VEHICLE_SAUCER_DEPLOY_ARM = 0x801deb68;
/** zz_01d773c_ @0x801d773c — DEATH SAUCER deploy position solver (also the ph1 entry). */
export const VEHICLE_SAUCER_DEPLOY_SOLVE = 0x801d773c;

// ----------------------------------------------------------------------------
// Per-family float constants (read from boot.dol, cited).
// ----------------------------------------------------------------------------
export const BEAM_SAT = {
  /** FLOAT_8043be94 = 180.0 — action-2 +0x558 seed on successful ammo gate. */
  A2_OK_TIMER: 180.0,
  /** FLOAT_8043be98 = 10.0 — action-2 +0x558 seed on ammo denial. */
  A2_FAIL_TIMER: 10.0,
  /** FLOAT_8043be9c = 0.0 — action-2 phase-2 cooldown exit threshold. */
  A2_THRESHOLD: 0.0,
  /** +0x548 = 0x1e (30) — action-0 hardpoint-countdown seed when a hardpoint fires. */
  A0_HIT_COUNTDOWN: 30,
  /** +0x548 = 0xa (10) — action-0 hardpoint-countdown seed when no hardpoint is active. */
  A0_MISS_COUNTDOWN: 10,
  /** 4 hardpoints polled at +0x144..+0x147 (FUN_801d59b0 loop). */
  A0_HARDPOINT_COUNT: 4,
  /** zz_013212c_(actor, i + 0x16) — base record-select argument. */
  A0_HARDPOINT_BASE_TYPE: 0x16,
  /** +0x548 = 1 — action-2 armed flag set on successful spawn (gates +0x597 |= 4). */
  A2_ARMED_FLAG: 1,
  /** +0x597 |= 4 — action-2 sub-router post-dispatch animation flag mask. */
  A2_ANIM_FLAG_MASK: 0x4,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
} as const;

export const ANTARES = {
  /** FLOAT_8043bea4 = 30.0 — action-0 ph0 +0x558 seed; action-2 ph1 OK +0x558 seed. */
  A0_PH0_TIMER: 30.0,
  /** FLOAT_8043beb4 = 0.2 — FUN_8006cc90 stream rate (cosmetic, no-op without banks). */
  STREAM_RATE: 0.2,
  /** FLOAT_8043beac = 0.0 — ph1 wait threshold / ph3 cooldown exit / ph2 fail cd. */
  A0_THRESHOLD: 0.0,
  /** FLOAT_8043beb8 = 40.0 — action-0 ph2 +0x558 seed on successful ammo gate. */
  A0_PH2_OK_TIMER: 40.0,
  /** FLOAT_8043bebc = 20.0 — action-0 ph2 +0x55c cooldown seed on success. */
  A0_PH2_OK_CD: 20.0,
  /** FLOAT_8043bec0 = 10.0 — action-0 ph2 +0x558 seed on denial; action-2 ph1 deny seed. */
  A0_FAIL_TIMER: 10.0,
  /** FLOAT_8043bea8 = -400.0 — action-0 ph0 aim local_10 threshold (unsurfaced aim solve). */
  A0_PH0_Y_THRESHOLD: -400.0,
  /** FLOAT_8043beb0 = 750.0 — action-0 ph0 aim local_14 threshold (unsurfaced aim solve). */
  A0_PH0_Z_THRESHOLD: 750.0,
  /** FLOAT_8043bea4 = 30.0 — action-2 ph1 +0x558 seed on successful ammo gate. */
  A2_OK_TIMER: 30.0,
  /** FLOAT_8043bec0 = 10.0 — action-2 ph1 +0x558 seed on denial. */
  A2_FAIL_TIMER: 10.0,
  /** FLOAT_8043beac = 0.0 — action-2 phase-2 cooldown exit threshold. */
  A2_THRESHOLD: 0.0,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
} as const;

export const DEATH_SAUCER = {
  /** FLOAT_8043beec = 180.0 — action-0 ph0 +0x558 seed; action-2 ph1 OK +0x558 seed. */
  A0_PH0_TIMER: 180.0,
  /** FLOAT_8043bef0 = 0.0 — ph1 deploy-solve exit threshold; action-2 ph2 threshold. */
  A0_PH1_THRESHOLD: 0.0,
  /** +0x6f7 = 0x78 (120) — action-0 ph0 deploy frame-counter seed. */
  A0_PH0_DEPLOY_FRAMES: 120,
  /** +0x6ea = 2 — action-0 ph0 deploy part-slot seed (overridden by paired-actor select). */
  A0_PH0_DEPLOY_SLOT: 2,
  /** zz_006a53c_(actor, 10) — action-0 ph0 cancel param on ammo denial. */
  A0_CANCEL_PARAM: 10,
  /** FLOAT_8043bef4 = 100000.0 — paired-actor nearest-of-4 initial distance (unsurfaced). */
  A0_NEAREST_INIT_DIST: 100000.0,
  /** FLOAT_8043bef8 = -100.0 — deploy-solve local_14 clamp base (unsurfaced matrix solve). */
  A0_SOLVE_CLAMP_BASE: -100.0,
  /** FLOAT_8043befc = 100.0 — +0x55c += when +0x6f7 > 0 (unsurfaced matrix solve). */
  A0_SOLVE_CD_STEP: 100.0,
  /** FLOAT_8043beec = 180.0 — action-2 ph1 +0x558 seed on successful ammo gate. */
  A2_OK_TIMER: 180.0,
  /** FLOAT_8043bf00 = 10.0 — action-2 ph1 +0x558 seed on denial. */
  A2_FAIL_TIMER: 10.0,
  /** FLOAT_8043bef0 = 0.0 — action-2 phase-2 cooldown exit threshold. */
  A2_THRESHOLD: 0.0,
  /** +0x548 = 1 — action-2 armed flag set on successful spawn. */
  A2_ARMED_FLAG: 1,
  /** +0x597 |= 4 — action-2 sub-router post-dispatch animation flag mask. */
  A2_ANIM_FLAG_MASK: 0x4,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface VehicleScratch {
  /** +0x144..+0x147: 4 hardpoint attachment flags (BEAM SAT action-0 polls bit 0). */
  vehHardpointFlags?: [number, number, number, number];
  /** +0x14e: ANTARES action-2 spawn toggle (^1 each shot). */
  vehToggle14e?: number;
  /** +0x14f: ANTARES action-0 ph2 spawn slot (selected by the unsurfaced ph0 aim solve). */
  vehSlot14f?: number;
  /** +0x150: ANTARES stream/aim channel (selected by the unsurfaced ph0 aim solve). */
  vehSlot150?: number;
  /** +0x548: handler-local short — action-0 hardpoint countdown / action-2 armed flag. */
  vehCountdown548?: number;
  /** +0x55c: cooldown sub-timer (float; ANTARES ph2/ph3 + DEATH SAUCER ph0). */
  vehCooldownTimer55c?: number;
  /** +0x597: action-2 animation flag byte (|= 4 while +0x548 != 0 for BEAM SAT / SAUCER). */
  vehFlag597?: number;
  /** +0x6ea: DEATH SAUCER deploy part-slot cursor. */
  vehDeploySlot6ea?: number;
  /** +0x6f7: DEATH SAUCER deploy frame counter (seeded 0x78). */
  vehDeployFrames6f7?: number;
}

type VehicleActor = RomActor & VehicleScratch;

function scratchOf(actor: RomActor): VehicleActor {
  return actor as VehicleActor;
}

// ----------------------------------------------------------------------------
// zz_006a53c_(actor, param) — chunk_0009.c:750. Common action-exit: clear
// housekeeping, strip the action-mode bits, dispatch full-body cue 0x1b, and
// (when param > 0) seed +0x694 = param + dt.
// ----------------------------------------------------------------------------
function exitAction(actor: VehicleActor, param: number, cue: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, cue);
}

// ----------------------------------------------------------------------------
// FUN_8006cc90 host bridge. The vehicle family has no extracted stream banks
// (code-driven), so the tick is an honest no-op returning 0 — the exact ROM
// behavior when no bank is attached (the +0x1d80 bank pointer is null).
// ----------------------------------------------------------------------------
function tickVehicleStream(): number {
  return 0;
}

// ============================================================================
// BEAM SATELLITE (pl0e01, ctor 0x801d5718)
// ============================================================================

/** Action 0 — hardpoint spawn (table @0x8038d224, 3 phases).
 *  ph0 stub_59a0: advance.
 *  ph1 FUN_801d59b0: +0x540++; seed +0x548=10; loop 4 hardpoints (+0x144+i), on the
 *     first with bit 0 set fire zz_013212c_(actor, i+0x16), set +0x548=30, return.
 *  ph2 FUN_801d5a28: +0x548--; exit (zz_006a53c_(0)) when +0x548 < 1. */
function beamSatAction0(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: // stub FUN_801d59a0 — advance
      actor.fbPhaseSlots[0] = 1;
      return;
    case 1: { // FUN_801d59b0 — hardpoint loop
      actor.fbPhaseSlots[0] = 2;
      actor.vehCountdown548 = BEAM_SAT.A0_MISS_COUNTDOWN; // +0x548 = 10
      const flags = actor.vehHardpointFlags ?? [0, 0, 0, 0];
      for (let i = 0; i < BEAM_SAT.A0_HARDPOINT_COUNT; i += 1) {
        if ((flags[i] ?? 0) & 1) {
          // zz_013212c_(actor, i + 0x16, &flag) — family-local hardpoint spawn.
          ctx.onFamilyProjectile?.(actor, VEHICLE_HARDPOINT_SPAWNER, BEAM_SAT.A0_HARDPOINT_BASE_TYPE + i);
          actor.vehCountdown548 = BEAM_SAT.A0_HIT_COUNTDOWN; // +0x548 = 0x1e (30)
          return; // ROM returns on the first active hardpoint
        }
      }
      return;
    }
    case 2: { // FUN_801d5a28 — countdown
      actor.vehCountdown548 = (actor.vehCountdown548 ?? 0) - 1;
      if ((actor.vehCountdown548 ?? 0) < 1) exitAction(actor, 0, BEAM_SAT.EXIT_CUE);
      return;
    }
    default: return;
  }
}

/** Action 2 — ammo-gated dual-port spawn (table @0x8038d230, 3 phases).
 *  ph0 stub_5ac4: advance.
 *  ph1 FUN_801d5adc: +0x540++; zz_006dbe0_(slot 2); on success +0x558=180,
 *     zz_01f23b0_(actor,0)+(actor,1), +0x548=1; on denial +0x558=10.
 *  ph2 FUN_801d5b5c: +0x558 -= dt; exit when +0x558 <= 0.0.
 *  Sub-router FUN_801d5a64 also sets +0x597 |= 4 when +0x548 != 0 (handled by root). */
function beamSatAction2(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: // stub FUN_801d5ac4 — advance
      actor.fbPhaseSlots[0] = 1;
      return;
    case 1: { // FUN_801d5adc — ammo-gated dual spawn
      actor.fbPhaseSlots[0] = 2;
      if (allocateWeapon(actor, ctx, 2, 1, true)) {
        actor.handlerTimer = BEAM_SAT.A2_OK_TIMER; // +0x558 = 180 (FLOAT_8043be94)
        ctx.onFamilyProjectile?.(actor, VEHICLE_DUAL_PORT_SPAWNER, 0); // zz_01f23b0_(actor,0)
        ctx.onFamilyProjectile?.(actor, VEHICLE_DUAL_PORT_SPAWNER, 1); // zz_01f23b0_(actor,1)
        actor.vehCountdown548 = BEAM_SAT.A2_ARMED_FLAG; // +0x548 = 1
      } else {
        actor.handlerTimer = BEAM_SAT.A2_FAIL_TIMER; // +0x558 = 10 (FLOAT_8043be98)
      }
      return;
    }
    case 2: { // FUN_801d5b5c — cooldown
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= BEAM_SAT.A2_THRESHOLD) exitAction(actor, 0, BEAM_SAT.EXIT_CUE);
      return;
    }
    default: return;
  }
}

// ============================================================================
// ANTARES (pl0e03, ctor 0x801d5ba4)
// ============================================================================

/** Action 0 — aimed burst (table @0x8038dbd4, 4 phases).
 *  ph0 FUN_801d5f08: +0x540++; +0x558=30; aim solve via zz_0066408_ writes +0x14f/+0x150
 *     from a 3-axis threshold lookup (HEAVY host dep — see TODO).
 *  ph1 FUN_801d5fbc: +0x558 -= dt; FUN_8006cc90 stream tick (no-op); advance on event
 *     or when +0x558 <= 0.0.
 *  ph2 FUN_801d6034: +0x540++; zz_006dbe0_(slot 0); on success stream tick +
 *     FUN_801f3784(actor,+0x14f), +0x558=40, +0x55c=20; on denial +0x558=10, +0x55c=0.
 *  ph3 FUN_801d60d0: while +0x55c>0 tick stream + drain +0x55c; drain +0x558;
 *     exit when +0x558 <= 0.0. */
function antaresAction0(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_801d5f08 — setup + aim solve
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = ANTARES.A0_PH0_TIMER; // +0x558 = 30 (FLOAT_8043bea4)
      // zz_0066408_(actor, descriptor+0x10, &+0x518, &local) computes a relative target
      // vector; the 3-axis thresholds (FLOAT_8043bea8=-400 / beac=0 / beb0=750) select a
      // (slot14f, slot150) pair from a lookup table.
      // TODO(host): descriptor bone (+0x4b0→+0x10) + aim origin (+0x518) + lookup
      // (uVar2*2 + base) are renderer/descriptor state not surfaced here; vehSlot14f /
      // vehSlot150 keep their prior value (0 when unset). Faithful port would write the
      // selected pair from the decoded lookup once the host surfaces the aim matrix.
      return;
    }
    case 1: { // FUN_801d5fbc — wait
      actor.handlerTimer -= actor.dt;
      const event = tickVehicleStream(); // FUN_8006cc90(rate 0.2, actor, +0x150, 1, &DAT)
      if (event === 0 && ANTARES.A0_THRESHOLD < actor.handlerTimer) return;
      actor.fbPhaseSlots[0] = 2;
      return;
    }
    case 2: { // FUN_801d6034 — fire
      actor.fbPhaseSlots[0] = 3;
      if (allocateWeapon(actor, ctx, 0, 1, true)) {
        tickVehicleStream(); // FUN_8006cc90(rate 0.2, actor, +0x150, 1, &DAT)
        ctx.onFamilyProjectile?.(actor, VEHICLE_ANTARES_AIMED_SPAWNER, actor.vehSlot14f ?? 0);
        actor.handlerTimer = ANTARES.A0_PH2_OK_TIMER; // +0x558 = 40 (FLOAT_8043beb8)
        actor.vehCooldownTimer55c = ANTARES.A0_PH2_OK_CD; // +0x55c = 20 (FLOAT_8043bebc)
      } else {
        actor.handlerTimer = ANTARES.A0_FAIL_TIMER; // +0x558 = 10 (FLOAT_8043bec0)
        actor.vehCooldownTimer55c = ANTARES.A0_THRESHOLD; // +0x55c = 0 (FLOAT_8043beac)
      }
      return;
    }
    case 3: { // FUN_801d60d0 — cooldown
      if (ANTARES.A0_THRESHOLD < (actor.vehCooldownTimer55c ?? 0)) {
        actor.vehCooldownTimer55c = (actor.vehCooldownTimer55c ?? 0) - actor.dt;
        tickVehicleStream();
      }
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= ANTARES.A0_THRESHOLD) exitAction(actor, 0, ANTARES.EXIT_CUE);
      return;
    }
    default: return;
  }
}

/** Action 2 — ammo-gated toggle spawn (table @0x8038dbf4, 3 phases).
 *  ph0 stub_6198: advance.
 *  ph1 FUN_801d61a8: +0x540++; zz_006dbe0_(slot 2); on success +0x558=30,
 *     zz_01f49c8_(actor,+0x14e), +0x14e ^= 1; on denial +0x558=10.
 *  ph2 FUN_801d6224: +0x558 -= dt; exit when +0x558 <= 0.0.
 *  Sub-router FUN_801d615c has NO +0x597 post-set (unlike BEAM SAT / DEATH SAUCER). */
function antaresAction2(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: // stub FUN_801d6198 — advance
      actor.fbPhaseSlots[0] = 1;
      return;
    case 1: { // FUN_801d61a8 — ammo-gated spawn
      actor.fbPhaseSlots[0] = 2;
      if (allocateWeapon(actor, ctx, 2, 1, true)) {
        actor.handlerTimer = ANTARES.A2_OK_TIMER; // +0x558 = 30 (FLOAT_8043bea4)
        ctx.onFamilyProjectile?.(actor, VEHICLE_ANTARES_SHOT_SPAWNER, actor.vehToggle14e ?? 0);
        actor.vehToggle14e = ((actor.vehToggle14e ?? 0) ^ 1) & 1; // +0x14e ^= 1
      } else {
        actor.handlerTimer = ANTARES.A2_FAIL_TIMER; // +0x558 = 10 (FLOAT_8043bec0)
      }
      return;
    }
    case 2: { // FUN_801d6224 — cooldown
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= ANTARES.A2_THRESHOLD) exitAction(actor, 0, ANTARES.EXIT_CUE);
      return;
    }
    default: return;
  }
}

// ============================================================================
// DEATH SAUCER (pl0e02, ctor 0x801d73c8)
// ============================================================================

/** zz_01d773c_ — per-frame deploy position solver (also the action-0 ph1 entry).
 *  Faithfully drains +0x558 and advances +0x540 when expired; the matrix/part-anchor
 *  position solve writing +0x144/+0x150 is host-renderer state not surfaced here. */
function deathSaucerDeploySolve(actor: VehicleActor): void {
  // zz_00665cc_(actor) — target aim refresh; no-op without a host target.
  // TODO(host): gnt4_PSMTXMultVec(+0x8d4 + vehDeploySlot6ea*0x30) projects the deploy
  // origin; gnt4_PSVECSubtract/PSQUATScale/PSVECAdd write the aimed position to +0x150.
  // The +0x55c += FLOAT_8043befc(100) when +0x6f7 > 0 scales the quat projection.
  // Those reads depend on the renderer-owned part-anchor rows (+0x8d4/+0x8e0/+0x8f0/
  // +0x900) which are not on RomActor; faithful port deferred to the host bridge.
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= DEATH_SAUCER.A0_PH1_THRESHOLD) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  }
}

/** Action 0 — deploy saucer (table @0x8038e004, 3 phases).
 *  ph0 FUN_801d75dc: +0x540++; zz_006dbe0_(slot 0); on denial cancel via zz_006a53c_(10);
 *     on success seed +0x558=180/+0x55c=0/+0x6f7=120/+0x6ea=2, run a paired-actor
 *     nearest-of-4 retarget (HEAVY host dep — see TODO), then zz_01deb68_ arm +
 *     zz_01d773c_ solve (called inline, draining +0x558 one frame).
 *  ph1 zz_01d773c_: per-frame solve (drain +0x558, advance when <= 0).
 *  ph2 FUN_801d7864: clear +0x73f/+0x5e0 and exit (zz_006a53c_(0)). */
function deathSaucerAction0(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_801d75dc — ammo-gated deploy arm
      actor.fbPhaseSlots[0] = 1;
      if (!allocateWeapon(actor, ctx, 0, 1, true)) {
        exitAction(actor, DEATH_SAUCER.A0_CANCEL_PARAM, DEATH_SAUCER.EXIT_CUE); // zz_006a53c_(10)
        return;
      }
      // zz_00665cc_(actor) — target aim refresh (no-op without host target).
      actor.handlerTimer = DEATH_SAUCER.A0_PH0_TIMER; // +0x558 = 180 (FLOAT_8043beec)
      actor.vehCooldownTimer55c = DEATH_SAUCER.A0_PH1_THRESHOLD; // +0x55c = 0 (FLOAT_8043bef0)
      actor.vehDeployFrames6f7 = DEATH_SAUCER.A0_PH0_DEPLOY_FRAMES; // +0x6f7 = 0x78
      actor.vehDeploySlot6ea = DEATH_SAUCER.A0_PH0_DEPLOY_SLOT; // +0x6ea = 2
      // TODO(host): the +0xcc-target paired-actor nearest-of-4 selection (DAT_80435b00
      // walks 4 part-anchor rows +0x8e0/+0x8f0/+0x900, min PSVEC distance vs +0x524)
      // overrides vehDeploySlot6ea when +0xcc != 0. Renderer-owned anchors not surfaced.
      ctx.onFamilyProjectile?.(actor, VEHICLE_SAUCER_DEPLOY_ARM, 9); // zz_01deb68_(actor,9,...)
      deathSaucerDeploySolve(actor); // ROM calls zz_01d773c_ inline at end of ph0
      return;
    }
    case 1: { // zz_01d773c_ — per-frame solve
      deathSaucerDeploySolve(actor);
      return;
    }
    case 2: { // FUN_801d7864 — exit (+0x73f=0; +0x5e0&=~3; zz_006a53c_(0))
      exitAction(actor, 0, DEATH_SAUCER.EXIT_CUE);
      return;
    }
    default: return;
  }
}

/** Action 2 — ammo-gated port spawn (table @0x8038e010, 3 phases).
 *  ph0 stub_78fc: advance.
 *  ph1 FUN_801d7914: +0x540++; zz_006dbe0_(slot 2); on success +0x558=180,
 *     zz_01f23b0_(actor,2), +0x548=1; on denial +0x558=10.
 *  ph2 FUN_801d7988: +0x558 -= dt; exit when +0x558 <= 0.0.
 *  Sub-router FUN_801d789c also sets +0x597 |= 4 when +0x548 != 0 (handled by root). */
function deathSaucerAction2(actor: VehicleActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: // stub FUN_801d78fc — advance
      actor.fbPhaseSlots[0] = 1;
      return;
    case 1: { // FUN_801d7914 — ammo-gated spawn
      actor.fbPhaseSlots[0] = 2;
      if (allocateWeapon(actor, ctx, 2, 1, true)) {
        actor.handlerTimer = DEATH_SAUCER.A2_OK_TIMER; // +0x558 = 180 (FLOAT_8043beec)
        ctx.onFamilyProjectile?.(actor, VEHICLE_DUAL_PORT_SPAWNER, 2); // zz_01f23b0_(actor,2)
        actor.vehCountdown548 = DEATH_SAUCER.A2_ARMED_FLAG; // +0x548 = 1
      } else {
        actor.handlerTimer = DEATH_SAUCER.A2_FAIL_TIMER; // +0x558 = 10 (FLOAT_8043bf00)
      }
      return;
    }
    case 2: { // FUN_801d7988 — cooldown
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= DEATH_SAUCER.A2_THRESHOLD) exitAction(actor, 0, DEATH_SAUCER.EXIT_CUE);
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher factory. Each borg wires its own action-0/action-2 handlers and
// declares whether its action-2 sub-router arms the +0x597 animation flag.
// ----------------------------------------------------------------------------
export interface VehicleMachineConfig {
  action0: (actor: VehicleActor, ctx: StreamContext) => void;
  action2: (actor: VehicleActor, ctx: StreamContext) => void;
  /** True for BEAM SAT / DEATH SAUCER (sub-router sets +0x597 |= 4 while +0x548 != 0). */
  action2ArmsAnimFlag: boolean;
  animFlagMask: number;
}

const BEAM_SAT_MACHINE: VehicleMachineConfig = {
  action0: beamSatAction0,
  action2: beamSatAction2,
  action2ArmsAnimFlag: true,
  animFlagMask: BEAM_SAT.A2_ANIM_FLAG_MASK,
};

const ANTARES_MACHINE: VehicleMachineConfig = {
  action0: antaresAction0,
  action2: antaresAction2,
  action2ArmsAnimFlag: false, // FUN_801d615c has no +0x597 post-set
  animFlagMask: 0,
};

const DEATH_SAUCER_MACHINE: VehicleMachineConfig = {
  action0: deathSaucerAction0,
  action2: deathSaucerAction2,
  action2ArmsAnimFlag: true,
  animFlagMask: DEATH_SAUCER.A2_ANIM_FLAG_MASK,
};

export function createVehicleRootAction(
  ctx: StreamContext,
  machine: VehicleMachineConfig,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0:
        machine.action0(actor, ctx);
        return;
      case 2:
        machine.action2(actor, ctx);
        // Sub-router post-dispatch (FUN_801d5a64 / FUN_801d789c): +0x597 |= mask while
        // the armed flag +0x548 is nonzero. ANTARES (FUN_801d615c) omits this.
        if (machine.action2ArmsAnimFlag && (actor.vehCountdown548 ?? 0) !== 0) {
          actor.vehFlag597 = (actor.vehFlag597 ?? 0) | machine.animFlagMask;
        }
        return;
      default:
        return; // action 1 (and others) not surfaced in this port
    }
  };
}

/** Configure a freshly-spawned vehicle-family member (pl0e01/pl0e02/pl0e03).
 *  Stamps the borg number and wires the borg-switched bespoke root action. */
export function configureVehicleFamily(
  actor: RomActor,
  borgId: VehicleBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = VEHICLE_BORG_NUMBERS[borgId] ?? 0;
  const machine =
    borgId === "pl0e01" ? BEAM_SAT_MACHINE
      : borgId === "pl0e02" ? DEATH_SAUCER_MACHINE
        : ANTARES_MACHINE;
  actor.rootAction = createVehicleRootAction(ctx, machine);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirrors rom.selfcheck.ts style. Covers each borg's action 0 + 2
// phase transitions, the BEAM SAT hardpoint loop, ammo gates, and spawn types.
// ============================================================================
export function runVehicleSelfTests(assert: (cond: boolean, msg: string) => void): void {
  type Shot = { addr: number; type: number };

  // ------------------------------------------------------------------------
  console.log("[vehicle-borg.selfcheck] BEAM SATELLITE (pl0e01) — action 0 hardpoint loop:");

  // --- action 0: first active hardpoint fires zz_013212c_(i+0x16), +0x548=30. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e01", sctx);
    assert(a.borgNumber === 0xe01, "pl0e01 borgNumber stamped 0xe01");
    assert(a.rootAction !== null, "BEAM SAT bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.vehHardpointFlags = [0, 1, 0, 0]; // hardpoint index 1 active
    root(a); // ph0 advance
    assert(a.fbPhaseSlots[0] === 1, "action 0 ph0 (stub) advances to ph1");
    root(a); // ph1 hardpoint loop
    assert(shots.length === 1 && shots[0]!.addr === VEHICLE_HARDPOINT_SPAWNER && shots[0]!.type === 0x17,
      `action 0 ph1 fires zz_013212c_(1+0x16=0x17) for first active hardpoint (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2 && a.vehCountdown548 === BEAM_SAT.A0_HIT_COUNTDOWN,
      "action 0 ph1 advances to ph2 and seeds +0x548=30 on hit");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 29; i += 1) root(a);
    assert(a.housekeeping73f === 1, "action 0 ph2 waits while +0x548 >= 1");
    root(a); // 30th decrement → exit
    assert((a.vehCountdown548 ?? 0) < 1 && a.housekeeping73f === 0 && a.controlWord === 0,
      "action 0 ph2 exits (clears +0x73f, strips +0x5e0) when +0x548 < 1");
  }

  // --- action 0: no hardpoint active → +0x548=10, no spawn, still advances. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e01", sctx);
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.vehHardpointFlags = [0, 0, 0, 0]; // none active
    root(a); root(a); // ph0 + ph1
    assert(shots.length === 0, "action 0 ph1 spawns nothing when no hardpoint active");
    assert(a.fbPhaseSlots[0] === 2 && a.vehCountdown548 === BEAM_SAT.A0_MISS_COUNTDOWN,
      "action 0 ph1 seeds +0x548=10 when no hardpoint active");
  }

  // ------------------------------------------------------------------------
  console.log("\n[vehicle-borg.selfcheck] BEAM SATELLITE (pl0e01) — action 2 ammo-gated dual spawn:");

  // --- action 2: ammo OK → dual spawn (types 0 + 1), +0x558=180, +0x548=1, +0x597|=4. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, slot, _c, _m) => { assert(slot === 2, "action 2 ammo gate calls zz_006dbe0_(actor,2,1,1)"); return true; },
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e01", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); // ph0 advance
    assert(a.fbPhaseSlots[0] === 1, "action 2 ph0 (stub) advances to ph1");
    root(a); // ph1 spawn
    assert(shots.length === 2 && shots[0]!.addr === VEHICLE_DUAL_PORT_SPAWNER && shots[0]!.type === 0 && shots[1]!.type === 1,
      `action 2 ph1 spawns zz_01f23b0_(0) + zz_01f23b0_(1) (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2 && a.handlerTimer === BEAM_SAT.A2_OK_TIMER && a.vehCountdown548 === 1,
      "action 2 ph1 advances to ph2, seeds +0x558=180, +0x548=1");
    assert((a.vehFlag597 ?? 0) === BEAM_SAT.A2_ANIM_FLAG_MASK,
      "action 2 sub-router sets +0x597 |= 4 while +0x548 != 0");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 180; i += 1) root(a); // ph2 drain 180→0
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 2 ph2 exits when +0x558 <= 0.0 (FLOAT_8043be9c)");
  }

  // --- action 2: ammo denial → +0x558=10, no spawn, +0x597 not armed. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e01", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); root(a); // ph0 + ph1
    assert(shots.length === 0 && a.handlerTimer === BEAM_SAT.A2_FAIL_TIMER,
      "action 2 ammo denial seeds +0x558=10 and suppresses spawn");
    assert((a.vehFlag597 ?? 0) === 0, "action 2 denial leaves +0x597 clear (+0x548 == 0)");
    assert(a.fbPhaseSlots[0] === 2, "action 2 ph1 still advances on denial");
  }

  // ------------------------------------------------------------------------
  console.log("\n[vehicle-borg.selfcheck] DEATH SAUCER (pl0e02) — action 0 deploy + cancel:");

  // --- action 0: ammo OK → arm spawn(9), seeds 180/0/120/2, drains to ph2, exits. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, slot) => { assert(slot === 0, "action 0 ammo gate calls zz_006dbe0_(actor,0,1,1)"); return true; },
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e02", sctx);
    assert(a.borgNumber === 0xe02, "pl0e02 borgNumber stamped 0xe02");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // ph0 (arm + inline solve → 180→179)
    assert(shots.length === 1 && shots[0]!.addr === VEHICLE_SAUCER_DEPLOY_ARM && shots[0]!.type === 9,
      `action 0 ph0 spawns zz_01deb68_(actor,9) (got ${JSON.stringify(shots)})`);
    assert(a.handlerTimer === DEATH_SAUCER.A0_PH0_TIMER - 1,
      "action 0 ph0 inline zz_01d773c_ drains +0x558 one frame (180→179)");
    assert(a.vehDeployFrames6f7 === DEATH_SAUCER.A0_PH0_DEPLOY_FRAMES && a.vehDeploySlot6ea === DEATH_SAUCER.A0_PH0_DEPLOY_SLOT,
      "action 0 ph0 seeds +0x6f7=120 and +0x6ea=2");
    assert(a.fbPhaseSlots[0] === 1, "action 0 ph0 advances +0x540 to ph1");
    for (let i = 0; i < 178; i += 1) root(a); // ph1 solve drains 179→1
    assert(a.fbPhaseSlots[0] === 1, "action 0 ph1 waits while +0x558 > 0.0");
    root(a); // 179th ph1 drain → +0x558 = 0 → advance to ph2
    assert(a.fbPhaseSlots[0] === 2, "action 0 ph1 advances to ph2 when +0x558 <= 0.0");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 exit
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 0 ph2 exits (clears +0x73f, strips +0x5e0) via zz_006a53c_(0)");
  }

  // --- action 0: ammo denial → cancel via zz_006a53c_(10) (stateTimer = 10 + dt). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => false, onFamilyProjectile: () => {} };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e02", sctx);
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // ph0 cancel
    assert(a.stateTimer === DEATH_SAUCER.A0_CANCEL_PARAM + 1,
      "action 0 ammo denial cancels via zz_006a53c_(10) → +0x694 = 10 + dt");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action 0 cancel clears +0x73f and strips +0x5e0 action bits");
  }

  // ------------------------------------------------------------------------
  console.log("\n[vehicle-borg.selfcheck] DEATH SAUCER (pl0e02) — action 2 ammo-gated spawn:");

  // --- action 2: ammo OK → zz_01f23b0_(2), +0x558=180, +0x548=1, +0x597|=4. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e02", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); root(a); // ph0 + ph1
    assert(shots.length === 1 && shots[0]!.addr === VEHICLE_DUAL_PORT_SPAWNER && shots[0]!.type === 2,
      `action 2 ph1 spawns zz_01f23b0_(2) (got ${JSON.stringify(shots)})`);
    assert(a.handlerTimer === DEATH_SAUCER.A2_OK_TIMER && a.vehCountdown548 === 1,
      "action 2 ph1 seeds +0x558=180, +0x548=1");
    assert((a.vehFlag597 ?? 0) === DEATH_SAUCER.A2_ANIM_FLAG_MASK,
      "action 2 sub-router sets +0x597 |= 4 while +0x548 != 0");
  }

  // --- action 2: ammo denial → +0x558=10, no spawn. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e02", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); root(a);
    assert(shots.length === 0 && a.handlerTimer === DEATH_SAUCER.A2_FAIL_TIMER,
      "action 2 ammo denial seeds +0x558=10 (FLOAT_8043bf00) and suppresses spawn");
  }

  // ------------------------------------------------------------------------
  console.log("\n[vehicle-borg.selfcheck] ANTARES (pl0e03) — action 0 aimed burst (4-phase):");

  // --- action 0: ph0 setup (+0x558=30) → ph1 wait → ph2 fire → ph3 cooldown exit. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e03", sctx);
    assert(a.borgNumber === 0xe03, "pl0e03 borgNumber stamped 0xe03");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === ANTARES.A0_PH0_TIMER,
      "action 0 ph0 advances and seeds +0x558=30 (FLOAT_8043bea4)");
    for (let i = 0; i < 30; i += 1) root(a); // ph1 drain 30→0
    assert(a.fbPhaseSlots[0] === 2, "action 0 ph1 advances when +0x558 <= 0.0 (stream no-op)");
    root(a); // ph2 fire
    assert(shots.length === 1 && shots[0]!.addr === VEHICLE_ANTARES_AIMED_SPAWNER,
      `action 0 ph2 spawns FUN_801f3784(+0x14f) (got ${JSON.stringify(shots)})`);
    assert(a.handlerTimer === ANTARES.A0_PH2_OK_TIMER && a.vehCooldownTimer55c === ANTARES.A0_PH2_OK_CD,
      "action 0 ph2 success seeds +0x558=40, +0x55c=20");
    assert(a.fbPhaseSlots[0] === 3, "action 0 ph2 advances to ph3");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 40; i += 1) root(a); // ph3 cooldown drain 40→0
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 0 ph3 exits when +0x558 <= 0.0 (FLOAT_8043beac)");
  }

  // --- action 0 ph2: ammo denial → +0x558=10, +0x55c=0, no spawn. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e03", sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a);
    a.handlerTimer = 0; // force ph1 → ph2 next tick
    root(a); // ph1 advance
    root(a); // ph2 denial
    assert(shots.length === 0 && a.handlerTimer === ANTARES.A0_FAIL_TIMER && a.vehCooldownTimer55c === ANTARES.A0_THRESHOLD,
      "action 0 ph2 ammo denial seeds +0x558=10, +0x55c=0 (FLOAT_8043bec0 / beac)");
  }

  // ------------------------------------------------------------------------
  console.log("\n[vehicle-borg.selfcheck] ANTARES (pl0e03) — action 2 toggle spawn:");

  // --- action 2: ammo OK → zz_01f49c8_(+0x14e), toggle flips, +0x558=30, NO +0x597 set. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e03", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); // ph0 advance
    assert(a.fbPhaseSlots[0] === 1, "action 2 ph0 (stub) advances to ph1");
    root(a); // ph1 spawn (toggle 0)
    assert(shots.length === 1 && shots[0]!.addr === VEHICLE_ANTARES_SHOT_SPAWNER && shots[0]!.type === 0,
      `action 2 ph1 spawns zz_01f49c8_(+0x14e=0) (got ${JSON.stringify(shots)})`);
    assert(a.vehToggle14e === 1 && a.handlerTimer === ANTARES.A2_OK_TIMER,
      "action 2 ph1 toggles +0x14e 0→1 and seeds +0x558=30 (FLOAT_8043bea4)");
    assert((a.vehFlag597 ?? 0) === 0, "ANTARES action 2 sub-router does NOT set +0x597 (FUN_801d615c)");
    // Re-arm a second shot: toggle flips 1→0.
    a.fbPhaseSlots[0] = 1;
    root(a);
    assert(shots.length === 2 && shots[1]!.type === 1, "action 2 second spawn uses toggled +0x14e=1");
    assert(a.vehToggle14e === 0, "action 2 +0x14e toggles back 1→0");
  }

  // --- action 2: ammo denial → +0x558=10, no spawn. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as VehicleActor;
    configureVehicleFamily(a, "pl0e03", sctx);
    const root = a.rootAction!;
    a.actionIndex = 2;
    root(a); root(a);
    assert(shots.length === 0 && a.handlerTimer === ANTARES.A2_FAIL_TIMER,
      "action 2 ammo denial seeds +0x558=10 (FLOAT_8043bec0) and suppresses spawn");
  }
}
