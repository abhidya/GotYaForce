// Shared attack engines — port of zz_0177dd8_ (standard melee, chunk_0044.c:3001) and
// zz_0178394_ (lunge/dash-attack, chunk_0044.c:3206). These are the GENERIC
// config-struct-driven engines that the MAJORITY of the roster's variant functions
// tail-call (the `lis r4, ...; addi r4, r4, ...; bl 0x80177dd8` pattern documented
// in cue-script-stream-decode §3).
//
// Once ported, any family whose variant functions use these engines gets real
// ROM-driven attacks by just providing the config struct data — no per-family code.

import type { RomActor } from "../rom/actor.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

const ENG = {
  STREAM_RATE: -1.0,
  TIMER_FLOOR: 0.0,
  MELEE_TIMER: 60.0,
  LUNGE_TIMER: 30.0,
  EXTRA_VEL: 0.5,
  LUNGE_VEL_MULT: 0.0625,
} as const;

/**
 * Port of `zz_01782dc_` — the forward-dash velocity setter. Shared by this file's
 * lunge/melee machines AND the more faithful B-close port in shared-melee-gred.ts.
 * Takes timerFrames directly so callers don't have to synthesize a full config. */
export function computeLungeSpeed(actor: RomActor, timerFrames: number): void {
  if (timerFrames > 0) {
    const row = ((actor.prevActionIndex % 3) + 3) % 3;
    actor.hSpeed = actor.actionSpeedRows[row]! / timerFrames;
  }
}

/** The config struct that each family's variant function loads into r4 before
 *  tail-calling the shared engine. Layout matches the ROM's struct at the address
 *  the `lis+addi` pair computes. */
export interface SharedEngineConfig {
  /** +0x0: seed slot byte — the first stream slot to play (config[0] → +0x6ea).
   *  Combo follow-ups increment this. */
  seedSlot: number;
  /** +0x4: float — proximity/velocity parameter passed to FUN_800668cc (the "is
   *  target in range" check that gates the active-frame advance). */
  proximityRange: number;
  /** +0x8: u32 — timer seed (frames) for the active window. Copied into +0x558
   *  at phase start; decremented per frame; expiry advances the phase. */
  timerFrames: number;
  /** +0xc: float — reposition scale (the lunge engine's "push from target" factor).
   *  Applied as motion = (pos - target) × scale; pos += motion (same pattern as
   *  G RED's G Crash). 0 = no repositioning (standard melee). */
  repositionScale: number;
  /** +0x10: chain callback — called when the combo-continue condition is met
   *  (+0x1cf0 & +0x746 & +0x745). Re-issues a command via zz_006a3d0_. */
  chainCallback?: (actor: RomActor) => void;
  /** +0x14: alt chain callback — called when +0x1dd & 0x80 and not +0x745. */
  altChainCallback?: (actor: RomActor) => void;
  /** zz_0178394 config +0x10: phase-2 launch velocity magnitude. */
  launchVelocity?: number;
  /** zz_0178394 config +0x14: scale applied to all four velocity scalars on P2->P3. */
  transitionScale?: number;
  /** zz_0178394 config +0x18: zz_006ed8c_ damping used in phases 3 and 4. */
  recoveryDamping?: number;
  /** zz_0178394 config s16 +0x0a: phase-3 timer seed. */
  recoveryFrames?: number;
}

/** Per-action config set: one config per actionIndex entry. The rootAction
 *  dispatcher reads +0x580 and dispatches to the matching engine + config. */
export interface SharedEngineActionTable {
  /** actionIndex 0: dash attack (uses the lunge engine). */
  dash?: SharedEngineConfig;
  /** actionIndex 1: B melee (uses the standard melee engine). */
  bMelee?: SharedEngineConfig;
  /** actionIndex 2: X / air-B (uses the lunge engine for rush attacks, or null
   *  to defer to a custom family handler like G RED's). */
  xSpecial?: SharedEngineConfig | null;
  /** actionIndex 3: B charge (uses the charge engine). */
  bCharge?: SharedEngineConfig;
}

// ============================================================================
// Standard melee engine (zz_0177dd8_) — group-3 stream + timer-gated active window.
// ============================================================================

