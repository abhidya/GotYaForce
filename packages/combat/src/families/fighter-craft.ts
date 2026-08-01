// BLUE STRIKER (pl0d00, ctor 0x800f7580) + ORANGE FIGHTER (pl0d04, ctor 0x800f7660)
// fighter-craft family — bespoke 4-action dispatch port.
//
// Both fighters share one root action router (FUN_800f789c → table @0x8031d120)
// that indexes the actor actionIndex (+0x580) into four action sub-routers. Each
// sub-router dispatches its own phase table (indexed by +0x540) and applies a
// shared bob/wobble decay on +0x1922/+0x1924.
//
//   action 0 (FUN_800f78d8, shared)  table @0x8031d130 — 4-phase burst volley
//   action 1 (FUN_800f7bf4, d00)     table @0x8031d140 — 3-phase hardpoint spawn (BLUE)
//   action 2 (FUN_800f7dc0, d04)     table @0x8031d14c — 3-phase dual-port spawn (ORANGE)
//   action 3 (FUN_800f7f98, shared)  table @0x8031d158 — 4-phase aimed burst
//
// Source: research/decomp/ghidra-export/chunk_0027.c:1013-1444.
// Exit helper zz_006a53c_ @ chunk_0009.c:750 (clear +0x73f, strip +0x5e0 action
// bits, dispatch full-body cue 0x1b; seed +0x694 = param+dt when param > 0).
//
// Float constants (read from boot.dol):
//   FLOAT_804391a4 = 30.0  main-timer seed (actions 0/3 setup, exit re-seed)
//   FLOAT_804391a0 = 0.0   phase-1/3 threshold
//   FLOAT_8043919c = 0.2   FUN_8006cc90 stream rate
//   FLOAT_80439184 = 0.9 / 80439188 = 0.1 / 8043918c = 1.0  bob decay factor

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

const FIGHTER_BORG_NUMBERS: Record<string, number> = {
  pl0d00: 0xd00, // BLUE STRIKER
  pl0d04: 0xd04, // ORANGE FIGHTER
};

export type FighterBorgId = keyof typeof FIGHTER_BORG_NUMBERS;

const FIGHTER = {
  /** FLOAT_804391a4 = 30.0 — main-timer seed (action setup + spawn-exit). */
  MAIN_TIMER_SEED: 30.0,
  /** FLOAT_804391a0 = 0.0 — phase-1 wait threshold / cooldown exit threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043919c = 0.2 — FUN_8006cc90 stream rate (cosmetic). */
  STREAM_RATE: 0.2,
  /** FLOAT_80439184 = 0.9 — bob factor base. */
  BOB_BASE: 0.9,
  /** FLOAT_80439188 = 0.1 — bob factor dt-scale. */
  BOB_DT_SCALE: 0.1,
  /** FLOAT_8043918c = 1.0 — bob factor dt-base. */
  BOB_DT_BASE: 1.0,
  /** +0x14c inter-shot frame delay (action 0 burst volley). */
  A0_SHOT_INTERVAL: 10,
  /** Action 0 burst-mode shot cap (advance when 9 < shotCount, i.e. 10 shots). */
  A0_BURST_SHOT_CAP: 9,
  /** +0x5bc status bit gating burst mode (latched into +0x14a). */
  BURST_STATUS_BIT: 0x200,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
  /** zz_006a53c_ cancel param (non-matching borg branch). */
  CANCEL_PARAM: 10,
} as const;

// ----------------------------------------------------------------------------
// Spawner addresses (zz_*  family-local projectile/effect spawners).
// ----------------------------------------------------------------------------
const SHOT_HELPER = 0x80082824;        // zz_0082824_ — record-table projectile spawn
const EFFECT_SPAWNER = 0x800c3be0;     // zz_00c3be0_ — effect spawn (action 3)
const BLUE_HARDPOINT_SPAWNER = 0x800f9400; // zz_00f9400_ — BLUE action-1 hardpoint spawn
const ORANGE_DUAL_SPAWNER = 0x800fcd38;    // zz_00fcd38_ — ORANGE action-2 dual-port spawn

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface FighterScratch {
  /** +0x149: action-0 alternating-shot toggle (& 1). */
  fighterShotToggle?: number;
  /** +0x14a: burst-mode latch (set when +0x5bc & 0x200). */
  fighterBurstFlag?: number;
  /** +0x14c: action-0 inter-shot frame countdown. */
  fighterShotCooldown?: number;
  /** +0x14e: action-0 shots fired this action. */
  fighterShotCount?: number;
  /** +0x148: BLUE action-1 hardpoint cursor (& 3). */
  fighterHardpointBlue?: number;
  /** +0x151: ORANGE action-2 dual-port cursor (& 1). */
  fighterHardpointOrange?: number;
  /** +0x1922: bob wobble yaw (decays toward 0 each frame). */
  bobYaw1922?: number;
  /** +0x1924: bob wobble pitch. */
  bobPitch1924?: number;
  /** +0x5bc: live status word; bit 0x200 gates burst mode. */
  statusWord5bc?: number;
}

