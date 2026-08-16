// PANTHER VEHICLE (pl0628, ctor 0x8018bb6c) family — bespoke action-0/action-3 port.
// @audit-ported pl0628 action=0 variants=0,1,2,3,4
// @audit-ported pl0628 action=3 variants=0,1,2,3,4
//
// The vehicle form of the Panther line. Root dispatcher FUN_8018bec4 (chunk_0046.c:4150)
// indexes PTR_FUN_803653f0[+0x580] (DOL dump):
//   [0] = 0x8018bf00  action 0 (timer volley — ported here)
//   [1] = 0x8018c094  action 1 (morph-back to borg 0x613 — not a player command slot)
//   [2] = 0x8018c0d8  action 2 (shared morph engine zz_017a374_ via zz_018c0f8_ — not live)
//   [3] = 0x8018c138  action 3 (single charge shot — ported here)
//
// Both ported machines share the same shape: an init block (+0x540==0) seeds a float
// timer +0x558 and a shot counter +0x6ef; a per-frame aim seek runs first; then the
// timer gates the fire. The two machines differ in shot count, timer values, spawner
// and ammo slot.
//
//   action 0 (FUN_8018bf00 → zz_018bf2c_, chunk_0046.c:4161): 5-shot volley.
//     init: +0x540=1, +0x558 = FLOAT_8043b0d0 (10.0), +0x6ef = 5.
//     fire: when +0x558 <= 0.0 → +0x558 = FLOAT_8043b0d8 (4.0), +0x6ef--; while +0x6ef
//           >= 0: ammo peek zz_006dbe0_(0,1,0) → target-visibility refresh
//           (zz_006bf80_) + ammo consume zz_006dbe0_(0,1,1) → borg-switched shot spawn
//           (0x614 → zz_0082824_ 0x34/0x35; 0x628 → 0x4f/0x50). Ammo denial or
//           shot-exhaust → exit.
//   action 3 (FUN_8018c138 → zz_018c164_, chunk_0046.c:4281): single charge shot.
//     init: +0x540=1, +0x558 = FLOAT_8043b0d0 (10.0), +0x6ef = 1.
//     fire: when +0x558 <= 0.0 → +0x558 = FLOAT_8043b0dc (16.0), +0x6ef--; while
//           +0x6ef >= 0: refresh target visibility, then borg-switched effect-child
//           spawn via zz_00c3be0_ (0x614 → 0x31/0x32; 0x628 → ammo-gated slot 2 →
//           0x51/0x52). Second expiry (shot-exhaust) → exit.
//
// Both exit paths: +0x73f = 0; +0x5e0 &= ~3; zz_006a668_(kind 4) — reset the shot
// channels (+0x1d9c/+0x1db2/+0x1db3), arm the exact weapon-part animation records
// (zz_0048d54_ kind 4), dispatch the current upper-body cue to full body
// (zz_006a6fc_(+0x5e4)); then +0x694 = FLOAT_8043b0d8 + dt (4.0 + dt).
//
// The per-tick continue path (timer still running) runs zz_0048d54_(kind 1) = the
// armWeaponPartAnimation(actor, 1) host helper (same convention as the Titan/Panther
// family gun in shared-aimed-shot-x.ts createTitanPantherGunAction0).
//
// The aim-seek zz_006eae0_ (chunk_0009.c:3592) = zz_006e998_(+0x197a) &
// zz_006e848_(+0x1976) is run every tick for its side effect on the gun-aim channels
// +0x1976/+0x197a (host-facing projectile-direction state). Neither machine branches
// on its return — the channels only feed the host spawner direction, so the port
// models them as a documented approximation (the FAMILY_GUN cone+decay pattern).
//
// Float constants (boot.dol, sdata2 @0x8043b0d0..):
//   FLOAT_8043b0d0 = 10.0   init +0x558 seed (both machines)
//   FLOAT_8043b0d4 = 0.0    fire threshold (+0x558 <= this → fire)
//   FLOAT_8043b0d8 = 4.0    action-0 inter-shot re-arm + exit cooldown seed
//   FLOAT_8043b0dc = 16.0   action-3 post-shot re-arm
//
// Spawners (shared precedent — see fighter-craft.ts / death-borg-nu.ts):
//   zz_0082824_ @0x80082824  record-table projectile spawn (SHOT_HELPER)
//   zz_00c3be0_ @0x800c3be0  per-borg effect child spawn (EFFECT_SPAWNER)

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { armWeaponPartAnimation, refreshTargetVisibility } from "./shared-aimed-shot-x.js";

