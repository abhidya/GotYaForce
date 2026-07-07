// Wave-B catch-all family module
// Provides lightweight family registrations for borgs that share common ROM engines
// but lack dedicated family files. Covers: Gun Borg (pl0100/0108), Ninja (pl0002/000b/0005/0009),
// Dragon (pl0504/0510/0502/050e), Knight (pl0202/020b), Wing (pl0a02/0a07/0a04/0a08/0a09),
// Death Borg (pl0105/010a/0a05/0a0a), and Air/Death (pl0d06/0d07/0505/0511).

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";

// ------------------------------------------------------------------
// Per-borg X config (groundSlot, airSlot, hasX) derived from actionStreamTables.json
// ------------------------------------------------------------------

interface BorgConfig {
  hasX: boolean;
  groundSlot: number | null;
  airSlot: number | null;
}

const BORG_CONFIGS: Record<string, BorgConfig> = {
  // Gun Borg — shared engine fallback (no decoded group-4 stream)
  pl0100: { hasX: false, groundSlot: null, airSlot: null },
  pl0108: { hasX: false, groundSlot: null, airSlot: null },
  // Ninja — some have X streams
  pl0002: { hasX: false, groundSlot: null, airSlot: null },
  pl000b: { hasX: false, groundSlot: null, airSlot: null },
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
};

const BORG_NUMBERS: Record<string, number> = {
  pl0100: 0x100, pl0108: 0x108, pl0002: 0x002, pl000b: 0x00b,
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
  const cfg = BORG_CONFIGS[borgId];
  if (!cfg.hasX || cfg.groundSlot === null) {
    // No X stream — generic combat layer owns all actions
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

export function configureWaveBFamily(actor: RomActor, borgId: WaveBBorgId, ctx: StreamContext): void {
  actor.borgNumber = BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createWaveBRootAction(borgId, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
