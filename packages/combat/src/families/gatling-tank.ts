// GATLING TANK (pl0c01, ctor 0x800ad7cc) family — bespoke 2-action port.
// @audit-ported pl0c01 action=0 variants=0,1
// @audit-ported pl0c01 action=2 variants=0,1
//
// Root dispatcher FUN_800ada28 @0x800ada28 (chunk_0017.c:1557):
//   `(*(code *)(&PTR_FUN_802fa1a8)[*(char *)(actor+0x580)])();`
//   [0] FUN_800ada64 (action 0), [1] FUN_800ade9c (action 2), [2] FUN_800ade9c.
//
// ACTION 0 — B volley (turret-cycle). Dispatcher FUN_800ada64 →
// PTR_FUN_80433a68[+0x581]: v0 → FUN_800ada9c → PTR_LAB_802fa1b4[+0x540];
// v1 → FUN_800adc9c → PTR_LAB_802fa1c8[+0x540]. 4-phase:
//   ph0 (0x800adb08/0x800add08) wait: +0x548--, +0x146 = 1, zz_00ae45c_ turret
//       probe → advance on expiry/aligned, zero +0x548/+0x54a/+0x54c.
//   ph1 (0x800adb78/0x800add78) fire: B-held (+0x5b4&0x200 → +0x548=1) armed the
//       burst; per 2-frame cycle zz_00ae56c_ (ammo-gated zz_0082824_ with a
//       rotating record) → advance on 10 (or 50 with B-held) shots.
//   ph2 (0x800adc4c/0x800ade4c) cooldown: +0x548--; exit via zz_006a668_(0x10).
//
// ACTION 2 — X-special. Dispatcher FUN_800ade9c → PTR_FUN_80433a70[+0x581]:
//   v0 → FUN_800aded4 → PTR_LAB_802fa1dc[+0x540]; v1 → FUN_800ae118.
//   ph0 (0x800adf28/0x800ae1dc): +0x540++, +0x548=10 (charge path: set +0x5ae =
//       heading−0x8000, hSpeed=40, hDecel=−1.5, +0x6ea=1).
//   ph1 (0x800adfb4/0x800ae268): +0x548-- (or zz_00ae400_ probe) → advance,
//       +0x541=0, stream g4 s0.
//   ph2 (0x800ae034/0x800ae2e8): ammo gate slot 2 → zz_00b5878_ spawn with
//       +0x14b cursor; stream tick → advance.
//   ph3 (0x800ae0d8/0x800ae3c0): clear +0x73f/+0x5e0, ground idle (exit).
//
// Exit helper zz_006a668_(kind 0x10) — see beam-tank.ts exitAction.
//
// Float constants (boot.dol, sdata2 @0x80438270..):
//   FLOAT_80438270 = -1.0    stream rate
//   FLOAT_80438274 = 1.0     gravity
//   FLOAT_80438278 = 50.0    ph3 ground hSpeed floor
//   FLOAT_8043827c = 40.0    a2 ph0 launch hSpeed
//   FLOAT_80438280 = -0.5    a2 ph0 launch hDecel
//   FLOAT_80438284 = -1.0    a2 ph0 launch yVel
//   FLOAT_80438288 = 0.2     zz_00ae400_/zz_00ae45c_ stream rates

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { allocateWeapon } from "../rom/helpers.js";
import { armWeaponPartAnimation } from "./shared-aimed-shot-x.js";

/** Borg number for GATLING TANK. */
export const GATLING_TANK_BORG_NUMBER = 0xc01;

