// Nurse/Wizard/Idol family cluster (pl0900-pl090d)
// Covers 13 borgs across 5 constructors. Many share the shared-X-special engine
// (zz_00ff2bc_) with group-4 seeds. This module provides a lightweight family
// registration that maps each borg to its correct X-special config.
//
// Constructor groups:
//   0x80079410 — pl0900/pl0908/pl090d (ANGEL NURSE / SNOW NURSE / HOLY NURSE)
//   0x8014d200 — pl0901 (WITCH)
//   0x8015d674 — pl0902/pl0909 (GUARD WITCH / BASTET WITCH)
//   0x80151790 — pl0903/pl090a (PATRA WITCH / ISIS WITCH)
//   0x8012c498 — pl0904 (MAGIC WITCH)
//   0x801a10e8 — pl0906/pl090b (DEATH BORG THETA / DEATH BORG IOTA)
//   0x801b3c6c — pl0907/pl090c (BASTET WITCH / SEKHMET WITCH)

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";

/** Per-borg X-special config (ground slot, air slot, on-hit). Determined from
 *  actionStreamTables.json group-4 seeds. Null = borg has no group-4 X stream. */
interface XConfig {
  groundSlot: number | null;
  airSlot: number | null;
  hasX: boolean;
}

/** ActionStreamTables-derived X configs for each pl09 borg. */
const NURSE_X_CONFIGS = {
  // ctor 0x80079410 (family bank 0x802c2660) — group 4 slots are runtime-conditional
  pl0900: { groundSlot: null, airSlot: null, hasX: false },
  pl0908: { groundSlot: null, airSlot: null, hasX: false },
  pl090d: { groundSlot: null, airSlot: null, hasX: false },
  // ctor 0x8014d200 (bank 0x8033ff00)
  pl0901: { groundSlot: 0, airSlot: 0, hasX: true },
  // ctor 0x8015d674 (bank 0x80347d00)
  pl0902: { groundSlot: 0, airSlot: 1, hasX: true },
  pl0909: { groundSlot: 0, airSlot: 1, hasX: true },
  // ctor 0x80151790 (bank 0x80341040)
  pl0903: { groundSlot: 0, airSlot: 0, hasX: true },
  pl090a: { groundSlot: 0, airSlot: 0, hasX: true },
  // ctor 0x8012c498 (bank 0x80332980)
  pl0904: { groundSlot: 3, airSlot: 3, hasX: true },
  // ctor 0x801a10e8 (bank 0x80378b80)
  pl0906: { groundSlot: null, airSlot: null, hasX: false },
  pl090b: { groundSlot: null, airSlot: null, hasX: false },
  // ctor 0x801b3c6c (bank 0x80381b40)
  pl0907: { groundSlot: 0, airSlot: 1, hasX: true },
  pl090c: { groundSlot: 0, airSlot: 1, hasX: true },
} as const satisfies Record<string, XConfig>;

/** Borg-number map (hex string → number). Used for projectile variant dispatch. */
const NURSE_BORG_NUMBERS: Record<string, number> = {
  pl0900: 0x900, pl0901: 0x901, pl0902: 0x902, pl0903: 0x903,
  pl0904: 0x904, pl0906: 0x906, pl0907: 0x907, pl0908: 0x908,
  pl0909: 0x909, pl090a: 0x90a, pl090b: 0x90b, pl090c: 0x90c, pl090d: 0x90d,
};

/** On-hit callback for nurse/wizard/idle family — placeholder until DOL-diggable
 *  family-specific callbacks are located.
 *  The ROM likely has per-family on-hit effects (heal, buff, etc.).
 *  For now, a standard small backflip pop (shared pattern). */
function nurseXOnHit(actor: RomActor, ctx: StreamContext): void {
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = 8.0;
  actor.hDecel = 0.0;
  actor.yVel = 12.0;
  actor.gravityCoeff = -0.8;
  void ctx;
}

export type NurseFamilyBorgId = keyof typeof NURSE_X_CONFIGS;

/** Build a rootAction for a single pl09 borg. Uses the shared-X engine when the
 *  borg has a decoded group-4 stream; otherwise falls back to the generic combat layer. */
export function createNurseFamilyRootAction(
  borgId: NurseFamilyBorgId,
  ctx: StreamContext,
): (actor: RomActor) => void {
  const cfg: XConfig = NURSE_X_CONFIGS[borgId];
  let xHandler: ((actor: RomActor) => void) | null = null;

  if (cfg.hasX && cfg.groundSlot !== null) {
    const xConfig: SharedXConfig = {
      groundSlot: cfg.groundSlot,
      airSlot: cfg.airSlot ?? cfg.groundSlot,
      onHit: nurseXOnHit,
    };
    xHandler = createSharedXSpecial(xConfig, ctx);
  }

  // For borgs that only have action-0/1 streams (no X), we wire a null rootAction
  // for action 2 so the generic combat layer handles X. Actions 0/1 keep their
  // cue-table-driven state machines (they're not ported yet, so the cue table still
  // routes through the generic layer for unported actions).
  return (actor: RomActor) => {
    if (actor.actionIndex === 2 && xHandler) {
      xHandler(actor);
    }
  };
}

/** Configure a nurse/wizard/idol-family actor. */
export function configureNurseFamily(
  actor: RomActor,
  borgId: NurseFamilyBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = NURSE_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createNurseFamilyRootAction(borgId, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