type FighterActor = RomActor & FighterScratch;

function scratchOf(actor: RomActor): FighterActor {
  return actor as FighterActor;
}

// ----------------------------------------------------------------------------
// zz_006a53c_(actor, param) — chunk_0009.c:750. Common action-exit: clear
// housekeeping, strip the action-mode bits, dispatch full-body cue 0x1b, and
// (when param > 0) seed +0x694 = param + dt.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, FIGHTER.EXIT_CUE);
}

// ----------------------------------------------------------------------------
// FUN_8006cc90 host bridge. The fighter family has no extracted stream banks
// (code-driven), so the tick is an honest no-op returning 0 — the exact ROM
// behavior when no bank is attached (the +0x1d80 bank pointer is null).
// ----------------------------------------------------------------------------
function tickFighterStream(): number {
  return 0;
}

/** The shared bob/wobble decay applied by every action sub-router after the
 *  phase dispatch: +0x1922/+0x1924 *= (0.1 × (1.0 − dt) + 0.9), truncated to short. */
function applyBob(actor: FighterActor): void {
  const factor = FIGHTER.BOB_DT_SCALE * (FIGHTER.BOB_DT_BASE - actor.dt) + FIGHTER.BOB_BASE;
  actor.bobYaw1922 = Math.trunc((actor.bobYaw1922 ?? 0) * factor);
  actor.bobPitch1924 = Math.trunc((actor.bobPitch1924 ?? 0) * factor);
}