/** Build the 4-phase table for the standard melee engine. */
function createMeleePhases(cfg: SharedEngineConfig): Array<(a: RomActor, ctx: StreamContext) => void> {
  return [
    // Phase 0: setup (FUN_80177e28) — start stream, set timer.
    (actor, ctx) => {
      actor.fbPhaseSlots[0]++;
      actor.streamSlot = cfg.seedSlot;
      // Air-check + yaw snapshot (FUN_80066838 — stubbed: always grounded path).
      actor.activeYaw = actor.heading;
      actor.lockYaw = actor.heading;
      // Start stream group 3 (melee strikes), slot = seedSlot.
      const slot = actor.streamSlot;
      startStream(actor, 0xf, 3, slot, ENG.STREAM_RATE);
      actor.streamSlot = slot + 1; // combo follow-up ++ (+0x6ea)
      actor.handlerTimer = ENG.MELEE_TIMER;
      void ctx;
    },
    // Phase 1: pre-active tick (FUN_80177f10) — tick stream, timer--, on 0 → phase 2.
    //   Calls zz_01782dc_ at the transition to set the forward-dash velocity.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= ENG.TIMER_FLOOR) {
        actor.fbPhaseSlots[0]++;
        actor.handlerTimer = cfg.timerFrames;
        computeLungeSpeed(actor, cfg.timerFrames); // ← zz_01782dc_: set forward-dash hSpeed
      }
    },
    // Phase 2: active frames (FUN_80177fd4) — tick + yaw-only physics + contact check.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      // Yaw-only physics (zz_00670dc_ = no gravity, just hSpeed projection).
      integratePhysics(0, actor, actor.activeYaw); // gravity=0 → yaw-only XZ movement
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= ENG.TIMER_FLOOR) {
        actor.fbPhaseSlots[0]++;
      }
    },
    // Phase 3: combo/recovery (FUN_801780e4) — tick, combo check, restart or end.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      integratePhysics(0, actor, actor.activeYaw);
      // Combo check: if contact flag set and combo window open, restart at phase 2.
      const combo = actor as RomActor & { comboFlag?: number };
      if (actor.contactP0 > 0 && (combo.comboFlag ?? 0) > 0) {
        if (cfg.chainCallback) {
          cfg.chainCallback(actor);
          return;
        }
        // Default: replay the stream at the next slot (combo follow-up).
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = cfg.timerFrames;
        startStream(actor, 0xf, 3, actor.streamSlot, ENG.STREAM_RATE);
        actor.streamSlot++;
      } else {
        // Recovery: return to idle — real zz_006a474_ call (FUN_801780e4 wall/stream
        // end, chunk_0044.c:3172; decomp-verified helper — the old full-0 + upper-6
        // mapping was refuted).
        actor.controlWord = actor.controlWord & ~0x3;
        romGroundIdleReturn(actor);
      }
    },
  ];
}

// ============================================================================
// Lunge / dash-attack engine (zz_0178394_) — zero velocity + reposition + stream.
// ============================================================================

function createLungePhases(cfg: SharedEngineConfig): Array<(a: RomActor, ctx: StreamContext) => void> {
  const scratch = (actor: RomActor) => actor as RomActor & {
    lockTarget?: { x: number; y: number; z: number } | null;
    grounded?: boolean;
    streamTickGate?: boolean;
    aimPitch54e?: number;
  };
  const damp = (actor: RomActor, factor: number) => {
    const amount = (1 - factor) * actor.dt;
    actor.hSpeed -= actor.hSpeed * amount;
    actor.yVel -= actor.yVel * amount;
  };
  return [
    // Phase 0: setup (zz_01783e4_) — zero velocity, reposition from target, start stream.
    (actor, ctx) => {
      actor.fbPhaseSlots[0]++;
      actor.handlerTimer = ENG.LUNGE_TIMER; // FLOAT_8043ae00 = 30
      // Zero the velocity scalars (the lunge starts from standstill).
      actor.hSpeed = 0;
      actor.yVel = 0;
      actor.hDecel = 0;
      actor.gravityCoeff = 0;
      actor.activeYaw = actor.heading;
      actor.lockYaw = actor.heading;
      actor.streamSlot = cfg.seedSlot;
      // Reposition: motion = (pos - target) × scale; pos += motion.
      const target = scratch(actor).lockTarget;
      if (target && cfg.repositionScale !== 0) {
        vecSubtract(actor.pos, target, actor.motion);
        vecScale(cfg.repositionScale, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
      }
      startStream(actor, 0xf, 3, actor.streamSlot, ENG.STREAM_RATE);
      actor.streamSlot++;
      // zz_006e514_/zz_006e1ac_ populate +0x54e. The bridge's +0x18da pitch
      // channel is the exact surfaced source for the flag-2 path.
      scratch(actor).aimPitch54e = actor.steerYaw;
      void ctx;
    },
    // Phase 1: tick + reposition continuation + timer (FUN_80178574).
    //   Calls zz_01782dc_ at the transition to set the forward-dash velocity.
    (actor, ctx) => {
      if (scratch(actor).streamTickGate !== false) tickStream(actor, 0xf, ctx);
      if (cfg.repositionScale !== 0) {
        vecScale(cfg.repositionScale, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
      }
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= ENG.TIMER_FLOOR) {
        actor.fbPhaseSlots[0]++;
        actor.handlerTimer = cfg.timerFrames; // cfg s16 +0x08
      }
    },
    // Phase 2 FUN_80178684: stream/aim tick, launch-vector integration, then seed P3.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      const pitch = scratch(actor).aimPitch54e ?? actor.steerYaw;
      const rad = (pitch / 0x10000) * Math.PI * 2;
      const velocity = cfg.launchVelocity ?? 0;
      actor.hSpeed = velocity * Math.cos(rad);
      actor.yVel = -velocity * Math.sin(rad);
      integratePhysics(1, actor, actor.lockYaw);
      actor.handlerTimer -= actor.dt;
      const target = scratch(actor).lockTarget;
      const inRange = target ? Math.hypot(target.x - actor.pos.x, target.z - actor.pos.z) <= cfg.proximityRange : false;
      if (actor.handlerTimer <= ENG.TIMER_FLOOR || inRange) {
        actor.fbPhaseSlots[0]++;
        actor.handlerTimer = cfg.recoveryFrames ?? 0; // cfg s16 +0x0a
        const scale = cfg.transitionScale ?? 1;
        actor.hSpeed *= scale;
        actor.hDecel *= scale;
        actor.yVel *= scale;
        actor.gravityCoeff *= scale;
      }
    },
    // Phase 3 FUN_80178808: damp/integrate until cfg+0x0a expires.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      damp(actor, cfg.recoveryDamping ?? 1);
      integratePhysics(1, actor, actor.lockYaw);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0) actor.fbPhaseSlots[0]++;
    },
    // Phase 4 FUN_80178908: stream/combo tail and exact grounded/wall exits.
    (actor, ctx) => {
      tickStream(actor, 0xf, ctx);
      if (actor.contactP0 < 0) actor.steerYaw = actor.steerYaw >> 1;
      damp(actor, cfg.recoveryDamping ?? 1);
      integratePhysics(1, actor, actor.lockYaw);
      if (scratch(actor).grounded === true && actor.contactP0 < 0) {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 7);
        actor.stateTimer = 1.0 + actor.dt;
      } else if (actor.wallContact !== 0) {
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor);
      }
    },
  ];
}

