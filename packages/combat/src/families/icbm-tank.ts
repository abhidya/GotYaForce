// ICBM TANK (pl0c05, ctor 0x800af538) family — bespoke 2-action port.
// @audit-ported pl0c05 action=0 variants=0,1
// @audit-ported pl0c05 action=2 variants=0,1
//
// Root dispatcher FUN_800af7f0 @0x800af7f0 (chunk_0017.c:2796):
//   `(*(code *)(&PTR_FUN_802fb300)[*(char *)(actor+0x580)])();`
//   [0] FUN_800af82c (action 0), [1] FUN_800afefc (action 2), [2] FUN_800afefc.
//
// ACTION 0 — B volley (turret-cycle). Dispatcher FUN_800af82c →
// PTR_FUN_80433a90[+0x581]: v0 → FUN_800af864 → PTR_LAB_802fb30c[+0x540];
// v1 → FUN_800afbb0 → PTR_LAB_802fb320[+0x540]. Both 5-phase, same shape:
//   ph0 setup (FUN_800af8a0/FUN_800afbec): +0x540++, +0x548 = 10.
//   ph1 wait (FUN_800af8b8/FUN_800afc04): +0x548--; FUN_800b04f8 (turret-aim
//       probe) → advance on expiry/aligned, zero the hardpoint flags.
//   ph2 fire (FUN_800af9c4/FUN_800afd10): B-held (+0x5b4&0x200 → +0x548=1) armed
//       the burst; per 6-frame cycle consume ammo slot 0 → spawn
//       zz_0082824_(nearestBarrel ? 8 : 9); advance on 2 (or 3 with B-held) shots.
//   ph3 cooldown (FUN_800afb60/FUN_800afeac): +0x548--; exit via zz_006a668_(0x10).
//   (ph4 = the next action's table start — overlap.)
//
// ACTION 2 — X-special. Dispatcher FUN_800afefc → PTR_FUN_80433a98[+0x581]:
//   v0 → FUN_800aff34 → PTR_FUN_802fb334[+0x540]; v1 → FUN_800b014c.
//   ph0 (FUN_800aff70/FUN_800b0188): +0x540++, zero +0x148/+0x146; if +0x784==0
//       → jump to ph3 (no charge); else SFX 0xbe + velocity decay + physics.
//   ph1 (FUN_800affc4/FUN_800b0254): face 0xc1 + FUN_800b0490 (turret-aligned) →
//       when both ready advance, +0x541=0, stream g4 s0; airborne sets +0x5e0|0x40.
//   ph2 (FUN_800b0064/FUN_800b0378): ammo gate slot 2 → FUN_800b6ac8 spawn +
//       +0x144=1; on contactP0==1 → ground idle; stream tick → advance.
//   ph3 (FUN_800b0118/FUN_800b045c): clear +0x73f/+0x5e0, ground idle (exit).
//
// Exit helper zz_006a668_(kind 0x10) — see beam-tank.ts / cyber-machine.ts
// cmXPhase1: reset shot channels, arm exact weapon-part animation, dispatch cue.
//
// Float constants (boot.dol, sdata2 @0x804382d8..):
//   FLOAT_804382d8 = 0.96    airborne velocity decay base
//   FLOAT_804382dc = 0.04    airborne velocity decay slope
//   FLOAT_804382e0 = 1.0     generic unity
//   FLOAT_804382e4 = 0.98    charged velocity decay base
//   FLOAT_804382e8 = 0.02    charged velocity decay slope
//   FLOAT_804382f8 = -1.0    stream rate
//   FLOAT_804382fc = 0.0     zero

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysicsFullClamp } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { allocateWeapon, groundSnapRevert, stepTargetYaw } from "../rom/helpers.js";
import { armWeaponPartAnimation } from "./shared-aimed-shot-x.js";

/** Borg number for ICBM TANK. */
export const ICBM_TANK_BORG_NUMBER = 0xc05;