// ----------------------------------------------------------------------------
// Config constants (DOL-read).
// ----------------------------------------------------------------------------
export const GATLING_TANK = {
  /** FLOAT_80438270 = -1.0 — stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80438274 = 1.0 — gravity. */
  GRAVITY: 1.0,
  /** FLOAT_80438278 = 50.0 — a2 ph2 ground hSpeed floor. */
  GROUND_FLOOR: 50.0,
  /** FLOAT_8043827c = 40.0 — a2 ph0 launch hSpeed. */
  LAUNCH_HSPEED: 40.0,
  /** FLOAT_80438280 = -0.5 — a2 ph0 launch hDecel. */
  LAUNCH_HDECEL: -0.5,
  /** FLOAT_80438284 = -1.0 — a2 ph0 launch yVel / zero. */
  LAUNCH_YVEL: -1.0,
  /** +0x548 turret-cycle seed (action-0/2). */
  CYCLE_SEED: 10,
  /** +0x548 cooldown seed (action-0 ph1 / action-2 ph0). */
  COOLDOWN_SEED: 0x1e,
  /** +0x54a fire-interval countdown (2 frames). */
  FIRE_INTERVAL: 2,
  /** action-0 burst budget (10; 50 with B-held). */
  BURST_BUDGET: 10,
  BURST_HELD_BUDGET: 0x32,
  /** +0x5b4 B-held status bit. */
  B_HELD_BIT: 0x200,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** zz_006a668_ exit kind (0x10). */
  EXIT_KIND: 0x10,
  /** zz_0082824_ @0x80082824 — shot spawner (action 0). */
  SHOT_HELPER: 0x80082824,
  /** zz_00b5878_ @0x800b5878 — action-2 spawner (with +0x14b cursor). */
  A2_SPAWNER: 0x800b5878,
  /** +0x146 B-held armed latch. */
  ARMED_LATCH: 1,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface GatlingTankScratch {
  /** +0x548: turret cycle / cooldown counter. */
  gtCycle548?: number;
  /** +0x146: B-held armed latch. */
  gtArmed146?: number;
  /** +0x54a: fire-interval countdown. */
  gtInterval54a?: number;
  /** +0x54c: burst counter. */
  gtBurst54c?: number;
  /** +0x541: one-shot latch. */
  gtLatch541?: number;
  /** +0x14b: action-2 hardpoint cursor. */
  gtCursor14b?: number;
  /** +0x6ea: stream slot cursor. */
  gtSlot6ea?: number;
  /** +0x148: action-0 burst record rotation cursor (& 3). */
  gtCursor148?: number;
  /** +0x1cef: contact byte (a2 ph2 ground-exit gate). */
  gtContactP0?: number;
}

type GtActor = RomActor & GatlingTankScratch;

function scratchOf(actor: RomActor): GtActor {
  return actor as GtActor;
}

// ----------------------------------------------------------------------------
// Exit helper — zz_006a668_(kind 0x10). See beam-tank.ts exitAction.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~GATLING_TANK.ACTION_MODE_BITS;
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  armWeaponPartAnimation(actor, GATLING_TANK.EXIT_KIND);
  dispatchFullBodyCue(actor, actor.ubCue);
}

// ----------------------------------------------------------------------------
// zz_00ae400_ @ chunk_0017.c:1982 — turret-aim probe (FUN_8006cc90(0.2, actor,
// 2, 1, tbl)). PORT APPROXIMATION: no-op without banks; returns 1 (aligned).
// ----------------------------------------------------------------------------
function turretAimProbe(actor: RomActor, ctx: StreamContext): number {
  const fired = tickStream(actor, 2, ctx);
  return fired ? 1 : 0;
}

// ----------------------------------------------------------------------------
// zz_00ae45c_ @ chunk_0017.c:2000 — turret-aligned probe (three stream ticks).
// PORT APPROXIMATION: same no-op semantics (returns true so the machine
// advances deterministically).
// ----------------------------------------------------------------------------
function turretAligned(actor: RomActor, ctx: StreamContext): boolean {
  turretAimProbe(actor, ctx);
  tickStream(actor, 9, ctx);
  tickStream(actor, 6, ctx);
  return true;
}

// ----------------------------------------------------------------------------
// zz_00ae56c_ @ chunk_0017.c:2036 — action-0 burst fire. +0x148 cursor rotate
// (& 3) → ammo-gated zz_0082824_(+0x148 + 4). Returns nothing (the ROM checks
// the +0x54c burst counter at the call site).
// ----------------------------------------------------------------------------
function burstFire(actor: GtActor, ctx: StreamContext): void {
  const cursor = ((actor.gtCursor148 ?? 0) + 1) & 3;
  actor.gtCursor148 = cursor;
  if (allocateWeapon(actor, ctx, 0, 1, true)) {
    ctx.onFamilyProjectile?.(actor, GATLING_TANK.SHOT_HELPER, cursor + 4);
  }
}