// ============================================================================
// Factory: build a rootAction dispatcher from a shared-engine action table.
// ============================================================================

/** Create a rootAction function for a family that uses the shared engines.
 *  ActionIndex → engine(config). Null entries fall through to the existing generic
 *  @gf/combat logic. */
export function createSharedEngineRootAction(
  table: SharedEngineActionTable,
): (actor: RomActor) => void {
  const entries: Array<{ phases: Array<(a: RomActor, ctx: StreamContext) => void>; ctx: StreamContext } | null> = [];
  // Build per-action phase tables. Each entry carries its phase array + the shared ctx
  // (the ctx is threaded when the bridge calls stepRomActor).
  if (table.dash) entries[0] = { phases: createLungePhases(table.dash), ctx: {} };
  if (table.bMelee) entries[1] = { phases: createMeleePhases(table.bMelee), ctx: {} };
  // entries[2] (X) — null means defer to a custom handler (G RED) or generic code.
  if (table.xSpecial === null) entries[2] = null;
  else if (table.xSpecial) entries[2] = { phases: createLungePhases(table.xSpecial), ctx: {} };
  if (table.bCharge) entries[3] = { phases: createMeleePhases(table.bCharge), ctx: {} };

  return (actor: RomActor) => {
    const entry = entries[actor.actionIndex];
    if (!entry) return; // null → fall through to generic code
    const phase = actor.fbPhaseSlots[0] ?? 0;
    const fn = entry.phases[phase];
    if (fn) fn(actor, entry.ctx);
  };
}

/** Whether the shared-engine root action wires a B-charge handler at actionIndex 3.
 *  Family configure closures call this to stamp RomActor.hasBCharge. */
export function sharedEngineHasBCharge(table: SharedEngineActionTable): boolean {
  return !!table.bCharge;
}

/** Default config templates for common attack shapes. These are STARTING points —
 *  each family overrides with its actual config struct data from boot.dol. */
export const DEFAULT_CONFIGS = {
  /** Standard ground melee: group 3, no reposition, 60f window. */
  groundMelee: (seedSlot: number): SharedEngineConfig => ({
    seedSlot,
    proximityRange: 100,
    timerFrames: 30,
    repositionScale: 0,
  }),
  /** Dash attack / X-rush: reposition toward target, shorter window.
   *  NOTE: repositionScale=0 until zz_01782dc_ (the forward-dash velocity setter) is
   *  ported — without it the borg gets pushed back but never dashes forward. */
  dashAttack: (seedSlot: number, _scale = 0): SharedEngineConfig => ({
    seedSlot,
    proximityRange: 200,
    timerFrames: 20,
    repositionScale: 0,
  }),
  /** Charge release: longer windup, burst damage. */
  chargeRelease: (seedSlot: number): SharedEngineConfig => ({
    seedSlot,
    proximityRange: 150,
    timerFrames: 40,
    repositionScale: 0.3,
  }),
} as const;
