// Tank Borg family (pl0c00-pl0c06)
// Covers 6 borgs across 4 constructors.
//
// Constructor groups:
//   0x8007ca5c — pl0c00/pl0c06 (NORMAL TANK / LEOPARD)
//   0x800ad7cc — pl0c01 (GATLING TANK)
//   0x80105144 — pl0c02 (BEAM TANK)
//   0x800b05b4 — pl0c04 (ULTIMATE CANNON)
//   0x800af538 — pl0c05 (ICBM TANK)
//
// Stream data from actionStreamTables.json:
//   pl0c00/pl0c06: a2v0/a2v1 bank=0x802c2e60 group=4 seed=0
//   pl0c04: a2v0/a2v1 bank=0x802fb820 group=2 seed=0; a3v0/a3v1 bank=... group=4 seed=0
//   Others: mostly null (code-driven)

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";

/** Per-borg config flags. */
interface TankConfig {
  hasX: boolean;
  groundSlot: number | null;
  airSlot: number | null;
}

const TANK_CONFIGS: Record<string, TankConfig> = {
  pl0c00: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0c01: { hasX: false, groundSlot: null, airSlot: null },
  pl0c02: { hasX: false, groundSlot: null, airSlot: null },
  pl0c04: { hasX: true, groundSlot: 0, airSlot: 0 },
  pl0c05: { hasX: false, groundSlot: null, airSlot: null },
  pl0c06: { hasX: true, groundSlot: 0, airSlot: 0 },
};

const TANK_BORG_NUMBERS: Record<string, number> = {
  pl0c00: 0xc00, pl0c01: 0xc01, pl0c02: 0xc02,
  pl0c04: 0xc04, pl0c05: 0xc05, pl0c06: 0xc06,
};

function tankXOnHit(actor: RomActor, ctx: StreamContext): void {
  // Standard tank knockback on X hit
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = 6.0;
  actor.hDecel = 0.0;
  actor.yVel = 8.0;
  actor.gravityCoeff = -0.6;
  void ctx;
}

export type TankBorgId = keyof typeof TANK_CONFIGS;

export function createTankRootAction(borgId: TankBorgId, ctx: StreamContext): (actor: RomActor) => void {
  const cfg = TANK_CONFIGS[borgId];
  if (!cfg.hasX || cfg.groundSlot === null) {
    return () => {};
  }
  const xConfig: SharedXConfig = {
    groundSlot: cfg.groundSlot,
    airSlot: cfg.airSlot ?? cfg.groundSlot,
    onHit: tankXOnHit,
  };
  const xHandler = createSharedXSpecial(xConfig, ctx);
  return (actor: RomActor) => {
    if (actor.actionIndex === 2) xHandler(actor);
  };
}

export function configureTankFamily(actor: RomActor, borgId: TankBorgId, ctx: StreamContext): void {
  actor.borgNumber = TANK_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createTankRootAction(borgId, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