// ============================================================================
// ACTION 0 — B volley (turret-cycle).
// ============================================================================

function a0Phase0Wait(actor: GtActor, ctx: StreamContext): void {
  actor.gtCycle548 = (actor.gtCycle548 ?? 0) - 1;
  actor.gtArmed146 = GATLING_TANK.ARMED_LATCH;
  if ((actor.gtCycle548 ?? 0) < 1 || turretAligned(actor, ctx)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.gtCycle548 = 0;
    actor.gtInterval54a = 0;
    actor.gtBurst54c = 0;
  }
}

function a0Phase1Fire(actor: GtActor, ctx: StreamContext): void {
  actor.gtArmed146 = GATLING_TANK.ARMED_LATCH;
  turretAimProbe(actor, ctx);
  if ((actor.statusWord5b4 & GATLING_TANK.B_HELD_BIT) !== 0) actor.gtCycle548 = 1;
  if ((actor.gtInterval54a ?? 0) === 0) {
    actor.gtInterval54a = GATLING_TANK.FIRE_INTERVAL;
    actor.gtBurst54c = (actor.gtBurst54c ?? 0) + 1;
    burstFire(actor, ctx);
    const budget = (actor.gtCycle548 ?? 0) === 0 ? GATLING_TANK.BURST_BUDGET : GATLING_TANK.BURST_HELD_BUDGET;
    if (budget <= (actor.gtBurst54c ?? 0)) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.gtCycle548 = GATLING_TANK.COOLDOWN_SEED;            // +0x548 = 0x1e
    }
  } else {
    actor.gtInterval54a = (actor.gtInterval54a ?? 0) - 1;
  }
}

function a0Phase2Cooldown(actor: GtActor): void {
  actor.gtCycle548 = (actor.gtCycle548 ?? 0) - 1;
  if ((actor.gtCycle548 ?? 0) < 1) exitAction(actor);
}

/** Action-0 root — dispatcher FUN_800ada64 → PTR_FUN_80433a68[+0x581]. */
function gatlingTankAction0(actor: GtActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a0Phase0Wait(actor, ctx); break;
    case 1: a0Phase1Fire(actor, ctx); break;
    case 2: a0Phase2Cooldown(actor); break;
    default: break;
  }
}

// ============================================================================
// ACTION 2 — X-special.
// ============================================================================

function a2Phase0Setup(actor: GtActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.gtCycle548 = GATLING_TANK.CYCLE_SEED;                // +0x548 = 10
  // charge path: +0x5ae = heading − 0x8000, hSpeed=40, hDecel=−0.5, yVel=−1.0.
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.hSpeed = GATLING_TANK.LAUNCH_HSPEED;
  actor.hDecel = GATLING_TANK.LAUNCH_HDECEL;
  actor.yVel = GATLING_TANK.LAUNCH_YVEL;
  actor.gtSlot6ea = 1;
}

function a2Phase1Charge(actor: GtActor, ctx: StreamContext): void {
  actor.gtCycle548 = (actor.gtCycle548 ?? 0) - 1;
  if ((actor.gtCycle548 ?? 0) < 1 || turretAligned(actor, ctx)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.gtLatch541 = 0;
    startStream(actor, 1, 4, 0, GATLING_TANK.STREAM_RATE); // g4 s0, mask 1
  }
}

function a2Phase2Spawn(actor: GtActor, ctx: StreamContext): void {
  if (actor.gtLatch541 === 0) {
    actor.gtLatch541 = 1;
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
      ctx.onFamilyProjectile?.(actor, GATLING_TANK.A2_SPAWNER, actor.gtCursor14b ?? 0);
      actor.gtCursor14b = ((actor.gtCursor14b ?? 0) + 1) & 1;
    }
  }
  const fired = tickStream(actor, 1, ctx);
  if (fired || actor.gtContactP0 === 1) {
    if (actor.gtContactP0 === 1) { // +0x1cef == 1 → ground idle
      actor.housekeeping73f = 0;
      actor.controlWord &= ~GATLING_TANK.ACTION_MODE_BITS;
      romGroundIdleReturn(actor);
      actor.gtContactP0 = 0;
    } else {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    }
  }
  if (actor.hSpeed < GATLING_TANK.GROUND_FLOOR) {
    actor.hSpeed = GATLING_TANK.GROUND_FLOOR;
  }
}

