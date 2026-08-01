// DEATH BORG CHI (pl0f04, ctor 0x801f0c68) death-borg-chi family — bespoke action-0 port.
//
// Standalone module (does NOT import death-borg-nu.ts). The ctor wires the root
// dispatcher FUN_801f0e8c (chunk_0060.c:3493), which indexes PTR_FUN_80435ba8[+0x580]
// (actionIndex). Only actionIndex 0 routes to the phase machine; other action rows
// fall through to the generic combat layer (null rootAction). The action-0 sub-router
// FUN_801f0efc (chunk_0060.c:3515) indexes PTR_LAB_803a15b8[+0x540] (fbPhaseSlots[0]).
//
//   action 0 table @0x803a15b8 = [0x801f0f38(6i stub), FUN_801f0f50(89i),
//                                 FUN_801f10b4(53i), FUN_801f1188(62i)] — 4 phases.
//
// Source: research/decomp/ghidra-export/chunk_0060.c:3515-3660. ph0 is a 6-instruction
// setup stub NOT emitted as a decomp header; decoded from boot.dol raw bytes this
// session (rtoc back-solved to 0x8043ea20 from FUN_801f10b4's lfs offsets):
//   +0: lbz r4, 0x540(r3)        ; load phase cursor
//   +4: lfs f0, -0x2500(r2)      ; f0 = FLOAT_8043c520 (30.0)
//   +8: addi r0, r4, 1           ; phase + 1
//  +12: stb r0, 0x540(r3)        ; +0x540 = phase + 1 (advance)
//  +16: stfs f0, 0x558(r3)       ; +0x558 = 30.0 (handlerTimer seed)
//  +20: blr
//
// The four phases:
//   0 setup — advance +0x540; +0x558 = 30.0 (FLOAT_8043c520).
//   1 aim   — converge +0x144 (a signed BAM aim offset) toward the target delta from
//             zz_00853ec_(actor, 0x17) (clamped to [-0x3800, 0x1800]) in ±0x180 steps
//             with a ±0xc0 deadband; latch bVar4 bits: bit0 = aim-ready
//             (FUN_800669d0(actor, 0xc1)), bit1 = +0x144 reached target. Drain +0x558
//             by dt; advance when (bVar4 == 3) OR +0x558 <= 0.0. Also runs the
//             +0x5e0&0x40 ground-snap branch (zz_00677b0_). +0x146 = 1.
//   2 dive  — ammo gate zz_006dbe0_(actor,0,1,1): on denial clear +0x709/+0x73f, strip
//             +0x5e0 action bits, exit via zz_006a474_ (TODO: cue dispatch unsurfaced).
//             On success: advance +0x540, zz_0084600_(actor,0x17) (sound/aim reset),
//             +0x5e0 |= 0x40, flip lockYaw (+0x5ae = +0x72 − 0x8000), seed the dive
//             scalars hSpeed/yVel = 20.0 (FLOAT_8043c528), hDecel = -0.3
//             (FLOAT_8043c52c), +0x50 = descriptor handlerData6c, +0x558 = 60.0
//             (FLOAT_8043c530). +0x146 = 0; +0x709 |= 1.
//   3 land  — integrate physics (zz_0067458_(1.0, actor, lockYaw)); drain +0x558 by dt;
//             if grounded (zz_00677b0_): land branch — spawn afterimage (zz_00b2190_(2)),
//             reset steerYaw/vel scalars to FLOAT_8043c524 (0.0), clear pose accum
//             (+0x7c/+0x7e/+0x80), clear +0x709/+0x73f, strip +0x5e0, exit via
//             zz_006a474_ (TODO). Else if +0x558 <= 0.0: clear +0x709/+0x73f, strip
//             +0x5e0, exit via zz_006a5a4_ (TODO). Else: +0x18da -= 0x1000 (dive pitch).
//
// Float constants (read from boot.dol via v2f, rtoc=0x8043ea20):
//   FLOAT_8043c520 = 30.0   ph0 handlerTimer seed
//   FLOAT_8043c524 = 0.0    ph1/ph3 threshold; ph3 land velocity/steerYaw reset
//   FLOAT_8043c528 = 20.0   ph2 dive hSpeed/yVel seed
//   FLOAT_8043c52c = -0.3   ph2 dive hDecel seed
//   FLOAT_8043c530 = 60.0   ph2 dive handlerTimer seed
//   FLOAT_8043c534 = 1.0    ph3 physics gravity arg (zz_0067458_)
//
// NOTE on partial port: ph1's aim helpers zz_00853ec_ (target angle delta) and
// FUN_800669d0 (aim-readiness) are not yet ported; ph1 uses the host lock-target via
// stepTargetYaw where possible and otherwise advances on the timer threshold (the
// exact ROM fallback path). The exit helpers zz_006a474_ / zz_006a5a4_
// (chunk_0009.c siblings of zz_006a53c_) are also not yet surfaced — the port clears
// the +0x73f/+0x5e0 bookkeeping exactly (the ROACH convention) and cites the missing
// cue dispatch as a TODO.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon } from "../rom/helpers.js";
import { integratePhysics } from "../rom/physics.js";
import { stepAfterimage } from "../rom/helpers.js";
import { stepTargetYaw } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Borg number for DEATH BORG CHI. */
const DEATH_BORG_CHI_NUMBER = 0xf04;

