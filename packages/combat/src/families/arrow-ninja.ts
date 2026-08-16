// ARROW NINJA / SHIJIMA (pl0002/pl000b), constructor 0x800cfe9c.
// @audit-ported pl0002 action=1 variants=0,1,2,3,4
// @audit-ported pl000b action=1 variants=0,1,2,3,4
// @audit-ported pl0002 action=2 variants=0,1,2,3,4
// @audit-ported pl000b action=2 variants=0,1,2,3,4
// Action 1 variant routing at 0x8030de28:
//   v0 -> shared zz_00fed6c_ (config 0x8030de3c)
//   v1/v2 -> FUN_800d0d14, phase table 0x8030de54
//   v3/v4 -> FUN_800d117c, phase table 0x8030de64
// Source: research/decomp/ghidra-export/chunk_0022.c:315-634.
//
// ACTION 2 (the dash-attack) at chunk_0022.c:639-783. Dispatcher FUN_800d15d0 ->
// PTR_FUN_8030de74[+0x581] — all 5 variants route to FUN_800d160c -> the 3-phase
// table PTR_FUN_8030de88[+0x540] = [0x800d1648, 0x800d1748, 0x800d1868]:
//   ph0 (0x800d1648) setup: +0x540++, face 0xc1, zero scalars/turn-rates,
//       reposition x0.95 + ground snap, group-4 stream (slot 0 ground / 1 air).
//   ph1 (0x800d1748) dash: reposition + ground snap; on +0x1cef contact advance,
//       air arm flips +0x5ae 180° and seeds the knockback speed vector, then the
//       weapon-cell-2 cost gate spawns zz_00a2684_ (subIdx 0 for borg 2 / 1 for 0xb).
//   ph2 (0x800d1868) recovery: integrate with +0x5ae; grounded+air+contact<0 exits
//       via upper cue 7, +0x1cee wall-contact exits ground idle / air fall.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { createSharedMeleeLunge, type SharedLungeConfig } from "./shared-melee-lunge.js";
import { allocateWeapon, isStreamTickEnabled, stepTargetYaw, targetPitchBam } from "../rom/helpers.js";

export const ARROW_NINJA_ACTION1 = {
  GRAVITY: 1.0,          // FLOAT_804389f0
  ZERO: 0.0,             // FLOAT_804389f4
  LAUNCH_SPEED: 40.0,    // FLOAT_80438a10
  STREAM_RATE: -1.0,     // FLOAT_80438a20
  AIR_DIVE_SPEED: 30.0,  // FLOAT_80438a28
  AIM_TIMER: 60.0,       // FLOAT_80438a2c
  REPOSITION: 0.95,      // FLOAT_80438a30
  DASH_TIMER: 20.0,      // FLOAT_80438a34
  TRAIL_THRESHOLD: 3.0,  // FLOAT_80438a38
  RANGE: 150.0,          // FLOAT_80438a3c
  DECEL: 0.9,            // FLOAT_80438a40
  EXIT_COOLDOWN: 4.0,    // FLOAT_80438a44
  DIVE_RANGE: 250.0,     // FLOAT_80438a4c
  STREAM_GROUP: 3,
} as const;

/** Config @0x8030de3c: 0, 150.0, 20, 0.95, 0.95, 0.8. */
export const ARROW_NINJA_SHARED_LUNGE_CONFIG: SharedLungeConfig = {
  slotBase: 0,
  range: 150,
  dashFrames: 20,
  decelA: 0.95,
  decelB: 0.95,
  decelC: 0.8,
};

/** Action-2 machine constants — every value read from boot.dol (sdata2
 *  @0x804389f0.., r2-relative with r2=0x8043ea20). */
export const ARROW_NINJA_ACTION2 = {
  /** FLOAT_804389f0 = 1.0 — recovery integrator gravity. */
  GRAVITY: 1.0,
  /** FLOAT_804389f4 = 0.0 — zero (scalars/turn-rates/stream-slot seed). */
  ZERO: 0.0,
  /** FLOAT_80438a20 = -1.0 — stream playback rate (group 4). */
  STREAM_RATE: -1.0,
  /** FLOAT_80438a30 = 0.95 — reposition scale (ph0 blink + ph1 per-tick glide). */
  REPOSITION: 0.95,
  /** FLOAT_80438a44 = 4.0 — ph1 air arm +0x48 seed AND the exit +0x694 re-seed. */
  AIR_RISE: 4.0,
  /** FLOAT_80438a50 = 10.0 — ph1 air arm +0x44 seed (forward speed). */
  AIR_SPEED: 10.0,
  /** FLOAT_80438a38 = 3.0 — afterimage trail threshold on |motion|. */
  TRAIL_THRESHOLD: 3.0,
  /** Stream group — immediate `li r5,4` @0x800d1680 (GROUP 4, unlike action 1). */
  STREAM_GROUP: 4,
  /** +0x5e0 airborne bit (position-frozen/air branch). */
  AIRBORNE_BIT: 0x40,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
} as const;