function a2Phase3Exit(actor: GtActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~GATLING_TANK.ACTION_MODE_BITS;
  romGroundIdleReturn(actor);
}

/** Action-2 root — dispatcher FUN_800ade9c → PTR_FUN_80433a70[+0x581]. */
function gatlingTankAction2(actor: GtActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a2Phase0Setup(actor); break;
    case 1: a2Phase1Charge(actor, ctx); break;
    case 2: a2Phase2Spawn(actor, ctx); break;
    case 3: a2Phase3Exit(actor); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_800ada28 indexes PTR_FUN_802fa1a8[+0x580].
// ----------------------------------------------------------------------------
export function createGatlingTankRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: gatlingTankAction0(actor, ctx); return;
      case 2: gatlingTankAction2(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned GATLING TANK (pl0c01). */
export function configureGatlingTankFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = GATLING_TANK_BORG_NUMBER;
  actor.rootAction = createGatlingTankRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const GATLING_TANK_CONSTANTS = GATLING_TANK;

// ============================================================================
// Self-tests — mirror the beam-tank / icbm-tank style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runGatlingTankSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // --- configure stamps borgNumber + wires bespoke rootAction. ---
  {
    const a = createRomActor() as GtActor;
    configureGatlingTankFamily(a, makeCtx());
    assert(a.borgNumber === 0xc01, "pl0c01 borgNumber stamped 0xc01");
    assert(a.rootAction !== null, "gatling-tank bespoke rootAction wired");
  }

  // --- action 0: ph0 wait → ph1 fire (10 shots) → ph2 cooldown exit. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as GtActor;
    configureGatlingTankFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0 wait (turret aligned → advance)
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances to ph1 on turret aligned");
    // ph1: shot cadence interval 2 → shot 1 at call 1, then 2-decrements → shots
    // 2-10 at calls 4,7,10,13,16,19,22,25,28. Budget 10 → done at call 28.
    for (let i = 0; i < 28; i += 1) root(a);
    assert(shots.length === 10, `action0 ph1 fires 10 shots (got ${shots.length})`);
    assert(shots[0]!.addr === GATLING_TANK.SHOT_HELPER && shots[0]!.type === 5,
      `action0 ph1 first shot zz_0082824_(+0x148+4) (got ${JSON.stringify(shots[0])})`);
    assert(a.fbPhaseSlots[0] === 2, "action0 ph1 advances to ph2 on burst completion");
    // ph2: cooldown 30 → exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 30; i += 1) root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph2 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 2: ph0 setup → ph1 charge → ph2 spawn → ph3 exit. ---
  {
    const a = createRomActor() as GtActor;
    configureGatlingTankFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 ph0 advances +0x540");
    assert(a.hSpeed === GATLING_TANK.LAUNCH_HSPEED,
      "action2 ph0 commits hSpeed = 40.0");
    // ph1: aligned → advance.
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action2 ph1 advances to ph2 on alignment");
    // ph2: stream tick false → no advance (waits); set contact to exit ground.
    a.gtContactP0 = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 ground-exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action2 ph2 ground-exits (clears +0x73f, strips +0x5e0)");
  }
}

/** Test context builder (mirrors beam-tank's makeCtx). */
function makeCtx(opts: {
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
  onPlayCue?: () => void;
} = {}): StreamContext {
  const ctx: StreamContext = {};
  if (opts.onFamilyProjectile) ctx.onFamilyProjectile = opts.onFamilyProjectile;
  if (opts.onPlayCue) ctx.onPlayCue = () => opts.onPlayCue!();
  return ctx;
}
