// Death Borg Nu / Death Eye family cluster (pl0f00-pl0f06).
//
// DEATH BORG NU (ctor 0x801b3598) and DEATH EYE (ctor 0x801e43f8) share one bespoke
// action-0 ammo-gated spawn machine — a 4-phase table indexed by +0x540:
//
//   DB NU   table @0x80380ee8 = [0x801b3768, 0x801b3798, 0x801b3824, 0x801b3990]
//   DEATH EYE table @0x80391cd8 = [0x801e460c, 0x801e463c, 0x801e46c8, 0x801e47f8]
//
// Source: research/decomp/ghidra-export/chunk_0052.c:4429-4553 (DB NU),
//         chunk_0059.c:893-984 (DEATH EYE). The four phases:
//   0 setup   — seed main timer (+0x558=20.0), cooldown timer (+0x55c=0.0), zero the
//               three scratch counters, advance +0x540.
//   1 wait    — latch the +0x5bc&0x200 burst flag, tick the action stream
//               (FUN_8006cc90), decrement +0x558 by dt; advance when a stream event
//               fires OR +0x558 <= 0.0 (FLOAT threshold).
//   2 spawn   — borg-switched ammo-gated spawn (zz_006dbe0_ gate → zz_0082824_ /
//               zz_00c3be0_ / zz_016cc24_ spawner). Single-shot borgs (NU pl0f02/0f03,
//               EYE non-0xf06) advance immediately; looping borgs (NU pl0f01, EYE
//               pl0f06) fire every 12 frames and exit after 1 shot (or 5 under burst).
//   3 cooldown — tick the stream while +0x55c > 0, decrement +0x558 by dt; when
//                +0x558 <= 0.0 clear +0x73f and strip the action-mode bits (+0x5e0&~3).
//
// The two families differ only in (a) scratch-field offsets, (b) the phase-2 spawn
// policy / shot type, (c) the NU single-shot branch re-seeding +0x55c to 20.0, and
// (d) the FUN_8006cc90 stream (group,slot) params. Float constants are identical:
// FLOAT_*50 = 20.0, FLOAT_*54/04 = 0.0, FLOAT_*58/08 = 0.5, FLOAT_*5c/0c = 40.0.
//
// The remaining members — DEATH BORG MU (pl0f00, ctor 0x801b289c), DEATH BORG CHI
// (pl0f04, ctor 0x801f0c68), and ROACH (pl0f05, ctor 0x801e7d78) — have no bespoke
// phase tables in boot.dol and stay on the generic combat layer (null rootAction).

import type { RomActor } from "../rom/actor.js";
import { allocateWeapon } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Borg numbers for Nu/Eye-family members. */
const NU_BORG_NUMBERS: Record<string, number> = {
  pl0f00: 0xf00, pl0f01: 0xf01, pl0f02: 0xf02,
  pl0f03: 0xf03, pl0f04: 0xf04, pl0f05: 0xf05, pl0f06: 0xf06,
};

export type NuBorgId = keyof typeof NU_BORG_NUMBERS;

// ----------------------------------------------------------------------------
// Shared spawner addresses (already referenced by tank-borg.ts / cyber-machine.ts).
// ----------------------------------------------------------------------------
const SHOT_HELPER = 0x80082824;       // zz_0082824_ — record-table projectile spawn
const EFFECT_SPAWNER_C3BE0 = 0x800c3be0; // zz_00c3be0_ — per-borg effect spawn
const EFFECT_SPAWNER_16CC24 = 0x8016cc24; // zz_016cc24_ — effect-child spawn