export interface ArrowNinjaScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  rangeRows868?: readonly [number, number, number];
  /** ROM +0x1d9 nonzero: phase-3 braking input. */
  arrowBrakeEvent?: boolean;
  /** ROM +0x71c: suppresses the ground-chain recovery body. */
  arrowRecoverySuppressed?: boolean;
  /** ROM +0x1d0f signed stream event. */
  arrowStreamEvent?: number;
  /** Host collision result corresponding to zz_00677b0_. */
  grounded?: boolean;
  housekeeping73f?: number;
  /** Optional exact homing pitch written to +0x54e by zz_006e6c4_. */
  divePitchBam?: number;
}

function targetDistance(actor: RomActor & ArrowNinjaScratch): number | null {
  const target = actor.lockTarget;
  if (!target) return null;
  return Math.hypot(target.x - actor.pos.x, target.y - actor.pos.y, target.z - actor.pos.z);
}

function rangeRow(actor: RomActor & ArrowNinjaScratch, offset = 0): number {
  return actor.rangeRows868?.[Math.abs(actor.prevActionIndex) % 3] ??
    (offset === 0 ? ARROW_NINJA_ACTION1.RANGE : ARROW_NINJA_ACTION1.DIVE_RANGE);
}

function groundChain(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & ArrowNinjaScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: { // FUN_800d0d64
        actor.fbPhaseSlots[0] = 1;
        actor.handlerTimer = ARROW_NINJA_ACTION1.AIM_TIMER;
        actor.streamSlot = 3;
        if (!actor.lockTarget || (targetDistance(actor) ?? Infinity) > rangeRow(actor)) {
          actor.activeYaw = actor.lockYaw;
        }
        stepTargetYaw(actor, 0xc0);
        if (actor.lockTarget) {
          vecSubtract(actor.pos, actor.lockTarget, actor.motion);
          vecScale(ARROW_NINJA_ACTION1.REPOSITION, actor.motion, actor.motion);
          vecAdd(actor.pos, actor.motion, actor.pos);
        }
        const slot = actor.streamSlot++;
        startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, slot,
          ARROW_NINJA_ACTION1.STREAM_RATE);
        return;
      }
      case 1: { // FUN_800d0e7c
        if (isStreamTickEnabled(actor)) tickStream(actor, 0xf, ctx);
        vecScale(ARROW_NINJA_ACTION1.REPOSITION, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
        actor.handlerTimer -= actor.dt;
        const facingReady = stepTargetYaw(actor, 0xc0);
        if (actor.handlerTimer <= 0 || facingReady) {
          actor.fbPhaseSlots[0] = 2;
          actor.handlerTimer = ARROW_NINJA_ACTION1.DASH_TIMER;
          let distance = rangeRow(actor);
          const live = targetDistance(actor);
          if (live !== null && live < distance) distance = live;
          actor.hSpeed = distance / ARROW_NINJA_ACTION1.DASH_TIMER;
          actor.hDecel = 0;
          ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
        }
        return;
      }
      case 2: { // FUN_800d0fb0
        stepTargetYaw(actor, 0xc0);
        if (actor.contactP0 === 0 || isStreamTickEnabled(actor)) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        const distance = targetDistance(actor);
        if (actor.handlerTimer <= 0 || (distance !== null && distance <= ARROW_NINJA_ACTION1.RANGE)) {
          actor.fbPhaseSlots[0] = 3;
          actor.hSpeed = ARROW_NINJA_ACTION1.LAUNCH_SPEED;
          actor.hDecel = 0;
          actor.yVel = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED;
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
          const slot = actor.streamSlot++;
          startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, slot,
            ARROW_NINJA_ACTION1.STREAM_RATE);
        }
        return;
      }
      case 3: // FUN_800d10b4
        if (actor.arrowBrakeEvent) {
          actor.hSpeed *= ARROW_NINJA_ACTION1.DECEL;
          actor.yVel *= ARROW_NINJA_ACTION1.DECEL;
        }
        if (actor.arrowRecoverySuppressed) return;
        tickStream(actor, 0xf, ctx);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.wallContact !== 0) {
          actor.lockYaw = actor.activeYaw;
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          romAirKnockoutReturn(actor);
          actor.stateTimer = ARROW_NINJA_ACTION1.EXIT_COOLDOWN + actor.dt;
        }
        return;
      default: return;
    }
  };
}