// ----------------------------------------------------------------------------
// Config constants (DOL-read).
// ----------------------------------------------------------------------------
export const ICBM_TANK = {
  /** FLOAT_804382fc = 0.0 — zero scalar. */
  ZERO: 0.0,
  /** FLOAT_804382d8 = 0.96 — airborne velocity decay base. */
  AIR_DECAY_BASE: 0.9599999785423279,
  /** FLOAT_804382dc = 0.04 — airborne velocity decay slope. */
  AIR_DECAY_SLOPE: 0.04000002145767212,
  /** FLOAT_804382e4 = 0.98 — charged velocity decay base. */
  CHARGED_DECAY_BASE: 0.9800000190734863,
  /** FLOAT_804382e8 = 0.02 — charged velocity decay slope. */
  CHARGED_DECAY_SLOPE: 0.019999980926513672,
  /** FLOAT_804382e0 = 1.0 — generic unity (gravity + decay blend). */
  UNITY: 1.0,
  /** FLOAT_804382f8 = -1.0 — stream playback rate. */
  STREAM_RATE: -1.0,
  /** +0x548 turret-cycle seed (action-0 ph0). */
  CYCLE_SEED: 10,
  /** +0x548 cooldown seed (action-0 ph2). */
  COOLDOWN_SEED: 0x1e,
  /** +0x54a fire-interval countdown (6 frames). */
  FIRE_INTERVAL: 6,
  /** action-0 shot budget (2; 3 with B-held). */
  SHOT_BUDGET: 2,
  SHOT_BUDGET_HELD: 3,
  /** +0x5b4 B-held status bit (0x200). */
  B_HELD_BIT: 0x200,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 airborne/position-frozen bit. */
  AIRBORNE_BIT: 0x40,
  /** zz_006a668_ exit kind (0x10). */
  EXIT_KIND: 0x10,
  /** zz_0082824_ @0x80082824 — shot spawner (action 0). */
  SHOT_HELPER: 0x80082824,
  /** action-0 projectile records (nearest barrel → 8, else 9). */
  SHOT_NEAR: 8,
  SHOT_FAR: 9,
  /** SFX cue 0xbe — action-2 ph0 charge windup. */
  CHARGE_SFX: 0xbe,
  /** +0x784 action-2 charge-available gate. */
  CHARGE_GATE: 0x784,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface IcbmTankScratch {
  /** +0x548: turret cycle / cooldown counter. */
  icCycle548?: number;
  /** +0x144: B-held armed latch (action-0 burst extension). */
  icArmed144?: number;
  /** +0x146: hardpoint fire-interval countdown. */
  icFireInterval146?: number;
  /** +0x148: burst counter. */
  icBurstCount148?: number;
  /** +0x54a: fire-interval countdown (action-0 ph2). */
  icInterval54a?: number;
  /** +0x54c: burst counter (action-0 ph2). */
  icBurst54c?: number;
  /** +0x541: one-shot target-invalid latch. */
  icInvalid541?: number;
  /** +0x784: charge-available word (action-2 ph0 gate). */
  icChargeGate?: number;
  /** +0x144: spawn-armed latch (action-2 ph2). */
  icSpawnArmed144?: number;
  /** +0x709: contact-slow / landing flag. */
  icLanding709?: number;
}

type IcActor = RomActor & IcbmTankScratch;

function scratchOf(actor: RomActor): IcActor {
  return actor as IcActor;
}

// ----------------------------------------------------------------------------
// Exit helper — zz_006a668_(kind 0x10). See beam-tank.ts exitAction.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~ICBM_TANK.ACTION_MODE_BITS;
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  armWeaponPartAnimation(actor, ICBM_TANK.EXIT_KIND);
  dispatchFullBodyCue(actor, actor.ubCue);
}

// ----------------------------------------------------------------------------
// Nearest-barrel select — the ROM compares squared distances from +0x518
// (aim origin) to two part-anchor rows @+0x9d0 and @+0xa00. The anchors are
// host-renderer state; the port surfaces the selection via the existing
// partAimAnchors (index 0 vs 1) and defaults to the FAR barrel when unset.
// ----------------------------------------------------------------------------
function nearestBarrel(actor: RomActor): boolean {
  const a0 = actor.partAimAnchors[0];
  const a1 = actor.partAimAnchors[1];
  if (a0 && a1) {
    const d0 = (actor.aimOrigin518.x - a0.x) ** 2 + (actor.aimOrigin518.y - a0.y) ** 2 + (actor.aimOrigin518.z - a0.z) ** 2;
    const d1 = (actor.aimOrigin518.x - a1.x) ** 2 + (actor.aimOrigin518.y - a1.y) ** 2 + (actor.aimOrigin518.z - a1.z) ** 2;
    return d1 < d0; // anchor 1 nearer → barrel 1
  }
  return false;
}

