// Fortress Borg family (pl0e00-pl0e05)
// Covers 6 borgs. All are code-driven (no stream banks extracted).
// These are immobile turret-style units; actions are implemented entirely in
// code (no animation stream dependency for their attack logic).

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Borg numbers for Fortress Borg family members. */
const FORTRESS_BORG_NUMBERS: Record<string, number> = {
  pl0e00: 0xe00, pl0e01: 0xe01, pl0e02: 0xe02,
  pl0e03: 0xe03, pl0e04: 0xe04, pl0e05: 0xe05,
};

export type FortressBorgId = keyof typeof FORTRESS_BORG_NUMBERS;

export function configureFortressFamily(actor: RomActor, borgId: FortressBorgId, _ctx: StreamContext): void {
  actor.borgNumber = FORTRESS_BORG_NUMBERS[borgId] ?? 0;
  // Fortress borgs are entirely code-driven; their root action is null
  // so the generic combat layer handles all actions.
  actor.rootAction = null;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