// EFFECT_SPAWNER re-declared locally (cited from death-borg-nu.ts:48) to keep this
// module standalone. The CHI ph2/ph3 exits do NOT spawn via this address, but it is
// exported for parity with the sibling death-borg family modules.
/** zz_00c3be0_ — per-borg effect spawn (cited: death-borg-nu.ts:48). Unused by CHI's
 *  phase machine but exported for family-module parity. */
const EFFECT_SPAWNER = 0x800c3be0;

// ----------------------------------------------------------------------------
// Config constants (DOL-read this session; sdata2 @0x8043c5xx).
// ----------------------------------------------------------------------------
const CHI = {
  /** FLOAT_8043c520 = 30.0 — ph0 handlerTimer seed. */
  PH0_TIMER_SEED: 30.0,
  /** FLOAT_8043c524 = 0.0 — ph1/ph3 threshold; ph3 land reset value. */
  THRESHOLD: 0.0,
  /** FLOAT_8043c528 = 20.0 — ph2 dive hSpeed/yVel seed. */
  DIVE_SPEED: 20.0,
  /** FLOAT_8043c52c = -0.3 — ph2 dive hDecel seed. */
  DIVE_DECEL: -0.3,
  /** FLOAT_8043c530 = 60.0 — ph2 dive handlerTimer seed. */
  DIVE_TIMER_SEED: 60.0,
  /** FLOAT_8043c534 = 1.0 — ph3 physics gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 position-frozen bit set by ph2 (gates ph1/ph3 ground-snap branch). */
  POSITION_FROZEN_BIT: 0x40,
  /** ph1 +0x144 convergence step (BAM16 per frame toward target). */
  AIM_STEP: 0x180,
  /** ph1 +0x144 deadband (snap-to-target window). */
  AIM_DEADBAND: 0xc0,
  /** ph1 zz_00853ec_ clamp low (BAM16). */
  AIM_CLAMP_LOW: -0x3800,
  /** ph1 zz_00853ec_ clamp high (BAM16). */
  AIM_CLAMP_HIGH: 0x1800,
  /** ph3 airborne +0x18da dive-pitch decrement (BAM16 per frame). */
  DIVE_PITCH_STEP: -0x1000,
  /** zz_006dbe0_ ammo args for ph2 dive gate: (widx=0, count=1, consumeMode=1). */
  AMMO_WIDX: 0,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface DeathBorgChiScratch {
  /** +0x144: signed BAM aim offset converged in ph1; latched to 1 in ph2 (no — ph2
   *  uses +0x144 differently; the +0x144 short carries the dive yaw offset). */
  chiAimOffset144?: number;
  /** +0x146: ph1 sets 1 (aim-active flag); ph2 clears to 0. */
  chiAimActive146?: number;
  /** +0x18da: dive pitch yaw decremented each airborne ph3 frame. */
  steerYaw18da?: number;
  /** +0x709: contact-slow flag byte (ORed with 1 by ph2/ph3 ground-snap; cleared at exit). */
  contactSlow709?: number;
}

type ChiActor = RomActor & DeathBorgChiScratch;

function scratchOf(actor: RomActor): ChiActor {
  return actor as ChiActor;
}

/** Common exit tail: clear +0x709, +0x73f, strip +0x5e0 action bits.
 *  TODO(rom): zz_006a474_ / zz_006a5a4_ @ chunk_0009.c also dispatch a full-body cue
 *  (the exact cue id is unsurfaced); the bookkeeping clear matches the ROACH convention. */
function chiExitClear(actor: ChiActor): void {
  actor.contactSlow709 = 0;
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~CHI.ACTION_MODE_BITS;
}

// ----------------------------------------------------------------------------
// Phase 0 — setup stub @0x801f0f38 (6 instrs, decoded from boot.dol bytes this session).
// ----------------------------------------------------------------------------
function chiPhase0Setup(actor: ChiActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = CHI.PH0_TIMER_SEED;                  // +0x558 = 30.0
}

// ----------------------------------------------------------------------------
// Phase 1 — aim. FUN_801f0f50 @ chunk_0060.c:3526 (89 instrs).
// ----------------------------------------------------------------------------
function chiPhase1Aim(actor: ChiActor): void {
  actor.chiAimActive146 = 1; // +0x146 = 1
  // zz_006660c_(actor) — host aim-yaw step (port: helpers.stepTargetYaw, aimType 0xc1).
  stepTargetYaw(actor, 0xc1);
  // FUN_800669d0(actor, 0xc1) — aim-readiness (bit0 of bVar4). The readiness gate is
  // the host's stepTargetYaw return (true when heading settled within turn-step).
  // TODO(rom): FUN_800669d0 has additional target-loss logic; approximated by the
  // stepTargetYaw settlement here.
  // zz_00853ec_(actor, 0x17) — target angle delta clamped to [-0x3800, 0x1800].
  // TODO(rom): zz_00853ec_ unsurfaced; without a host lock-target the delta is 0 and
  // the +0x144 convergence is a no-op (already at target). With a target, port the
  // real delta once zz_00853ec_ lands.
  const target = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  let aimDelta = 0;
  if (target) {
    // Approximate zz_00853ec_(actor, 0x17): target-relative yaw delta in BAM16.
    const dx = target.x - actor.aimOrigin518.x;
    const dz = target.z - actor.aimOrigin518.z;
    aimDelta = Math.round(Math.atan2(dx, dz) / (Math.PI * 2) * 0x10000);
    if (aimDelta >= 0x8000) aimDelta -= 0x10000;
    if (aimDelta < CHI.AIM_CLAMP_LOW) aimDelta = CHI.AIM_CLAMP_LOW;
    else if (aimDelta > CHI.AIM_CLAMP_HIGH) aimDelta = CHI.AIM_CLAMP_HIGH;
  }
  // Converge +0x144 toward aimDelta in ±0x180 steps with ±0xc0 deadband (chunk_0060.c:3548-3560).
  const cur = actor.chiAimOffset144 ?? 0;
  let next = cur;
  if (cur < aimDelta) {
    next = cur + CHI.AIM_STEP;
    if (aimDelta - CHI.AIM_DEADBAND <= next) next = aimDelta;
  } else if (aimDelta < cur) {
    next = cur - CHI.AIM_STEP;
    if (next <= aimDelta + CHI.AIM_DEADBAND) next = aimDelta;
  }
  actor.chiAimOffset144 = next;
  // bVar4 bit1 when +0x144 reached the target. bVar4 bit0 is the FUN_800669d0
  // aim-readiness probe — unsurfaced, so it stays 0 (the actor is never "aim-ready"
  // without the helper). bVar4 can therefore never equal 3 and the advance falls to
  // the +0x558 <= 0.0 timer gate (the exact ROM fallback when the probe returns 0).
  const aimReady = false; // TODO(rom): FUN_800669d0(actor, 0xc1) unsurfaced (chunk_0008.c).

  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  if ((aimReady && next === aimDelta) || actor.handlerTimer <= CHI.THRESHOLD) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.fbPhaseSlots[1] = 0; // +0x541 = 0
  }
  // +0x5e0 & 0x40 ground-snap branch: zz_00677b0_(actor) probe; clears the frozen bit
  // when ground is found. Port: defer to groundClamp via physicsRuntime when present.
  if ((actor.controlWord & CHI.POSITION_FROZEN_BIT) !== 0) {
    actor.contactSlow709 = (actor.contactSlow709 ?? 0) | 1;
    // zz_00677b0_(actor) returns nonzero when grounded → clear the frozen bit + +0x709.
    const grounded = actor.physicsRuntime?.isSupported?.(actor.pos.x, actor.pos.z) ?? false;
    if (grounded) {
      actor.controlWord = actor.controlWord & ~CHI.POSITION_FROZEN_BIT;
      actor.contactSlow709 = 0;
    }
  }
}

