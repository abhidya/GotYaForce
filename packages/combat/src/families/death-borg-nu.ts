// Death/Bug Borg Nu family (pl0f00-pl0f06)
// Covers 7 borgs. All are code-driven with no stream banks extracted.
// These are small disposable borgs (Death Borg Nu/Mu/Chi, Roach, Death Eye).

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Borg numbers for Nu-family members. */
const NU_BORG_NUMBERS: Record<string, number> = {
  pl0f00: 0xf00, pl0f01: 0xf01, pl0f02: 0xf02,
  pl0f03: 0xf03, pl0f04: 0xf04, pl0f05: 0xf05, pl0f06: 0xf06,
};

export type NuBorgId = keyof typeof NU_BORG_NUMBERS;

export function configureNuFamily(actor: RomActor, borgId: NuBorgId, _ctx: StreamContext): void {
  actor.borgNumber = NU_BORG_NUMBERS[borgId] ?? 0;
  // Code-driven; generic combat layer handles all action logic.
  actor.rootAction = null;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