// ----------------------------------------------------------------------------
// Config constants (identical floats across both families, cited per-family).
// ----------------------------------------------------------------------------
const NU_FAMILY = {
  /** FLOAT_8043b950 (NU) / FLOAT_8043c200 (EYE) = 20.0 — main timer seed. */
  MAIN_TIMER_SEED: 20.0,
  /** FLOAT_8043b954 (NU) / FLOAT_8043c204 (EYE) = 0.0 — phase-1/3 threshold + cd seed. */
  THRESHOLD: 0.0,
  /** FLOAT_8043b958 (NU) / FLOAT_8043c208 (EYE) = 0.5 — FUN_8006cc90 stream rate. */
  STREAM_RATE: 0.5,
  /** FLOAT_8043b95c (NU) / FLOAT_8043c20c (EYE) = 40.0 — spawn-exit main timer seed. */
  EXIT_TIMER_SEED: 40.0,
  /** FLOAT_8043b950 = 20.0 — NU single-shot branch re-seeds +0x55c. */
  SINGLE_SHOT_CD_RESEED: 20.0,
  /** 0xc — inter-shot frame delay armed on each spawn attempt (phase 2). */
  SHOT_INTERVAL: 12,
  /** Burst-mode shot cap (the +0x14a/>4 branch). */
  BURST_SHOT_CAP: 4,
  /** +0x5bc status bit gating burst mode (latched into the burst flag each tick). */
  BURST_STATUS_BIT: 0x200,
  /** +0x5e0 action-mode bits stripped at cooldown exit. */
  ACTION_MODE_BITS: 0x3,
  /** Cooldown stream-tick (group,slot) — both families use (2,1). */
  COOLDOWN_STREAM: [2, 1] as const,
} as const;

// ----------------------------------------------------------------------------
// Scratch fields. The ROM stores these at different offsets per family; the actor
// only runs one family at a time so named port-side mirrors are sufficient. The ROM
// offsets are cited for audit.
// ----------------------------------------------------------------------------
export interface NuFamilyScratch {
  /** +0x146 (NU) / +0x14c (EYE): burst-mode latch (set when +0x5bc & 0x200). */
  nuBurstFlag?: number;
  /** +0x148 (NU) / +0x14e (EYE): inter-shot frame countdown (SHOT_INTERVAL on fire). */
  nuShotCooldown?: number;
  /** +0x14a (NU) / +0x150 (EYE): shots fired this action. */
  nuShotCount?: number;
  /** +0x55c: cooldown sub-timer (0.0 from setup; NU single-shot re-seeds 20.0). */
  nuCooldownTimer?: number;
  /** +0x5bc: live status word; bit 0x200 gates burst mode. */
  statusWord5bc?: number;
}

type NuActor = RomActor & NuFamilyScratch;

function scratchOf(actor: RomActor): NuActor {
  return actor as NuActor;
}

// ----------------------------------------------------------------------------
// Phase 0 — setup. zz_01b3768_ (NU) / FUN_801e460c (EYE), 12 instrs each.
// ----------------------------------------------------------------------------
function nuPhase0Setup(actor: NuActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.handlerTimer = NU_FAMILY.MAIN_TIMER_SEED;       // +0x558 = 20.0
  actor.nuCooldownTimer = NU_FAMILY.THRESHOLD;          // +0x55c = 0.0
  actor.nuBurstFlag = 0;
  actor.nuShotCooldown = 0;
  actor.nuShotCount = 0;
}

// ----------------------------------------------------------------------------
// Phase 1 — wait. zz_01b3798_ (NU) / FUN_801e463c (EYE), 35 instrs each.
// FUN_8006cc90(rate 0.5, actor, group, slot, &DAT) ticks the action stream and
// returns nonzero when a stream event boundary is hit. The Death family has no
// extracted stream banks (code-driven); the host stream-tick returns 0, so the
// advance is governed by the +0x558 <= 0.0 threshold (the exact ROM fallback path).
// ----------------------------------------------------------------------------
function nuPhase1Wait(
  actor: NuActor,
  ctx: StreamContext,
  streamParams: readonly [number, number],
): void {
  if ((actor.statusWord5bc ?? 0) & NU_FAMILY.BURST_STATUS_BIT) {
    actor.nuBurstFlag = 1;
  }
  actor.handlerTimer -= actor.dt;                        // +0x558 -= +0x1dc8
  const streamEvent = tickDeathStream(actor, ctx, streamParams);
  if (streamEvent === 0 && NU_FAMILY.THRESHOLD < actor.handlerTimer) {
    return;                                              // not ready
  }
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
}