// ----------------------------------------------------------------------------
// Phase 2 — dive arm. FUN_801f10b4 @ chunk_0060.c:3582 (53 instrs).
// ----------------------------------------------------------------------------
function chiPhase2Dive(actor: ChiActor, ctx: StreamContext): void {
  actor.chiAimActive146 = 0; // +0x146 = 0
  const ammoOk = allocateWeapon(actor, ctx, CHI.AMMO_WIDX, 1, true); // zz_006dbe0_(actor,0,1,1)
  if (!ammoOk) {
    // Denied: clear +0x709/+0x73f, strip +0x5e0, exit via zz_006a474_.
    actor.contactSlow709 = 0;
    chiExitClear(actor);
    // TODO(rom): zz_006a474_ cue dispatch unsurfaced (chunk_0009.c sibling of zz_006a53c_).
    return;
  }
  // Success: advance + arm the dive.
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  // zz_0084600_(actor, 0x17) — sound/aim reset (host hook); no port-side effect here.
  actor.controlWord = actor.controlWord | CHI.POSITION_FROZEN_BIT; // +0x5e0 |= 0x40
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff; // +0x5ae = +0x72 − 0x8000
  actor.hSpeed = CHI.DIVE_SPEED;  // +0x44 = 20.0
  actor.hDecel = CHI.DIVE_DECEL;  // +0x4c = -0.3
  actor.yVel = CHI.DIVE_SPEED;    // +0x48 = 20.0
  // +0x50 = descriptor handlerData6c (gravityCoeff for the dive).
  actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  actor.contactSlow709 = (actor.contactSlow709 ?? 0) | 1; // +0x709 |= 1
  actor.handlerTimer = CHI.DIVE_TIMER_SEED; // +0x558 = 60.0
}

