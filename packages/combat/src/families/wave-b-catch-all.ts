// Wave-B catch-all family module
// Provides lightweight family registrations for borgs that share common ROM engines
// but lack dedicated family files. Covers: Gun Borg (pl0100/0108), Ninja (pl0005/0009),
// Dragon (pl0504/0510/0502/050e), Knight (pl0202/020b), Wing (pl0a02/0a07/0a04/0a08/0a09),
// Death Borg (pl0105/010a/0a05/0a0a), and Air/Death (pl0d06/0d07/0505/0511).
// @audit-ported pl0d07 action=0 variants=0

import { createRomActor, type RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";
import { integratePhysics } from "../rom/physics.js";
import { stepTargetYaw } from "../rom/helpers.js";

// ------------------------------------------------------------------
// Per-borg X config (groundSlot, airSlot, hasX) derived from actionStreamTables.json
// ------------------------------------------------------------------

interface BorgConfig {
  hasX: boolean;
  groundSlot: number | null;
  airSlot: number | null;
}

const BORG_CONFIGS = {
  // Gun Borg — shared engine fallback (no decoded group-4 stream)
  pl0100: { hasX: false, groundSlot: null, airSlot: null },
  pl0108: { hasX: false, groundSlot: null, airSlot: null },
  // Ninja — some have X streams
  pl0005: { hasX: false, groundSlot: null, airSlot: null },
  pl0009: { hasX: true, groundSlot: 4, airSlot: 4 },
  // Dragon
  pl0504: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0510: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0502: { hasX: false, groundSlot: null, airSlot: null },
  pl050e: { hasX: false, groundSlot: null, airSlot: null },
  pl0505: { hasX: false, groundSlot: null, airSlot: null },
  pl0511: { hasX: false, groundSlot: null, airSlot: null },
  // Knight
  pl0202: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl020b: { hasX: true, groundSlot: 2, airSlot: 2 },
  // Wing
  pl0a02: { hasX: false, groundSlot: null, airSlot: null },
  pl0a07: { hasX: false, groundSlot: null, airSlot: null },
  pl0a04: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0a08: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0a09: { hasX: true, groundSlot: 0, airSlot: 0 },
  // Death Borg misc
  pl0105: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl010a: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0a05: { hasX: false, groundSlot: null, airSlot: null },
  pl0a0a: { hasX: false, groundSlot: null, airSlot: null },
  // Air/Death misc
  pl0d06: { hasX: false, groundSlot: null, airSlot: null },
  pl0d07: { hasX: false, groundSlot: null, airSlot: null },
} as const satisfies Record<string, BorgConfig>;

const BORG_NUMBERS: Record<string, number> = {
  pl0100: 0x100, pl0108: 0x108,
  pl0005: 0x005, pl0009: 0x009, pl0504: 0x504, pl0510: 0x510,
  pl0502: 0x502, pl050e: 0x50e, pl0202: 0x202, pl020b: 0x20b,
  pl0a02: 0xa02, pl0a07: 0xa07, pl0a04: 0xa04, pl0a08: 0xa08,
  pl0a09: 0xa09, pl0105: 0x105, pl010a: 0x10a, pl0a05: 0xa05,
  pl0a0a: 0xa0a, pl0d06: 0xd06, pl0d07: 0xd07, pl0505: 0x505,
  pl0511: 0x511,
};

export type WaveBBorgId = keyof typeof BORG_CONFIGS;

function onHitFallBack(actor: RomActor, ctx: StreamContext): void {
  // Generic fallback on-hit: small backflip
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = 8.0;
  actor.hDecel = 0.0;
  actor.yVel = 10.0;
  actor.gravityCoeff = -0.6;
  void ctx;
}

export function createWaveBRootAction(borgId: WaveBBorgId, ctx: StreamContext): (actor: RomActor) => void {
  const cfg: BorgConfig = BORG_CONFIGS[borgId];
  if (!cfg.hasX || cfg.groundSlot === null) {
    // No X stream — generic combat layer owns all actions EXCEPT the code-driven
    // pl0d07 DEATH BOMB action 0 (FUN_801ae7f4, chunk_0052.c:571).
    if (borgId === "pl0d07") {
      return (actor: RomActor) => {
        if (actor.actionIndex === 0) deathBombAction0(actor, ctx);
      };
    }
    return () => {};
  }
  const xConfig: SharedXConfig = {
    groundSlot: cfg.groundSlot,
    airSlot: cfg.airSlot ?? cfg.groundSlot,
    onHit: onHitFallBack,
  };
  const xHandler = createSharedXSpecial(xConfig, ctx);
  return (actor: RomActor) => {
    if (actor.actionIndex === 2) xHandler(actor);
  };
}

// ============================================================================
// DEATH BOMB (pl0d07, ctor 0x801ae30c) — code-driven action 0 (FUN_801ae7f4,
// chunk_0052.c:571). No phase table: seeds SFX on first entry, applies the drag
// decay (+0x44 ×= 0.1·(1−dt) + 0.9), reloads gravityCoeff from desc.6c, then the
// direction probe zz_0066ac0_(0) gates a physics integrator on +0x5ac, followed by
// the standard integrator on +0x5ae. The probe returns nonzero while a direction is
// held — modeled as the existing stepTargetYaw gate (labeled approximation, same
// class as the tank turret probes).
// ============================================================================

/** Constants read from boot.dol (sdata2 @0x8043b8b0.., r2=0x8043ea20). */
const DEATH_BOMB_A0 = {
  /** FLOAT_8043b8b0 = 0.9 — drag decay base. */
  DRAG_BASE: 0.9,
  /** FLOAT_8043b8c8 = 0.1 — drag decay dt-slope. */
  DRAG_DT_SLOPE: 0.1,
  /** FLOAT_8043b8cc = 1.0 — unity (1 − dt). */
  UNITY: 1.0,
  /** FLOAT_8043b8d0 = 10.0 — gate integrator gravity arg. */
  GATE_GRAVITY: 10.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
} as const;

function deathBombAction0(actor: RomActor, ctx: StreamContext): void {
  if (actor.fbPhaseSlots[0] === 0) {
    actor.fbPhaseSlots[0] = 1;
    ctx.onPlayCue?.(actor, 0xe8); // zz_00f036c_(actor, 0xe8)
    ctx.onPlayCue?.(actor, 0xe9); // zz_00f036c_(actor, 0xe9)
  }
  // +0x44 ×= (0.1·(1−dt) + 0.9) — per-frame speed decay.
  actor.hSpeed *= DEATH_BOMB_A0.DRAG_DT_SLOPE * (DEATH_BOMB_A0.UNITY - actor.dt) + DEATH_BOMB_A0.DRAG_BASE;
  // +0x50 = *(desc + 0x6c) — reload gravityCoeff from the family descriptor.
  actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  // zz_0066ac0_(actor, 0) direction probe → FUN_800676d8(10, actor, +0x5ac).
  // PORT APPROXIMATION (labeled): the probe returns 1 while a direction is held;
  // modeled as stepTargetYaw (nonzero once the yaw converges toward the held
  // direction). The exact +0x5ac integration is the standard physics integrator.
  const probe = stepTargetYaw(actor, 0xc0);
  if (probe) {
    integratePhysics(DEATH_BOMB_A0.GATE_GRAVITY, actor, actor.activeYaw);
  }
  // FUN_80067524(1.0, actor, +0x5ae) — standard integrator.
  integratePhysics(DEATH_BOMB_A0.UNITY, actor, actor.lockYaw);
}

export function configureWaveBFamily(actor: RomActor, borgId: WaveBBorgId, ctx: StreamContext): void {
  actor.borgNumber = BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createWaveBRootAction(borgId, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — DEATH BOMB action 0 (mirror the tank-module style).
// ============================================================================

type AssertFn = (cond: boolean, msg: string) => void;

export function runDeathBombSelfTests(assert: AssertFn): void {
  console.log("\n[wave-b.selfcheck] pl0d07 DEATH BOMB action 0 — code-driven glide:");

  const cues: number[] = [];
  const ctx: StreamContext = {
    onPlayCue: (_a, cue) => cues.push(cue),
  };
  const a = createRomActor() as RomActor;
  a.actionIndex = 0;
  a.dt = 1;
  a.controlWord = 0x3;
  a.hSpeed = 100;
  configureWaveBFamily(a, "pl0d07", ctx);
  assert(a.rootAction !== null, "configureWaveBFamily wires rootAction for pl0d07");

  a.rootAction?.(a);
  assert(a.fbPhaseSlots[0] === 1, "action-0 init advances +0x540");
  assert(cues.includes(0xe8) && cues.includes(0xe9), "action-0 init plays SFX 0xe8/0xe9");
  // dt=1 → drag ×= (0.1·0 + 0.9) = 0.9.
  assert(Math.abs(a.hSpeed - 90) < 0.001, "action-0 applies the 0.9 drag at dt=1");
}