// ----------------------------------------------------------------------------
// Phase 3 — cooldown. zz_01b3990_ (NU) / FUN_801e47f8 (EYE), 37 instrs each.
// ----------------------------------------------------------------------------
function nuPhase3Cooldown(
  actor: NuActor,
  ctx: StreamContext,
): void {
  if (NU_FAMILY.THRESHOLD < (actor.nuCooldownTimer ?? 0)) {
    tickDeathStream(actor, ctx, NU_FAMILY.COOLDOWN_STREAM);
    actor.nuCooldownTimer = (actor.nuCooldownTimer ?? 0) - actor.dt;
  }
  actor.handlerTimer -= actor.dt;                        // +0x558 -= +0x1dc8
  if (actor.handlerTimer <= NU_FAMILY.THRESHOLD) {
    actor.housekeeping73f = 0;                            // +0x73f = 0
    actor.controlWord = actor.controlWord & ~NU_FAMILY.ACTION_MODE_BITS; // +0x5e0 &= ~3
  }
}

// ----------------------------------------------------------------------------
// Per-borg phase-2 spawn policies.
// ----------------------------------------------------------------------------

/** zz_01b3824_ DB NU branch: pl0f01 loops (shot 0x4a), pl0f02/pl0f03 single-shot. */
function nuSpawnNuFamily(actor: NuActor, ctx: StreamContext): void {
  // The leading FUN_8006cc90(0.5, actor, 2, 1, &DAT) stream tick (no-op without banks).
  tickDeathStream(actor, ctx, [2, 1]);
  if (actor.borgNumber === 0xf01) {
    if ((actor.statusWord5bc ?? 0) & NU_FAMILY.BURST_STATUS_BIT) actor.nuBurstFlag = 1;
    if ((actor.nuShotCooldown ?? 0) === 0) {
      actor.nuShotCooldown = NU_FAMILY.SHOT_INTERVAL;
      actor.nuShotCount = (actor.nuShotCount ?? 0) + 1;
      if (allocateWeapon(actor, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(actor, SHOT_HELPER, 0x4a);
      }
      exitLoopOrContinue(actor);
    } else {
      actor.nuShotCooldown = (actor.nuShotCooldown ?? 0) - 1;
    }
    return;
  }
  // Single-shot branch (0xf02 / 0xf03). Ammo gate → borg-switched effect spawner;
  // always advances to cooldown and re-seeds +0x55c to 20.0.
  if (allocateWeapon(actor, ctx, 0, 1, true)) {
    if (actor.borgNumber === 0xf02) {
      ctx.onFamilyProjectile?.(actor, EFFECT_SPAWNER_C3BE0, 0x3d);
    } else { // 0xf03
      ctx.onFamilyProjectile?.(actor, EFFECT_SPAWNER_16CC24, 0xb);
    }
  }
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.handlerTimer = NU_FAMILY.EXIT_TIMER_SEED;        // +0x558 = 40.0
  actor.nuCooldownTimer = NU_FAMILY.SINGLE_SHOT_CD_RESEED; // +0x55c = 20.0
}

/** The shared exit check after each looping shot (NU 0xf01 +0x146/+0x14a logic). */
function exitLoopOrContinue(actor: NuActor): void {
  const shots = actor.nuShotCount ?? 0;
  if ((actor.nuBurstFlag ?? 0) === 0) {
    if (0 < shots) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      actor.handlerTimer = NU_FAMILY.EXIT_TIMER_SEED;    // +0x558 = 40.0
    }
  } else {
    actor.nuBurstFlag = 0;
    if (NU_FAMILY.BURST_SHOT_CAP < shots) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      actor.handlerTimer = NU_FAMILY.EXIT_TIMER_SEED;    // +0x558 = 40.0
    }
  }
}

/** FUN_801e46c8 DEATH EYE branch: pl0f06 loops (shot 0x7a); other borgs single-shot
 *  (0x7b) and advance immediately. EYE never re-seeds +0x55c. */
function nuSpawnDeathEye(actor: NuActor, ctx: StreamContext): void {
  // Leading FUN_8006cc90(0.5, actor, 1, 0, &DAT) stream tick.
  tickDeathStream(actor, ctx, [1, 0]);
  if ((actor.statusWord5bc ?? 0) & NU_FAMILY.BURST_STATUS_BIT) actor.nuBurstFlag = 1;
  if ((actor.nuShotCooldown ?? 0) === 0) {
    actor.nuShotCooldown = NU_FAMILY.SHOT_INTERVAL;
    actor.nuShotCount = (actor.nuShotCount ?? 0) + 1;
    if (allocateWeapon(actor, ctx, 0, 1, true)) {
      if (actor.borgNumber !== 0xf06) {
        ctx.onFamilyProjectile?.(actor, SHOT_HELPER, 0x7b);
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
        actor.handlerTimer = NU_FAMILY.EXIT_TIMER_SEED;  // +0x558 = 40.0
        return;
      }
      ctx.onFamilyProjectile?.(actor, SHOT_HELPER, 0x7a);
    }
    exitLoopOrContinue(actor);
  } else {
    actor.nuShotCooldown = (actor.nuShotCooldown ?? 0) - 1;
  }
}