// ----------------------------------------------------------------------------
// Borg number (pl0628 = 0x628). The ROM machines also serve borg 0x614 (the shared
// morph-target vehicle form) with different projectile records; pl0628 is the only
// registered roster member of this ctor, so the 0x628 branch is what this port fires.
// ----------------------------------------------------------------------------
export const PANTHER_VEHICLE_BORG_NUMBER = 0x628;

// ----------------------------------------------------------------------------
// Config constants (DOL-read this session).
// ----------------------------------------------------------------------------
export const PANTHER_VEHICLE = {
  /** FLOAT_8043b0d0 = 10.0 — init +0x558 timer seed (both machines). */
  INIT_TIMER: 10.0,
  /** FLOAT_8043b0d4 = 0.0 — fire threshold (+0x558 <= this → fire). */
  FIRE_THRESHOLD: 0.0,
  /** FLOAT_8043b0d8 = 4.0 — action-0 inter-shot re-arm + exit +0x694 seed. */
  SHOT_INTERVAL: 4.0,
  /** FLOAT_8043b0dc = 16.0 — action-3 post-shot re-arm. */
  CHARGE_RECOVERY: 16.0,
  /** +0x6ef initial shot counter: 5 (action 0 volley) / 1 (action 3 charge). */
  VOLLEY_SHOT_COUNT: 5,
  CHARGE_SHOT_COUNT: 1,
  /** Ammo slot 0 — action-0 shot gate (zz_006dbe0_(0,1,0) peek then (0,1,1) consume). */
  VOLLEY_AMMO_SLOT: 0,
  /** Ammo slot 2 — action-3 charge gate (zz_006dbe0_(2,1,1) consume). */
  CHARGE_AMMO_SLOT: 2,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** zz_0082824_ @0x80082824 — record-table projectile spawn (action 0). */
  SHOT_HELPER: 0x80082824,
  /** zz_00c3be0_ @0x800c3be0 — per-borg effect child spawn (action 3). */
  EFFECT_SPAWNER: 0x800c3be0,
  /** Action-0 projectile records for borg 0x628 (zz_0082824_ args). */
  VOLLEY_RECORDS: [0x4f, 0x50],
  /** Action-3 effect records for borg 0x628 (zz_00c3be0_ args). */
  CHARGE_RECORDS: [0x51, 0x52],
  /** exit-kind passed to zz_006a668_ (reset shot channels + arm kind 4). */
  EXIT_KIND: 4,
  /** continue-kind passed to zz_0048d54_ (arm kind 1). */
  CONTINUE_KIND: 1,
  /** FAMILY_GUN aim-decay (0.96) — see createTitanPantherGunAction0. */
  AIM_DECAY: 0.9599999785423279,
  /** FAMILY_GUN aim cone (±0x4800 BAM) outside which the channel decays. */
  AIM_CONE: 0x4800,
  /** FAMILY_GUN per-tick aim step clamp (0x400 BAM). */
  AIM_STEP: 0x400,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface PantherVehicleScratch {
  /** +0x6ef: shot counter (5 = volley, 1 = charge). */
  pvShotCount?: number;
  /** +0x197a: gun-aim yaw channel (host-facing; seek approximation). */
  pvAim197a?: number;
  /** +0x1976: gun-aim pitch channel (host-facing; seek approximation). */
  pvAim1976?: number;
}

type PantherVehicleActor = RomActor & PantherVehicleScratch;

function scratchOf(actor: RomActor): PantherVehicleActor {
  return actor as PantherVehicleActor;
}

// ----------------------------------------------------------------------------
// zz_006eae0_(actor, &+0x1976, &+0x197a, 0) — chunk_0009.c:3592. Runs the two gun-aim
// channel seeks every tick; the machine discards the ANDed return. PORT APPROXIMATION:
// follows the FAMILY_GUN cone+decay pattern (shared-aimed-shot-x.ts) on both channels —
// the exact zz_006e998_/zz_006e848_ seek math (desc+0xae step × dt, ±0x2000 pitch
// clamp) is host-facing projectile-direction state, not branch logic.
// ----------------------------------------------------------------------------
function seekAimChannels(actor: PantherVehicleActor): void {
  const targetYaw = Math.round(
    (Math.atan2(actor.pos.x - actor.targetCache5e8.x, actor.pos.z - actor.targetCache5e8.z) /
      (Math.PI * 2)) *
      0x10000,
  );
  for (const key of ["pvAim1976", "pvAim197a"] as const) {
    const cur = actor[key] ?? 0;
    const cone = toS16(targetYaw - actor.heading);
    if (cone >= -PANTHER_VEHICLE.AIM_CONE && cone <= PANTHER_VEHICLE.AIM_CONE) {
      const delta = Math.max(
        -PANTHER_VEHICLE.AIM_STEP,
        Math.min(PANTHER_VEHICLE.AIM_STEP, toS16(cone - cur)),
      );
      actor[key] = toS16(cur + delta);
    } else {
      actor[key] = Math.trunc(toS16(cur) * PANTHER_VEHICLE.AIM_DECAY);
    }
  }
}

function toS16(v: number): number {
  let s = v & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return s;
}

// ----------------------------------------------------------------------------
// zz_006a668_(..., kind 4) + the caller's +0x694 = 4.0 + dt — the shared exit helper.
// Resets the shot channels, arms the exact weapon-part animation (zz_0048d54_ kind 4),
// dispatches the current upper-body cue to full body (zz_006a6fc_(+0x5e4)), then seeds
// the cooldown +0x694 = FLOAT_8043b0d8 + dt. (The caller strips +0x5e0 action bits
// first, so zz_006a668_'s internal cooldown guard is inert — the caller's store wins.)
// ----------------------------------------------------------------------------
function exitMachine(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~PANTHER_VEHICLE.ACTION_MODE_BITS;
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  armWeaponPartAnimation(actor, PANTHER_VEHICLE.EXIT_KIND);
  dispatchFullBodyCue(actor, actor.ubCue);
  actor.stateTimer = PANTHER_VEHICLE.SHOT_INTERVAL + actor.dt;
}

// ----------------------------------------------------------------------------
// Action 0 — FUN_8018bf00 → zz_018bf2c_ (chunk_0046.c:4161). 5-shot ammo-gated volley.
//   wrapper: +0x18da (steerYaw) halved every dispatched tick (FUN_8018bf00:4167).
// ----------------------------------------------------------------------------
function action0(actor: PantherVehicleActor, ctx: StreamContext): void {
  actor.steerYaw = toS16(actor.steerYaw) >> 1; // wrapper: +0x18da >> 1

  // init block (+0x540 == 0): +0x540=1, +0x558 = 10.0, +0x6ef = 5.
  if ((actor.fbPhaseSlots[0] ?? 0) === 0) {
    actor.fbPhaseSlots[0] = 1;
    actor.handlerTimer = PANTHER_VEHICLE.INIT_TIMER;
    actor.pvShotCount = PANTHER_VEHICLE.VOLLEY_SHOT_COUNT;
  }

  seekAimChannels(actor); // zz_006eae0_(actor, &+0x1976, &+0x197a, 0)

  if (actor.handlerTimer <= PANTHER_VEHICLE.FIRE_THRESHOLD) {
    // Fire: re-arm 4.0, decrement shot counter.
    actor.handlerTimer = PANTHER_VEHICLE.SHOT_INTERVAL;
    const shots = (actor.pvShotCount ?? 0) - 1;
    actor.pvShotCount = shots;
    if (shots >= 0) {
      // ammo peek zz_006dbe0_(0,1,0) → refresh visibility + ammo consume (0,1,1) → spawn.
      if (allocateWeapon(actor, ctx, PANTHER_VEHICLE.VOLLEY_AMMO_SLOT, 1, false)) {
        refreshTargetVisibility(actor);
        ctx.onRefreshTargetVisibility?.(actor);
        if (allocateWeapon(actor, ctx, PANTHER_VEHICLE.VOLLEY_AMMO_SLOT, 1, true)) {
          for (const record of PANTHER_VEHICLE.VOLLEY_RECORDS) {
            ctx.onFamilyProjectile?.(actor, PANTHER_VEHICLE.SHOT_HELPER, record);
          }
        }
        armWeaponPartAnimation(actor, PANTHER_VEHICLE.CONTINUE_KIND);
        return;
      }
    }
    // Ammo denied or shot-exhaust → exit.
    exitMachine(actor);
    return;
  }

  // Timer still running: +0x558 -= dt; continue (arm kind 1).
  actor.handlerTimer -= actor.dt;
  armWeaponPartAnimation(actor, PANTHER_VEHICLE.CONTINUE_KIND);
}

// ----------------------------------------------------------------------------
// Action 3 — FUN_8018c138 → zz_018c164_ (chunk_0046.c:4281). Single charge shot.
//   wrapper: +0x18da (steerYaw) halved every dispatched tick (FUN_8018c138:4287).
// ----------------------------------------------------------------------------
function action3(actor: PantherVehicleActor, ctx: StreamContext): void {
  actor.steerYaw = toS16(actor.steerYaw) >> 1; // wrapper: +0x18da >> 1

  // init block (+0x540 == 0): +0x540=1, +0x558 = 10.0, +0x6ef = 1.
  if ((actor.fbPhaseSlots[0] ?? 0) === 0) {
    actor.fbPhaseSlots[0] = 1;
    actor.handlerTimer = PANTHER_VEHICLE.INIT_TIMER;
    actor.pvShotCount = PANTHER_VEHICLE.CHARGE_SHOT_COUNT;
  }

  seekAimChannels(actor); // zz_006eae0_(actor, &+0x1976, &+0x197a, 0)

  if (actor.handlerTimer <= PANTHER_VEHICLE.FIRE_THRESHOLD) {
    // Fire: re-arm 16.0, decrement shot counter.
    actor.handlerTimer = PANTHER_VEHICLE.CHARGE_RECOVERY;
    const shots = (actor.pvShotCount ?? 0) - 1;
    actor.pvShotCount = shots;
    if (shots < 0) {
      // Shot-exhaust → exit and return (the ROM returns without the continue tail).
      exitMachine(actor);
      return;
    }
    // Refresh target visibility, then borg-switched effect spawn (ammo-gated slot 2).
    refreshTargetVisibility(actor);
    ctx.onRefreshTargetVisibility?.(actor);
    if (allocateWeapon(actor, ctx, PANTHER_VEHICLE.CHARGE_AMMO_SLOT, 1, true)) {
      for (const record of PANTHER_VEHICLE.CHARGE_RECORDS) {
        ctx.onFamilyProjectile?.(actor, PANTHER_VEHICLE.EFFECT_SPAWNER, record);
      }
    }
  } else {
    // Timer still running: +0x558 -= dt.
    actor.handlerTimer -= actor.dt;
  }
  // continue (arm kind 1).
  armWeaponPartAnimation(actor, PANTHER_VEHICLE.CONTINUE_KIND);
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_8018bec4 indexes PTR_FUN_803653f0[+0x580]. Actions 1/2
// (morph-back / shared morph engine) are not player command slots for pl0628 and keep
// the generic fallback (null), matching the audit's live-slot set.
// ----------------------------------------------------------------------------
export function createPantherVehicleRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: PantherVehicleActor) => void) | null> = [
    (a) => action0(a, ctx),
    null, // 1: 0x8018c094 — morph-back, not live
    null, // 2: 0x8018c0d8 — shared morph engine, not live
    (a) => action3(a, ctx),
    null,
  ];
  return (base: RomActor) => {
    const actor = scratchOf(base);
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned PANTHER VEHICLE (pl0628). Stamps the borg number and
 *  wires the bespoke action-0 volley + action-3 charge machines. */
export function configurePantherVehicleFamily(
  actor: RomActor,
  borgId: "pl0628",
  ctx: StreamContext,
): void {
  void borgId;
  actor.borgNumber = PANTHER_VEHICLE_BORG_NUMBER;
  actor.rootAction = createPantherVehicleRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const PANTHER_VEHICLE_CONSTANTS = PANTHER_VEHICLE;

// ============================================================================
// Self-tests — mirrors the fighter-craft / victory-jet style. Covers both machines'
// init, timer-gated fire, ammo gates, borg-switched spawn records, and the exit path.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runPantherVehicleSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // ----------------------------------------------------------------------------
  console.log("\n[panther-vehicle.selfcheck] pl0628 action 0 — 5-shot ammo-gated volley:");

  // --- init + first fire: 10.0 windup, then 4.0 re-arm, ammo peek+consume, spawn 0x4f/0x50. ---
  {
    const shots: Shot[] = [];
    const gates: Array<[number, number]> = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, slot, _count, mode) => {
        gates.push([slot, mode ?? 0]);
        return true;
      },
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    assert(a.borgNumber === 0x628, "pl0628 borgNumber stamped 0x628");
    assert(a.rootAction !== null, "panther-vehicle bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // init (windup 10.0) — the same dispatch drains by dt
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === 10.0 - 1 && a.pvShotCount === 5,
      "action 0 init seeds +0x558=10.0, +0x6ef=5, +0x540=1");
    assert(shots.length === 0, "action 0 does not fire during windup");

    // 9 more ticks drain the timer 9.0 → 0.0 (no fire at 0.0 yet).
    for (let i = 0; i < 9; i += 1) root(a);
    assert(a.handlerTimer === 0.0 && shots.length === 0,
      "action 0 drains +0x558 by dt during windup");

    // Next dispatch: timer <= 0 → re-arm 4.0, shot 5→4, peek(0,1,0)+consume(0,1,1), spawn.
    root(a);
    assert(a.handlerTimer === 4.0 && a.pvShotCount === 4,
      "action 0 re-arms +0x558=4.0 and decrements +0x6ef to 4 on fire");
    assert(shots.length === 2
        && shots[0]!.addr === PANTHER_VEHICLE.SHOT_HELPER && shots[0]!.type === 0x4f
        && shots[1]!.addr === PANTHER_VEHICLE.SHOT_HELPER && shots[1]!.type === 0x50,
      `action 0 spawns zz_0082824_(0x4f,0x50) (got ${JSON.stringify(shots)})`);
    assert(gates.length === 2 && gates[0]![0] === 0 && gates[0]![1] === 0 && gates[1]![1] === 1,
      "action 0 gates ammo slot 0 peek(0) then consume(1)");
  }

  // --- full volley: init drains 10.0→0.0 (10 dispatches incl. init), fires 5 shots,
  //     then shot-exhaust exits. Subsequent shots cadence at 4.0 (4 drains + 1 fire). ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // init → timer 9.0
    assert(shots.length === 0, "action 0 volley does not fire during the init windup");
    // Drain the remaining 9.0 → 0.0 (9 drains); no fire until the timer is <= 0 at a
    // dispatch start, so this dispatch (timer 1.0) drains to 0.0.
    for (let f = 0; f < 9; f += 1) root(a);
    assert(shots.length === 0 && a.handlerTimer === 0.0, "action 0 timer drained to 0.0");
    // Fire 1: timer 0.0 <= 0 → re-arm 4.0, shot 5→4, spawn 2.
    root(a);
    assert(shots.length === 2 && a.handlerTimer === 4.0 && a.pvShotCount === 4,
      "action 0 fires shot 1 (2 projectiles, +0x558=4.0, +0x6ef=4)");
    // Fires 2..5: each needs 5 dispatches (4 drains from 4.0→0.0 + 1 fire dispatch).
    for (let i = 1; i < 5; i += 1) {
      for (let f = 0; f < 5; f += 1) root(a);
      assert(shots.length === (i + 1) * 2, `action 0 fired ${i + 1} shots`);
    }
    // 6th expiry: shot 0 → -1 < 0 → exit (no spawn).
    for (let f = 0; f < 5; f += 1) root(a);
    assert(shots.length === 10, "action 0 fires 10 projectiles total (5 shots × 2)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action 0 exits (clears +0x73f, strips +0x5e0 action bits) on shot-exhaust");
    assert(a.stateTimer === 4.0 + 1, "action 0 exit seeds +0x694 = 4.0 + dt (FLOAT_8043b0d8)");
  }

  // --- ammo denial at peek: no spawn, immediate exit. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // init windup 10.0
    for (let f = 0; f < 10; f += 1) root(a); // windup drain → fire
    assert(shots.length === 0, "action 0 ammo denial suppresses spawn");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action 0 ammo denial exits immediately");
  }

  // ----------------------------------------------------------------------------
  console.log("\n[panther-vehicle.selfcheck] pl0628 action 3 — single charge shot:");

  // --- init + windup + first fire: 10.0 → 16.0, ammo slot 2 consume, spawn 0x51/0x52. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, slot, _c, mode) => {
        assert(slot === 2, "action 3 ammo gate uses slot 2");
        assert(mode === 1, "action 3 ammo gate consumes (zz_006dbe0_(2,1,1))");
        return true;
      },
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    root(a); // init (windup 10.0) — the same dispatch drains by dt
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === 10.0 - 1 && a.pvShotCount === 1,
      "action 3 init seeds +0x558=10.0, +0x6ef=1, +0x540=1");
    // Drain 9.0 → 0.0 (9 more dispatches; no fire until timer <= 0 at dispatch start).
    for (let f = 0; f < 9; f += 1) root(a);
    assert(shots.length === 0 && a.handlerTimer === 0.0,
      "action 3 windup drains +0x558 to 0.0 without firing");
    // Fire: timer 0.0 <= 0 → re-arm 16.0, shot 1→0, ammo slot 2 consume, spawn 0x51/0x52.
    root(a);
    assert(a.handlerTimer === 16.0 && a.pvShotCount === 0,
      "action 3 re-arms +0x558=16.0 and decrements +0x6ef to 0 on fire");
    assert(shots.length === 2
        && shots[0]!.addr === PANTHER_VEHICLE.EFFECT_SPAWNER && shots[0]!.type === 0x51
        && shots[1]!.addr === PANTHER_VEHICLE.EFFECT_SPAWNER && shots[1]!.type === 0x52,
      `action 3 spawns zz_00c3be0_(0x51,0x52) (got ${JSON.stringify(shots)})`);
  }

  // --- second expiry (shot-exhaust) exits; ammo slot-2 denial still consumes-gates. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // init → 9.0
    for (let f = 0; f < 9; f += 1) root(a); // drain to 0.0
    root(a); // first fire (shots 2), re-arm 16.0
    assert(shots.length === 2, "action 3 first fire spawns 2 effects");
    // Drain 16.0 → 0.0 (16 dispatches), then next dispatch (timer 0.0) exits.
    for (let f = 0; f < 16; f += 1) root(a);
    assert(a.handlerTimer === 0.0 && shots.length === 2,
      "action 3 recovery drains +0x558 to 0.0 without re-firing");
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action 3 exits on shot-exhaust (second expiry)");
    assert(a.stateTimer === 4.0 + 1, "action 3 exit seeds +0x694 = 4.0 + dt");
  }

  // ----------------------------------------------------------------------------
  console.log("\n[panther-vehicle.selfcheck] non-live action indices fall through:");
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as PantherVehicleActor;
    configurePantherVehicleFamily(a, "pl0628", sctx);
    const root = a.rootAction!;
    a.actionIndex = 1; // morph-back — not live
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action 1 (morph-back) no-ops in this port");
  }
}