// ----------------------------------------------------------------------------
// FUN_800b04f8(actor, barrel) — turret-aim probe (stream part tick). PORT
// APPROXIMATION: no-op without resident banks; returns 1 (aligned) so the
// machine advances deterministically, mirroring the beam-tank turretAimProbe.
// ----------------------------------------------------------------------------
function turretAimProbe(actor: RomActor, ctx: StreamContext): number {
  const fired = tickStream(actor, 2, ctx);
  return fired ? 1 : 0;
}

// ----------------------------------------------------------------------------
// FUN_800b0490(actor) — turret-aligned probe (action-2 ph1). PORT APPROXIMATION:
// without resident banks the probe has no event to report, so it is treated as
// aligned (returns true) — the ROM advances when BOTH the face gate and the
// turret probe succeed (bVar3 == 3); with the probe modelled as aligned the face
// gate alone drives the transition, matching the beam-tank turretAimProbe
// convention.
// ----------------------------------------------------------------------------
function turretAligned(): boolean {
  return true;
}

// ----------------------------------------------------------------------------
// ACTION 0 — B volley (turret-cycle).
// ----------------------------------------------------------------------------

function a0Phase0Setup(actor: IcActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.icCycle548 = ICBM_TANK.CYCLE_SEED;                   // +0x548 = 10
}

function a0Phase1Wait(actor: IcActor, ctx: StreamContext): void {
  actor.icCycle548 = (actor.icCycle548 ?? 0) - 1;
  if ((actor.icCycle548 ?? 0) < 1 || turretAimProbe(actor, ctx) !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.icArmed144 = 0;
    actor.icFireInterval146 = 0;
    actor.icBurstCount148 = 0;
    actor.icInterval54a = 0;
    actor.icBurst54c = 0;
  }
}

function a0Phase2Fire(actor: IcActor, ctx: StreamContext): void {
  // FUN_800af9c4/FUN_800afd10: B-held (+0x5b4 & 0x200 → +0x548 = 1) arms the
  // burst extension; per 6-frame cycle consume ammo slot 0, spawn nearest/far.
  if ((actor.statusWord5b4 & ICBM_TANK.B_HELD_BIT) !== 0) actor.icCycle548 = 1;
  if ((actor.icInterval54a ?? 0) === 0) {
    actor.icInterval54a = ICBM_TANK.FIRE_INTERVAL;
    actor.icBurst54c = (actor.icBurst54c ?? 0) + 1;
    if (allocateWeapon(actor, ctx, 0, 1, true)) {
      ctx.onFamilyProjectile?.(actor, ICBM_TANK.SHOT_HELPER,
        nearestBarrel(actor) ? ICBM_TANK.SHOT_NEAR : ICBM_TANK.SHOT_FAR);
    }
    const budget = (actor.icCycle548 ?? 0) === 0 ? ICBM_TANK.SHOT_BUDGET : ICBM_TANK.SHOT_BUDGET_HELD;
    // ROM: `if (+0x548 == 0) { if (1 < +0x54c) advance } else { +0x548=0; if (2 < +0x54c) advance }`
    // — done edge fires on the shot that reaches budget (count >= budget).
    if (budget <= (actor.icBurst54c ?? 0)) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.icCycle548 = ICBM_TANK.COOLDOWN_SEED;               // +0x548 = 0x1e
    }
  } else {
    actor.icInterval54a = (actor.icInterval54a ?? 0) - 1;
  }
}

function a0Phase3Cooldown(actor: IcActor): void {
  actor.icCycle548 = (actor.icCycle548 ?? 0) - 1;
  if ((actor.icCycle548 ?? 0) < 1) exitAction(actor);
}