function diveVelocity(actor: RomActor & ArrowNinjaScratch): void {
  const pitch = actor.divePitchBam ?? targetPitchBam(actor) ?? 0;
  actor.divePitchBam = pitch;
  const angle = (pitch & 0xffff) * Math.PI * 2 / 0x10000;
  actor.hSpeed = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED * Math.cos(angle);
  actor.yVel = -ARROW_NINJA_ACTION1.AIR_DIVE_SPEED * Math.sin(angle);
}

function airDive(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & ArrowNinjaScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: // FUN_800d11cc
        actor.fbPhaseSlots[0] = 1;
        actor.hSpeed = actor.yVel = actor.hDecel = actor.gravityCoeff = 0;
        actor.handlerTimer = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED;
        actor.streamSlot = 3;
        ctx.onFamilyProjectile?.(actor, 0x80092dcc, 0);
        startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, 2,
          ARROW_NINJA_ACTION1.STREAM_RATE);
        return;
      case 1: { // FUN_800d12b4
        diveVelocity(actor);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        const distance = targetDistance(actor);
        if (actor.handlerTimer <= 0 || (distance !== null && distance <= ARROW_NINJA_ACTION1.DIVE_RANGE)) {
          actor.fbPhaseSlots[0] += 2; // ROM intentionally skips phase 2.
        }
        return;
      }
      case 2: // FUN_800d1404 (reachable through external phase rewrites)
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        if (actor.handlerTimer <= 0) {
          actor.fbPhaseSlots[0] = 3;
          diveVelocity(actor);
        }
        return;
      case 3: // FUN_800d14bc
        tickStream(actor, 0xf, ctx);
        if ((actor.arrowStreamEvent ?? 0) < 0) {
          actor.arrowStreamEvent = 0;
          actor.yVel = Math.min(actor.yVel, 0);
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
        }
        actor.hSpeed *= Math.pow(ARROW_NINJA_ACTION1.REPOSITION, actor.dt);
        actor.yVel *= Math.pow(ARROW_NINJA_ACTION1.REPOSITION, actor.dt);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if ((actor.grounded === true && actor.contactP0 < 0) || actor.wallContact !== 0) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          if (actor.grounded === true && actor.contactP0 < 0) dispatchUpperBodyCue(actor, 7);
          else romAirKnockoutReturn(actor);
          actor.stateTimer = ARROW_NINJA_ACTION1.GRAVITY + actor.dt;
        }
        return;
      default: return;
    }
  };
}

export type ArrowNinjaBorgId = "pl0002" | "pl000b";

/** zz_00a2684_ @0x800a2684 — the family projectile spawner. Builds a kind-0x11
 *  child (+0x10 = 0x11, +0x11 = subIdx). Borg-gated: only +0x3e8 == 2 / 0xb spawn.
 *  The phase-1 call site passes subIdx 0 for borg 2 (pl0002) and 1 for borg 0xb
 *  (pl000b). */
export const ARROW_NINJA_SPAWNER = 0x800a2684;

// ============================================================================
// ACTION 2 — dash attack (FUN_800d15d0 -> 3-phase table PTR_FUN_8030de88).
// ============================================================================

