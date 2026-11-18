import borgData from "../../../../packages/assets/data/borgs.json";

import { createBorgRoster, type BorgAssetEntry, type BorgRoster, type BorgRosterData } from "@gf/assets";
import {
  actionProfileForProfile,
  buildProfile,
  type BorgActionProfile,
  type BorgProfile,
  type BorgStats,
} from "@gf/combat";
import type { ForceBorg, ForceSlot } from "../ui/index.js";

export const DEFAULT_LEAD = "pl0615"; // G Red, fully animated default lead.

const DEFAULT_FORCE_SLOT_SEEDS: ForceSlot[] = [
  { no: 1, name: "G RED FORCE", borgIds: [DEFAULT_LEAD] },
  { no: 2, name: "DEATH BORG FORCE", borgIds: ["pl0008", "pl000c"] },
  { no: 3, name: "GUN BORG FORCE", borgIds: ["pl0102", "pl0104"] },
  // Browser starter presets, not a claim about the retail memory-card contents.
  // Each full roster fits Challenge's lowest (1500) energy budget. Existing
  // saved slots take precedence when syncForceSlots restores them.
  { no: 4, name: "G RED ALL STARS", borgIds: ["pl0615", "pl0000", "pl0100", "pl0200", "pl0300", "pl0103"] },
  { no: 5, name: "NINJA SQUAD", borgIds: ["pl0000", "pl0001", "pl0002", "pl0004", "pl0307"] },
  { no: 6, name: "GUNNER SQUAD", borgIds: ["pl0100", "pl0101", "pl0102", "pl0103", "pl0107"] },
  { no: 7, name: "KNIGHT AND ROBOT", borgIds: ["pl0200", "pl0201", "pl0400", "pl0407"] },
];

export interface GameBorgCatalog {
  roster: readonly BorgAssetEntry[];
  rosterIndex: BorgRoster;
  combatStats: readonly BorgStats[];
  profiles: ReadonlyMap<string, BorgProfile>;
  forceCatalog: readonly ForceBorg[];
  forceById: ReadonlyMap<string, ForceBorg>;
  defaultForceSlots: readonly ForceSlot[];
  actionProfileFor(borgId: string): BorgActionProfile | null;
  forceFromSlot(slot: ForceSlot): string[];
}

export function createGameBorgCatalog(data: BorgRosterData): GameBorgCatalog {
  const rosterIndex = createBorgRoster(data);
  const roster = rosterIndex.entries;
  const combatStats = roster as readonly BorgStats[];
  const profiles = new Map(combatStats.map((borg) => [borg.id, buildProfile(borg)] as const));
  const forceCatalog: ForceBorg[] = [...rosterIndex.forceCatalog()];
  const forceById = new Map(forceCatalog.map((entry) => [entry.id, entry] as const));

  return {
    roster,
    rosterIndex,
    combatStats,
    profiles,
    forceCatalog,
    forceById,
    defaultForceSlots: DEFAULT_FORCE_SLOT_SEEDS.map((slot) => ({ ...slot, borgIds: [...slot.borgIds] })),
    actionProfileFor(borgId) {
      const profile = profiles.get(borgId);
      return profile ? actionProfileForProfile(profile) : null;
    },
    forceFromSlot(slot) {
      return rosterIndex.validIds(slot.borgIds, { fallbackId: DEFAULT_LEAD });
    },
  };
}

export const BORG_CATALOG = createGameBorgCatalog(borgData as BorgRosterData);