/** Action-0 root — dispatcher FUN_800af82c → PTR_FUN_80433a90[+0x581]. */
function icbmTankAction0(actor: IcActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a0Phase0Setup(actor); break;
    case 1: a0Phase1Wait(actor, ctx); break;
    case 2: a0Phase2Fire(actor, ctx); break;
    case 3: a0Phase3Cooldown(actor); break;
    default: break;
  }
}

// ============================================================================
// ACTION 2 — X-special (turret charge).
// ============================================================================

/** ph0 — FUN_800aff70/FUN_800b0188: +0x540++, zero counters; charge-gate. */
function a2Phase0Setup(actor: IcActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.icBurstCount148 = 0;
  actor.icFireInterval146 = 0;
  if ((actor.icChargeGate ?? 0) === 0) {
    // +0x784 == 0 → jump straight to ph3 (no charge available).
    actor.fbPhaseSlots[0] = 3;
    return;
  }
  ctx.onPlayCue?.(actor, ICBM_TANK.CHARGE_SFX); // zz_00f036c_(0xbe)
  // Charged velocity decay: hSpeed ×= (0.02·(1−dt) + 0.98), yVel ×= (0.04·(1−dt)+0.96),
  // +0x4c/+0x50 = 0, full-clamp physics, ground snap, +0x709 = 1.
  const blend = (t: number, base: number, slope: number) => slope * (ICBM_TANK.UNITY - t) + base;
  actor.hSpeed *= blend(actor.dt, ICBM_TANK.CHARGED_DECAY_BASE, ICBM_TANK.CHARGED_DECAY_SLOPE);
  actor.yVel *= blend(actor.dt, ICBM_TANK.AIR_DECAY_BASE, ICBM_TANK.AIR_DECAY_SLOPE);
  actor.hDecel = ICBM_TANK.ZERO;
  actor.gravityCoeff = ICBM_TANK.ZERO;
  integratePhysicsFullClamp(ICBM_TANK.UNITY, actor, actor.lockYaw); // zz_0067458_(1.0)
  groundSnapRevert(actor);
  actor.icLanding709 = 1;
}

/** ph1 — FUN_800affc4/FUN_800b0254: face 0xc1 + turret-aligned → advance. */
function a2Phase1Face(actor: IcActor, ctx: StreamContext): void {
  const faced = stepTargetYawC1(actor); // zz_006660c_ + FUN_800669d0(0xc1)
  const aligned = turretAligned();
  if (faced && aligned) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.icInvalid541 = 0;
    startStream(actor, 3, 4, 0, ICBM_TANK.STREAM_RATE); // zz_004beb8_(g4 s0, mask 3)
    if ((actor.controlWord & ICBM_TANK.AIRBORNE_BIT) !== 0) {
      actor.controlWord |= ICBM_TANK.AIRBORNE_BIT; // airborne set
    }
  }
  decayAndPhysics(actor, ctx);
}

/** ph2 — FUN_800b0064/FUN_800b0378: ammo-gated spawn + stream tick + exit. */
function a2Phase2Spawn(actor: IcActor, ctx: StreamContext): void {
  if (actor.icInvalid541 === 0) {
    actor.icInvalid541 = 1;
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
      ctx.onFamilyProjectile?.(actor, 0x800b6ac8, 0); // FUN_800b6ac8 spawn
      actor.icSpawnArmed144 = 1; // +0x144 = 1
    }
  }
  if (actor.contactP0 === 1) { // +0x1cef == 1 → ground idle
    actor.housekeeping73f = 0;
    actor.controlWord &= ~ICBM_TANK.ACTION_MODE_BITS;
    romGroundIdleReturn(actor); // zz_006a474_
    actor.contactP0 = 0;
  }
  if (tickStream(actor, 3, ctx)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
  decayAndPhysics(actor, ctx);
}

/** ph3 — FUN_800b0118/FUN_800b045c: clear + exit (ground idle). */
function a2Phase3Exit(actor: IcActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~ICBM_TANK.ACTION_MODE_BITS;
  romGroundIdleReturn(actor); // zz_006a474_
}