function arrowNinjaAction2(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & ArrowNinjaScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: { // FUN_800d1648
        actor.fbPhaseSlots[0] = 1; // +0x540++
        // `if (+0xcc == 0) +0x5ac = +0x72;` — no lock → activeYaw = heading.
        if (!actor.lockTarget) actor.activeYaw = actor.heading;
        stepTargetYaw(actor, 0xc1); // zz_006d144_(actor, 0xc1) — face helper
        // Zero scalars +0x50/+0x48/+0x4c/+0x44 and turn rates +0x80/+0x7e/+0x7c.
        actor.gravityCoeff = 0;
        actor.yVel = 0;
        actor.hDecel = 0;
        actor.hSpeed = 0;
        // REPOSITION: motion = pos - lockTarget; motion x= 0.95; pos += motion.
        if (actor.lockTarget) {
          vecSubtract(actor.pos, actor.lockTarget, actor.motion);
          vecScale(ARROW_NINJA_ACTION2.REPOSITION, actor.motion, actor.motion);
          vecAdd(actor.pos, actor.motion, actor.pos);
        }
        // zz_00679d0_ ground snap (registered ground clamp stands in).
        // +0x6ea = 0; airborne (+0x5e0 & 0x40) → 1; then +0x6ea++ AFTER the stream
        // slot is read (slot = pre-increment value). Group 4.
        actor.streamSlot = (actor.controlWord & ARROW_NINJA_ACTION2.AIRBORNE_BIT) !== 0 ? 1 : 0;
        const slot = actor.streamSlot;
        actor.streamSlot = slot + 1;
        startStream(actor, 0xf, ARROW_NINJA_ACTION2.STREAM_GROUP, slot, ARROW_NINJA_ACTION2.STREAM_RATE);
        return;
      }
      case 1: { // FUN_800d1748
        tickStream(actor, 0xf, ctx);
        stepTargetYaw(actor, 0xc1); // zz_006d144_(actor, 0xc1)
        vecScale(ARROW_NINJA_ACTION2.REPOSITION, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
        if (actor.contactP0 !== undefined && actor.contactP0 > 0) {
          actor.fbPhaseSlots[0] = 2; // +0x540++
          if ((actor.controlWord & ARROW_NINJA_ACTION2.AIRBORNE_BIT) !== 0) {
            // +0x5ae = +0x72 + (-0x8000): knockback flies BACKWARD.
            actor.activeYaw = (actor.heading - 0x8000) & 0xffff;
            actor.hSpeed = ARROW_NINJA_ACTION2.AIR_SPEED;    // +0x44 = 10.0
            actor.hDecel = ARROW_NINJA_ACTION2.ZERO;         // +0x4c = 0
            actor.yVel = ARROW_NINJA_ACTION2.AIR_RISE;       // +0x48 = 4.0
            actor.gravityCoeff = ARROW_NINJA_ACTION2.STREAM_RATE; // +0x50 = -1.0
          }
          // Weapon cell 2 cost gate (consume) → spawn zz_00a2684_(0 / 1 by borg).
          if (allocateWeapon(actor, ctx, 2, 1, true)) {
            const subIdx = actor.borgNumber === 2 ? 0 : 1; // 2 → 0, 0xb → 1
            ctx.onFamilyProjectile?.(actor, ARROW_NINJA_SPAWNER, subIdx);
          }
        }
        // Afterimage trail on |motion| > 3.0 (zz_00b22f4_ — renderer-side, unported).
        return;
      }
      case 2: { // FUN_800d1868
        tickStream(actor, 0xf, ctx);
        integratePhysics(ARROW_NINJA_ACTION2.GRAVITY, actor, actor.activeYaw);
        // `if (grounded && (+0x5e0 & 0x40) && +0x1cef < 0)` → upper cue 7 exit.
        if (
          actor.grounded === true &&
          (actor.controlWord & ARROW_NINJA_ACTION2.AIRBORNE_BIT) !== 0 &&
          actor.contactP0 !== undefined && actor.contactP0 < 0
        ) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~ARROW_NINJA_ACTION2.ACTION_MODE_BITS;
          dispatchUpperBodyCue(actor, 7); // zz_006a750_(actor, 7)
          actor.stateTimer = ARROW_NINJA_ACTION2.AIR_RISE + actor.dt; // +0x694 = 4.0 + dt
          return;
        }
        // `if (+0x1cee != 0)` → ground idle (grounded) or air-fall.
        if (actor.wallContact !== 0) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~ARROW_NINJA_ACTION2.ACTION_MODE_BITS;
          if ((actor.controlWord & ARROW_NINJA_ACTION2.AIRBORNE_BIT) === 0) {
            romGroundIdleReturn(actor); // zz_006a474_
          } else {
            romAirKnockoutReturn(actor); // zz_006a5a4_
          }
          actor.stateTimer = ARROW_NINJA_ACTION2.AIR_RISE + actor.dt;
        }
        return;
      }
      default: return;
    }
  };
}

