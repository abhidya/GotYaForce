// Per-move properties (solidity / penetration / refill / explodes / ammo / effect) for the
// roster, distilled from the Gotcha Force Wiki harvest and cross-validated against extracted
// ROM stat rows (behavior-notes (aw)/(ax); generator scripts/gen-borg-move-properties.mjs).
//
// TIER: OBSERVED_WIKI. This is community-cataloged taxonomy, NOT DERIVED from decomp. The port
// consumes it as fallback/reference data:
//   - `penetration` (none | borgs | total) is the target semantics for ATK-008's consume-vs-
//     persist policy; traces T5/T6 remain the arbiter of the engine mechanism.
//   - `refill` maps to the ROM weapon-cell type (all_at_once -> type 0, gradual -> type 1;
//     ROM types 2/3 are dead per (ax)); the DERIVED per-borg values live in sourceBorgStats.
// Nothing here drives gameplay yet; it is exposed for the resolver work (ATK-003/005/008),
// the debug overlay, and validation. Do not treat these values as ROM-confirmed.

import moveData from "./data/borgMoveProperties.json" with { type: "json" };

export type Penetration = "none" | "borgs" | "total";
export type MoveSolidity = "solid" | "nonsolid";
export type MoveRefill = "all_at_once" | "gradual" | "other";

export interface MoveAmmo {
  lv1?: number | null;
  lv10?: number | null;
  raw?: string;
}

export interface BorgMove {
  name: string;
  /** Button label as cataloged: "B Shot" | "B Attack" | "B Charge" | "X" | "X Charge". */
  button: string | null;
  flair: string | null;
  solidity: MoveSolidity | null;
  penetration: Penetration | null;
  refill: MoveRefill | null;
  explodes: boolean | null;
  ammo: MoveAmmo | null;
  /** Player-visible status/effect text, or null for "None". Seeds the status-id mapping (Q8). */
  effect: string | null;
}

export interface BorgMoveProfile {
  wikiTitle: string;
  moves: BorgMove[];
}

type MovePropertiesFile = {
  schema: string;
  provenance: Record<string, string>;
  penetrationEnum: Penetration[];
  romCrossValidation: unknown;
  borgs: Record<string, BorgMoveProfile>;
};

const DATA = moveData as unknown as MovePropertiesFile;

/** OBSERVED_WIKI per-move properties for a borg id, or null if the wiki had no move data. */
export function moveProfileForBorgId(id: string): BorgMoveProfile | null {
  return DATA.borgs[id.toLowerCase()] ?? null;
}

/** The move on `id` matching a button label prefix (e.g. "B Shot", "X"), or null. */
export function moveByButton(id: string, buttonPrefix: string): BorgMove | null {
  const profile = moveProfileForBorgId(id);
  if (!profile) return null;
  return profile.moves.find((m) => (m.button ?? "").toLowerCase().startsWith(buttonPrefix.toLowerCase())) ?? null;
}

/**
 * OBSERVED_WIKI penetration for a borg's primary ranged shot: the "B Charge" move when `charged`,
 * else the "B Shot" move. Returns the penetration enum ("none" | "borgs" | "total") or null when
 * the wiki had no matching move. Drives ATK-008's projectile consume-vs-persist policy (this is
 * the consumer the module header names). Traces T5/T6 remain the arbiter of the engine mechanism
 * — treat as best-known, not ROM-confirmed.
 */
export function shotPenetrationForBorgId(id: string, charged: boolean): Penetration | null {
  const move = moveByButton(id, charged ? "B Charge" : "B Shot");
  return move?.penetration ?? null;
}

/** Number of roster borgs with cataloged move data (coverage metric). */
export function moveDataCoverage(): { borgs: number; moves: number } {
  const borgs = Object.keys(DATA.borgs).length;
  const moves = Object.values(DATA.borgs).reduce((n, b) => n + b.moves.length, 0);
  return { borgs, moves };
}

export const moveCrossValidation = DATA.romCrossValidation;