/** Shared action-2 velocity decay + full-clamp physics tail. */
function decayAndPhysics(actor: IcActor, ctx: StreamContext): void {
  void ctx;
  const blend = (t: number, base: number, slope: number) => slope * (ICBM_TANK.UNITY - t) + base;
  actor.hSpeed *= blend(actor.dt, ICBM_TANK.AIR_DECAY_BASE, ICBM_TANK.AIR_DECAY_SLOPE);
  actor.yVel *= blend(actor.dt, ICBM_TANK.AIR_DECAY_BASE, ICBM_TANK.AIR_DECAY_SLOPE);
  integratePhysicsFullClamp(ICBM_TANK.UNITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
  actor.icLanding709 = 1;
}

/** zz_006660c_ + FUN_800669d0(actor, 0xc1) — face gate (stepTargetYaw 0xc1). */
function stepTargetYawC1(actor: RomActor): boolean {
  return stepTargetYaw(actor, 0xc1);
}

/** Action-2 root — dispatcher FUN_800afefc → PTR_FUN_80433a98[+0x581]. */
function icbmTankAction2(actor: IcActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a2Phase0Setup(actor, ctx); break;
    case 1: a2Phase1Face(actor, ctx); break;
    case 2: a2Phase2Spawn(actor, ctx); break;
    case 3: a2Phase3Exit(actor); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_800af7f0 indexes PTR_FUN_802fb300[+0x580].
// ----------------------------------------------------------------------------
export function createIcbmTankRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: icbmTankAction0(actor, ctx); return;
      case 2: icbmTankAction2(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned ICBM TANK (pl0c05). */
export function configureIcbmTankFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = ICBM_TANK_BORG_NUMBER;
  actor.rootAction = createIcbmTankRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const ICBM_TANK_CONSTANTS = ICBM_TANK;

// ============================================================================
// Self-tests — mirror the beam-tank / teleport-ninja style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runIcbmTankSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // --- configure stamps borgNumber + wires bespoke rootAction. ---
  {
    const a = createRomActor() as IcActor;
    configureIcbmTankFamily(a, makeCtx());
    assert(a.borgNumber === 0xc05, "pl0c05 borgNumber stamped 0xc05");
    assert(a.rootAction !== null, "icbm-tank bespoke rootAction wired");
  }

  // --- action 0: ph0 setup → ph1 wait → ph2 fire (2 shots) → ph3 exit. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as IcActor;
    configureIcbmTankFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances +0x540");
    assert(a.icCycle548 === ICBM_TANK.CYCLE_SEED, "action0 ph0 seeds +0x548 = 10");
    for (let i = 0; i < 10; i += 1) root(a); // ph1 wait
    assert(a.fbPhaseSlots[0] === 2, "action0 ph1 advances to ph2 after 10 frames");
    // ph2: interval 6 → shot 1 at call 1, then 6 decrements (calls 2-7), shot 2 at
    // call 8 which also hits budget 2 → advance to ph3 on the same call.
    for (let i = 0; i < 8; i += 1) root(a);
    assert(shots.length === 2, `action0 ph2 fires 2 shots (got ${shots.length})`);
    assert(shots[0]!.addr === ICBM_TANK.SHOT_HELPER && (shots[0]!.type === 8 || shots[0]!.type === 9),
      `action0 ph2 shot uses zz_0082824_(8/9) (got ${JSON.stringify(shots[0])})`);
    assert(a.fbPhaseSlots[0] === 3, "action0 ph2 advances to ph3 on burst completion");
    assert(a.icCycle548 === ICBM_TANK.COOLDOWN_SEED, "action0 ph2 seeds +0x548 = 0x1e");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 30; i += 1) root(a); // ph3 cooldown
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph3 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 2: ph0 setup → ph1 face → ph2 spawn → ph3 exit. ---
  {
    const a = createRomActor() as IcActor;
    configureIcbmTankFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.icChargeGate = 1; // +0x784 != 0 → charge path
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 ph0 advances +0x540 when charge gate set");
    // ph1: face converges (no target → heading settles) → advance.
    for (let i = 0; i < 5; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 2, "action2 ph1 advances to ph2 on face + alignment");
    root(a); // ph2 spawn
    assert(a.fbPhaseSlots[0] === 3, "action2 ph2 advances to ph3");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph3 exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action2 ph3 exits (clears +0x73f, strips +0x5e0)");
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