// ----------------------------------------------------------------------------
// FUN_8006cc90 host bridge. The ROM helper ticks the part-mask action stream at the
// given rate and returns 1 when an op boundary fires. The Death family has no
// extracted stream banks (the configure closures leave familyStreamBank null), so
// the tick is an honest no-op returning 0 — the exact ROM behavior with no bank
// attached (chunk_0006.c: zz_004beb8_ returns -1 → FUN_8006cc90 returns 0).
// ----------------------------------------------------------------------------
function tickDeathStream(
  _actor: NuActor,
  _ctx: StreamContext,
  _streamParams: readonly [number, number],
): number {
  return 0;
}

// ----------------------------------------------------------------------------
// Root action dispatcher. Each family wires its phase-2 spawn policy + the
// phase-1 wait stream params.
// ----------------------------------------------------------------------------
interface NuMachineConfig {
  spawnPhase: (actor: NuActor, ctx: StreamContext) => void;
  waitStreamParams: readonly [number, number];
}

const DB_NU_MACHINE: NuMachineConfig = {
  spawnPhase: nuSpawnNuFamily,
  waitStreamParams: [2, 1],
};

const DEATH_EYE_MACHINE: NuMachineConfig = {
  spawnPhase: nuSpawnDeathEye,
  waitStreamParams: [1, 0],
};