// ----------------------------------------------------------------------------
// Phase 3 — land. FUN_801f1188 @ chunk_0060.c:3620 (62 instrs).
// ----------------------------------------------------------------------------
function chiPhase3Land(actor: ChiActor): void {
  // zz_0067458_(FLOAT_8043c534=1.0, actor, lockYaw) — physics integration.
  integratePhysics(CHI.PHYSICS_GRAVITY, actor, actor.lockYaw);
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  // zz_00677b0_(actor) — ground probe.
  const grounded = actor.physicsRuntime?.isSupported?.(actor.pos.x, actor.pos.z) ?? false;
  if (!grounded) {
    if (CHI.THRESHOLD < actor.handlerTimer) {
      // Still diving: decrement dive pitch +0x18da.
      actor.steerYaw18da = ((actor.steerYaw18da ?? 0) + CHI.DIVE_PITCH_STEP) & 0xffff;
      return;
    }
    // Timer expired mid-air: clear +0x709, exit via zz_006a5a4_.
    actor.contactSlow709 = 0;
    chiExitClear(actor);
    // TODO(rom): zz_006a5a4_ cue dispatch unsurfaced.
    return;
  }
  // Grounded (landed): spawn afterimage (zz_00b2190_(actor, 2)), reset scalars, exit.
  stepAfterimage(actor); // zz_00b2190_(actor, 2) — emits trail child when criteria met
  actor.steerYaw18da = 0; // +0x18da = 0
  actor.gravityCoeff = CHI.THRESHOLD; // +0x50 = 0.0
  actor.yVel = CHI.THRESHOLD;         // +0x48 = 0.0
  actor.hDecel = CHI.THRESHOLD;       // +0x4c = 0.0
  actor.hSpeed = CHI.THRESHOLD;       // +0x44 = 0.0
  actor.poseAccum80 = 0;              // +0x80 = 0
  actor.poseAccum7e = 0;              // +0x7e = 0
  actor.poseAccum7c = 0;              // +0x7c = 0
  chiExitClear(actor);
  // TODO(rom): zz_006a474_ cue dispatch unsurfaced.
}