export function configureArrowNinjaFamily(
  actor: RomActor,
  borgId: ArrowNinjaBorgId,
  ctx: StreamContext,
): void {
  const shared = createSharedMeleeLunge(ARROW_NINJA_SHARED_LUNGE_CONFIG, ctx);
  const ground = groundChain(ctx);
  const air = airDive(ctx);
  const dash = arrowNinjaAction2(ctx);
  actor.borgNumber = borgId === "pl0002" ? 0x002 : 0x00b;
  actor.rootAction = (a: RomActor): void => {
    if (a.actionIndex === 2) { dash(a); return; }
    if (a.actionIndex !== 1) return;
    if (a.variantIndex === 0) shared(a);
    else if (a.variantIndex <= 2) ground(a);
    else air(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — action 2 phase flow (mirror the tank-module style).
// ============================================================================

type AssertFn = (cond: boolean, msg: string) => void;

export function runArrowNinjaAction2SelfTests(assert: AssertFn): void {
  console.log("\n[arrow-ninja.selfcheck] pl0002 action 2 — dash attack:");

  const shots: Array<{ addr: number; type: number }> = [];
  const ctx: StreamContext = {
    onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    onAllocateResource: () => true,
  };
  const a = createRomActor() as RomActor & ArrowNinjaScratch;
  a.actionIndex = 2;
  a.borgNumber = 0x002;
  a.controlWord = 0x3;
  a.heading = 0x2000;
  a.activeYaw = 0x2000;
  a.pos = { x: 0, y: 0, z: 0 };
  a.motion = { x: 0, y: 0, z: 0 };
  a.lockTarget = { x: 100, y: 0, z: 0 };
  a.grounded = false;
  a.dt = 1;
  // Minimal cue table so dispatchUpperBodyCue(7) resolves to a state.
  a.cueTable = new Int8Array([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]);
  const root = configureArrowNinjaFamily;
  const dash = (): void => root(a as unknown as RomActor, "pl0002", ctx);

  // Configure stamps the root dispatcher; drive action 2 through it.
  dash();
  assert(a.rootAction !== null, "configureArrowNinjaFamily wires rootAction");
  a.rootAction?.(a);

  // ph0: +0x540=1, reposition applied (0.95 toward target), stream started.
  assert(a.fbPhaseSlots[0] === 1, "action-2 ph0 advances to phase 1");
  assert(Math.abs(a.pos.x + 95) < 0.001, "action-2 ph0 repositions 0.95 toward target");

  // ph1 (dash): no contact → stays; motion glides further.
  a.rootAction?.(a);
  assert(a.fbPhaseSlots[0] === 1, "action-2 ph1 holds without contact");
  assert(Math.abs(a.pos.x + 185.25) < 0.001, "action-2 ph1 continues the glide");

  // ph1 contact → advance to ph2 + spawn (grounded: no air knockback arm).
  a.contactP0 = 1;
  a.rootAction?.(a);
  assert(a.fbPhaseSlots[0] === 2, "action-2 ph1 advances to recovery on contact");
  assert(shots.length === 1 && shots[0]!.addr === ARROW_NINJA_SPAWNER && shots[0]!.type === 0,
    "action-2 contact spawns zz_00a2684_ subIdx 0 for borg 0x002");

  // ph2 recovery: grounded+air+contact<0 → upper cue 7; else wall contact exit.
  a.grounded = true;
  a.contactP0 = -1;
  a.controlWord = 0x43; // airborne bit set
  a.rootAction?.(a);
  assert(a.ubCue === 7, "action-2 recovery exits via upper cue 7");
  assert((a.controlWord & 0x3) === 0, "action-2 recovery strips action-mode bits");

  console.log("\n[arrow-ninja.selfcheck] pl000b action 2 — borg-switched spawn:");
  const shots2: Array<{ addr: number; type: number }> = [];
  const ctx2: StreamContext = {
    onFamilyProjectile: (_a, addr, type) => shots2.push({ addr, type }),
    onAllocateResource: () => true,
  };
  const b = createRomActor() as RomActor & ArrowNinjaScratch;
  b.actionIndex = 2;
  b.borgNumber = 0x00b;
  b.controlWord = 0x3;
  b.pos = { x: 0, y: 0, z: 0 };
  b.motion = { x: 0, y: 0, z: 0 };
  b.grounded = false;
  b.dt = 1;
  const rootB = configureArrowNinjaFamily;
  rootB(b as unknown as RomActor, "pl000b", ctx2);
  b.rootAction?.(b);
  b.contactP0 = 1;
  b.rootAction?.(b);
  assert(shots2.length === 1 && shots2[0]!.addr === ARROW_NINJA_SPAWNER && shots2[0]!.type === 1,
    "action-2 contact spawns subIdx 1 for borg 0x00b");
}