// ----------------------------------------------------------------------------
// Action 0 — shared burst volley (table @0x8031d130, 4 phases).
//   ph0 (0x800f79c8): setup — seed +0x558=30.0, zero +0x149/+0x14a/+0x14c/+0x14e.
//   ph1 (0x800f79f4): wait — latch burst, tick stream, drain +0x558; advance on event/threshold.
//   ph2 (0x800f7a80): spawn loop — alternating shot type (d00 0xe/0xf, d04 0x42/0x43),
//                      1 shot (or 10 under burst), advance to cooldown.
//   ph3 (0x800f7bac): cooldown — drain +0x558; exit when <= 0.0.
// ----------------------------------------------------------------------------
function action0(actor: FighterActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;       // +0x558 = 30.0
      actor.fighterShotToggle = 0;                         // +0x149
      actor.fighterBurstFlag = 0;                          // +0x14a
      actor.fighterShotCooldown = 0;                       // +0x14c
      actor.fighterShotCount = 0;                          // +0x14e
      return;
    }
    case 1: {
      if ((actor.statusWord5bc ?? 0) & FIGHTER.BURST_STATUS_BIT) actor.fighterBurstFlag = 1;
      actor.handlerTimer -= actor.dt;                       // +0x558 -= dt
      const event = tickFighterStream();
      if (event === 0 && FIGHTER.THRESHOLD < actor.handlerTimer) return;
      actor.fbPhaseSlots[0] = 2;
      return;
    }
    case 2: {
      if ((actor.statusWord5bc ?? 0) & FIGHTER.BURST_STATUS_BIT) actor.fighterBurstFlag = 1;
      if ((actor.fighterShotCooldown ?? 0) === 0) {
        actor.fighterShotCooldown = FIGHTER.A0_SHOT_INTERVAL; // +0x14c = 10
        actor.fighterShotCount = (actor.fighterShotCount ?? 0) + 1;
        if (allocateWeapon(actor, ctx, 0, 1, true)) {
          const toggle = (actor.fighterShotToggle ?? 0) & 1;
          // d00: zz_0082824_(toggle + 0xe); d04: zz_0082824_(toggle + 0x42).
          const type = (actor.borgNumber === 0xd00 ? 0xe : 0x42) + toggle;
          ctx.onFamilyProjectile?.(actor, SHOT_HELPER, type);
        }
        actor.fighterShotToggle = ((actor.fighterShotToggle ?? 0) + 1) & 1;
        const shots = actor.fighterShotCount ?? 0;
        if ((actor.fighterBurstFlag ?? 0) === 0) {
          if (0 < shots) { actor.fbPhaseSlots[0] = 3; actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED; }
        } else {
          actor.fighterBurstFlag = 0;
          if (FIGHTER.A0_BURST_SHOT_CAP < shots) {
            actor.fbPhaseSlots[0] = 3; actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;
          }
        }
      } else {
        actor.fighterShotCooldown = (actor.fighterShotCooldown ?? 0) - 1;
      }
      return;
    }
    case 3: {
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= FIGHTER.THRESHOLD) exitAction(actor, 0);
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Action 1 — BLUE (d00) hardpoint spawn (table @0x8031d140, 3 phases).
//   ph0 (0x800f7cb8): setup — +0x558 = 0.0 (immediate advance next tick).
//   ph1 (0x800f7cd0): spawn-once — d00: advance + ammo gate → activate hardpoint
//                     +0x148 (base +0x144), zz_00f9400_(hardpoint), cursor = (cursor+1)&3.
//                     Non-d00: cancel via zz_006a53c_(10).
//   ph2 (0x800f7d78): cooldown — drain +0x558; exit when <= 0.0.
// ----------------------------------------------------------------------------
function action1(actor: FighterActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0:
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = FIGHTER.THRESHOLD;             // +0x558 = 0.0
      return;
    case 1: {
      if (actor.borgNumber === 0xd00) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;     // +0x558 = 30.0
        if (allocateWeapon(actor, ctx, 2, 1, true)) {
          // ROM: *(+0x144 + (+0x148)) = 1; zz_00f9400_(actor, +0x148).
          ctx.onFamilyProjectile?.(actor, BLUE_HARDPOINT_SPAWNER, actor.fighterHardpointBlue ?? 0);
          actor.fighterHardpointBlue = ((actor.fighterHardpointBlue ?? 0) + 1) & 3;
        }
      } else {
        exitAction(actor, FIGHTER.CANCEL_PARAM);
      }
      return;
    }
    case 2: {
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= FIGHTER.THRESHOLD) exitAction(actor, 0);
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Action 2 — ORANGE (d04) dual-port spawn (table @0x8031d14c, 3 phases).
//   ph0 (0x800f7e8c): setup — +0x558 = 0.0.
//   ph1 (0x800f7ea4): spawn-once — d04: advance + ammo gate → activate port
//                     +0x151 (base +0x152), zz_00fcd38_(actor, 2, port), cursor = (cursor+1)&1.
//                     Non-d04: cancel.
//   ph2 (0x800f7f50): cooldown.
// ----------------------------------------------------------------------------
function action2(actor: FighterActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0:
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = FIGHTER.THRESHOLD;
      return;
    case 1: {
      if (actor.borgNumber === 0xd04) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;
        if (allocateWeapon(actor, ctx, 2, 1, true)) {
          ctx.onFamilyProjectile?.(actor, ORANGE_DUAL_SPAWNER, actor.fighterHardpointOrange ?? 0);
          actor.fighterHardpointOrange = ((actor.fighterHardpointOrange ?? 0) + 1) & 1;
        }
      } else {
        exitAction(actor, FIGHTER.CANCEL_PARAM);
      }
      return;
    }
    case 2: {
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= FIGHTER.THRESHOLD) exitAction(actor, 0);
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Action 3 — shared aimed burst (table @0x8031d158, 4 phases).
//   ph0 (0x800f7ff4): setup — +0x558 = 30.0.
//   ph1 (0x800f800c): wait — tick stream (borg-switched desc: d00 @0x8031d168,
//                     d04 @0x8031d170), drain +0x558; advance on event/threshold.
//   ph2 (0x800f809c): fire-once — advance +0x558=30.0; zz_00c3be0_(0x14 d00 / 0x38 d04).
//   ph3 (0x800f80ec): cooldown — drain +0x558; exit when <= 0.0.
// ----------------------------------------------------------------------------
function action3(actor: FighterActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0:
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;
      return;
    case 1: {
      actor.handlerTimer -= actor.dt;
      // Borg-switched stream descriptor (0x8031d168 d00 / 0x8031d170 d04) — no-op
      // without banks; the tick returns 0 so the threshold gates the advance.
      tickFighterStream();
      if (FIGHTER.THRESHOLD < actor.handlerTimer) return;
      actor.fbPhaseSlots[0] = 2;
      return;
    }
    case 2: {
      actor.fbPhaseSlots[0] = 3;
      actor.handlerTimer = FIGHTER.MAIN_TIMER_SEED;
      ctx.onFamilyProjectile?.(actor, EFFECT_SPAWNER, actor.borgNumber === 0xd00 ? 0x14 : 0x38);
      return;
    }
    case 3: {
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= FIGHTER.THRESHOLD) exitAction(actor, 0);
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_800f789c indexes PTR_FUN_8031d120[+0x580]. Each sub-router
// dispatches its phase table then applies the shared bob decay.
// ----------------------------------------------------------------------------
export function createFighterRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: action0(actor, ctx); applyBob(actor); return;
      case 1: action1(actor, ctx); applyBob(actor); return;
      case 2: action2(actor, ctx); applyBob(actor); return;
      case 3: action3(actor, ctx); applyBob(actor); return;
      default: return;
    }
  };
}

export function configureFighterFamily(
  actor: RomActor,
  borgId: FighterBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = FIGHTER_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createFighterRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const FIGHTER_CONSTANTS = FIGHTER;
export const FIGHTER_SHOT_HELPER = SHOT_HELPER;
export const FIGHTER_EFFECT_SPAWNER = EFFECT_SPAWNER;
export const FIGHTER_BLUE_HARDPOINT_SPAWNER = BLUE_HARDPOINT_SPAWNER;
export const FIGHTER_ORANGE_DUAL_SPAWNER = ORANGE_DUAL_SPAWNER;