// ----------------------------------------------------------------------------
// Root action dispatcher. Only actionIndex 0 routes to the phase machine.
// ----------------------------------------------------------------------------
export function createDeathBorgChiRootAction(
  _ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    if (base.actionIndex !== 0) return;
    const actor = scratchOf(base);
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: chiPhase0Setup(actor); return;
      case 1: chiPhase1Aim(actor); return;
      case 2: chiPhase2Dive(actor, _ctx); return;
      case 3: chiPhase3Land(actor); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned DEATH BORG CHI (pl0f04). Stamps the borg number and
 *  wires the bespoke action-0 dive machine. */
export function configureDeathBorgChiFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = DEATH_BORG_CHI_NUMBER;
  actor.rootAction = createDeathBorgChiRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const DEATH_BORG_CHI_CONSTANTS = CHI;
export const DEATH_BORG_CHI_EFFECT_SPAWNER = EFFECT_SPAWNER;

// ============================================================================
// Self-tests. Mirror the rom.selfcheck.ts MU/ROACH style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runDeathBorgChiSelfTests(assert: AssertFn): void {
  // --- pl0f04 ph0: advance + seed +0x558 = 30.0 (FLOAT_8043c520). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    assert(a.borgNumber === 0xf04, "pl0f04 borgNumber stamped 0xf04");
    assert(a.rootAction !== null, "death-borg-chi bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "CHI ph0 advances to ph1");
    assert(a.handlerTimer === 30.0, "CHI ph0 seeds +0x558 = 30.0 (FLOAT_8043c520)");
  }

  // --- pl0f04 ph1: timer gate advances to ph2 when +0x558 <= 0.0 (no target). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0 → phase 1 (+0x558 = 30.0)
    assert(a.fbPhaseSlots[0] === 1, "CHI ph0 advances to ph1");
    root(a); // ph1 tick 1: sets +0x146 = 1, drains +0x558 30→29
    assert(a.chiAimActive146 === 1, "CHI ph1 sets +0x146 = 1 (aim-active flag)");
    assert(a.fbPhaseSlots[0] === 1, "CHI ph1 stays in ph1 after first tick");
    // 28 more ph1 ticks drain +0x558 29 → 1 (still > 0.0 threshold).
    for (let i = 0; i < 28; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 1, "CHI ph1 waits while +0x558 > 0.0");
    root(a); // 30th ph1 tick: +0x558 1 → 0 → advance
    assert(a.fbPhaseSlots[0] === 2, "CHI ph1 advances to ph2 when +0x558 <= 0.0");
  }

  // --- pl0f04 ph2: ammo-denied exit (clears +0x709/+0x73f, strips +0x5e0). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => false };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2; // jump straight to ph2
    a.controlWord = 0x3; a.housekeeping73f = 1; a.contactSlow709 = 1;
    root(a); // ph2 denied
    assert(a.fbPhaseSlots[0] === 2, "CHI ph2 denied does NOT advance +0x540");
    assert(a.contactSlow709 === 0, "CHI ph2 denied clears +0x709");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "CHI ph2 denied clears +0x73f and strips +0x5e0 action bits");
  }

  // --- pl0f04 ph2: success arm (dive scalars + lockYaw flip + +0x5e0|=0x40). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.heading = 0x2000;
    a.fbPhaseSlots[0] = 2; // jump to ph2
    root(a); // ph2 success
    assert(a.fbPhaseSlots[0] === 3, "CHI ph2 success advances to ph3");
    assert(a.hSpeed === 20.0 && a.yVel === 20.0,
      "CHI ph2 seeds hSpeed/yVel = 20.0 (FLOAT_8043c528)");
    assert(a.hDecel === -0.3, "CHI ph2 seeds hDecel = -0.3 (FLOAT_8043c52c)");
    assert(a.handlerTimer === 60.0, "CHI ph2 seeds +0x558 = 60.0 (FLOAT_8043c530)");
    assert(a.lockYaw === ((0x2000 - 0x8000) & 0xffff),
      "CHI ph2 flips lockYaw (+0x5ae = +0x72 − 0x8000)");
    assert((a.controlWord & 0x40) !== 0, "CHI ph2 sets +0x5e0 |= 0x40 (position-frozen)");
    assert(a.chiAimActive146 === 0, "CHI ph2 clears +0x146 = 0");
  }

  // --- pl0f04 ph3 airborne: timer-expiry exit (mid-air, clears +0x709/+0x73f/+0x5e0). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.lockYaw = 0; a.heading = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 3; // jump to ph3
    a.handlerTimer = 2.0;
    a.controlWord = 0x43; a.housekeeping73f = 1; a.contactSlow709 = 1;
    // No physicsRuntime → isSupported undefined → not grounded → airborne branch.
    root(a); // +0x558 2→1, airborne
    assert(a.fbPhaseSlots[0] === 3, "CHI ph3 airborne stays in ph3 while +0x558 > 0.0");
    root(a); // +0x558 1→0
    root(a); // 0.0 <= 0.0 → mid-air exit
    assert(a.contactSlow709 === 0, "CHI ph3 mid-air exit clears +0x709");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "CHI ph3 mid-air exit clears +0x73f and strips +0x5e0 action bits");
  }

  // --- pl0f04 ph3 grounded: land exit (resets velocity scalars + pose accum). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.lockYaw = 0; a.heading = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 3;
    a.hSpeed = 20.0; a.yVel = 20.0; a.hDecel = -0.3;
    a.poseAccum7c = 5; a.poseAccum7e = 6; a.poseAccum80 = 7;
    a.steerYaw18da = 0x3000;
    a.controlWord = 0x43; a.housekeeping73f = 1; a.contactSlow709 = 1;
    // Wire a physicsRuntime that reports grounded.
    a.physicsRuntime = {
      clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }),
      isSupported: () => true,
    };
    root(a); // grounded → land exit
    assert(a.hSpeed === 0.0 && a.yVel === 0.0 && a.hDecel === 0.0 && a.gravityCoeff === 0.0,
      "CHI ph3 land resets velocity scalars to FLOAT_8043c524 (0.0)");
    assert(a.steerYaw18da === 0 && a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      "CHI ph3 land clears +0x18da and pose accumulators (+0x7c/+0x7e/+0x80)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "CHI ph3 land exit clears +0x73f and strips +0x5e0 action bits");
  }

  // --- Non-action-0 indices fall through (no-op). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & DeathBorgChiScratch;
    configureDeathBorgChiFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; // not 0
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "CHI rootAction no-ops for actionIndex != 0");
  }
}