export function createNuFamilyRootAction(
  ctx: StreamContext,
  machine: NuMachineConfig,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: nuPhase0Setup(actor); return;
      case 1: nuPhase1Wait(actor, ctx, machine.waitStreamParams); return;
      case 2: machine.spawnPhase(actor, ctx); return;
      case 3: nuPhase3Cooldown(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned DEATH BORG NU member (pl0f01/pl0f02/pl0f03).
 *  Stamps the borg number and wires the bespoke action-0 spawn machine. */
export function configureDeathBorgNuFamily(
  actor: RomActor,
  borgId: "pl0f01" | "pl0f02" | "pl0f03",
  ctx: StreamContext,
): void {
  actor.borgNumber = NU_BORG_NUMBERS[borgId] ?? 0xf01;
  actor.rootAction = createNuFamilyRootAction(ctx, DB_NU_MACHINE);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure DEATH EYE (pl0f06) on the shared machine with the EYE spawn policy. */
export function configureDeathEyeFamily(
  actor: RomActor,
  ctx: StreamContext,
): void {
  actor.borgNumber = NU_BORG_NUMBERS.pl0f06 ?? 0xf06;
  actor.rootAction = createNuFamilyRootAction(ctx, DEATH_EYE_MACHINE);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure the remaining tableless members (pl0f00/pl0f04/pl0f05/pl0f06 fallback
 *  only used when a borg is not covered by a bespoke registration). Stamps the borg
 *  number; the generic combat layer owns all action logic. */
export function configureNuFamily(actor: RomActor, borgId: NuBorgId, _ctx: StreamContext): void {
  actor.borgNumber = NU_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = null;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEATH BORG MU (pl0f00, ctor 0x801b289c) — bespoke action-0 4-phase machine.
// Table @0x80380a80 = [zz_01b2a2c_, zz_01b2a54_, zz_01b2ac8_, zz_01b2b28_]
// (chunk_0052.c:3834-3900). A simple linear single-shot:
//   ph0 setup: +0x558 = 20.0 (FLOAT_8043b920), zero +0x146/+0x148/+0x14a, advance.
//   ph1 wait:  drain +0x558 by dt; advance when <= 0.0 (FLOAT_8043b928 threshold).
//   ph2 fire:  ammo gate → zz_00c3be0_(0x3c); advance; +0x548 = 40 (0x28).
//   ph3 exit:  +0x548--; exit (zz_006a53c_(0)) when +0x548 < 1.
// ============================================================================
const MU = {
  MAIN_TIMER_SEED: 20.0,   // FLOAT_8043b920
  THRESHOLD: 0.0,          // FLOAT_8043b928
  STREAM_RATE: 0.5,        // FLOAT_8043b924
  EXIT_COUNTDOWN: 40,      // +0x548 = 0x28
} as const;

export interface MuScratch {
  /** +0x548: phase-3 exit countdown (40 → 0). */
  muExitCountdown?: number;
}

export function configureDeathBorgMuFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = NU_BORG_NUMBERS.pl0f00 ?? 0xf00;
  actor.rootAction = (base: RomActor) => {
    const a = base as RomActor & NuFamilyScratch & MuScratch;
    const phase = a.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0:
        a.fbPhaseSlots[0] = 1;
        a.handlerTimer = MU.MAIN_TIMER_SEED;        // +0x558 = 20.0
        a.nuBurstFlag = 0; a.nuShotCooldown = 0; a.nuShotCount = 0; // +0x146/148/14a
        return;
      case 1: {
        a.handlerTimer -= a.dt;                       // +0x558 -= dt
        // FUN_8006cc90(0.5, actor, 2, 1, &DAT) — no-op without stream banks.
        if (MU.THRESHOLD < a.handlerTimer) return;
        a.fbPhaseSlots[0] = 2;
        return;
      }
      case 2: {
        if (allocateWeapon(a, ctx, 0, 1, true)) {
          ctx.onFamilyProjectile?.(a, EFFECT_SPAWNER_C3BE0, 0x3c);
        }
        a.fbPhaseSlots[0] = 3;
        a.muExitCountdown = MU.EXIT_COUNTDOWN;        // +0x548 = 40
        return;
      }
      case 3: {
        a.muExitCountdown = (a.muExitCountdown ?? 0) - 1;
        if ((a.muExitCountdown ?? 0) < 1) {
          a.housekeeping73f = 0;
          a.controlWord = a.controlWord & ~0x3;
        }
        return;
      }
      default: return;
    }
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// ROACH (pl0f05, ctor 0x801e7d78) — bespoke action-0 3-phase machine.
// Table @0x803929a8 = [FUN_801e7f64, FUN_801e7f74, FUN_801e7fe0]
// (chunk_0059.c:3619-3683). Single-shot + cooldown:
//   ph0 advance: +0x540++.
//   ph1 fire:    +0x540++, +0x558 = 10.0 (FLOAT_8043c2d8); ammo gate →
//                FUN_801fad10(actor, 0) + zz_00f036c_(actor, 0xeb) (sound cue).
//   ph2 exit:    drain +0x558 by dt; when < threshold clear +0x73f and +0x5e0&=~3.
// ============================================================================
const ROACH_FX_SPAWNER = 0x801fad10;        // FUN_801fad10 — roach effect spawner
const ROACH = {
  MAIN_TIMER_SEED: 10.0,   // FLOAT_8043c2d8
  THRESHOLD: 0.0,          // FLOAT_8043c2dc
  SOUND_CUE: 0xeb,         // zz_00f036c_(actor, 0xeb)
} as const;

export function configureRoachFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = NU_BORG_NUMBERS.pl0f05 ?? 0xf05;
  actor.rootAction = (base: RomActor) => {
    const a = base as RomActor;
    const phase = a.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0:
        a.fbPhaseSlots[0] = 1;
        return;
      case 1: {
        a.fbPhaseSlots[0] = 2;
        a.handlerTimer = ROACH.MAIN_TIMER_SEED;     // +0x558 = 10.0
        if (allocateWeapon(a, ctx, 0, 1, true)) {
          ctx.onFamilyProjectile?.(a, ROACH_FX_SPAWNER, 0);
          ctx.onPlayCue?.(a, ROACH.SOUND_CUE);
        }
        return;
      }
      case 2: {
        a.handlerTimer -= a.dt;
        if (a.handlerTimer < ROACH.THRESHOLD) {
          a.housekeeping73f = 0;
          a.controlWord = a.controlWord & ~0x3;
        }
        return;
      }
      default: return;
    }
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const NU_FAMILY_CONSTANTS = NU_FAMILY;
export const NU_SHOT_HELPER = SHOT_HELPER;
export const NU_EFFECT_SPAWNER_C3BE0 = EFFECT_SPAWNER_C3BE0;
export const NU_EFFECT_SPAWNER_16CC24 = EFFECT_SPAWNER_16CC24;
export type { NuMachineConfig };
