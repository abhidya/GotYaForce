// Actor velocity-scale system (param-tier + status timescale) — the ROM's +0x5f8/+0x5f4
// multipliers, ported as a MECHANISM with exact DERIVED tables.
//
// Evidence (research/decomp/movement-hit-decode-2026-07-04.md §1):
//   worldDelta/frame = speed(+0x44) × statusTimescale(+0x5f4) × tierVelScale(+0x5f8)
// - Tier scale: refresh_actor_param_tier_table @0x8006826c reads the 33-row × 3-float table
//   (data/paramTierTables.json, dumped from boot.dol @0x802dd5a0) at row = tier byte +0x74a
//   (default 16 → ×1.0). Row = [sizeScale, animRateScale, velocityScale]; the +4-tier
//   self-buff (zz_011230c_, 1200f) = ×2.366 velocity + ×2.6 size — the "acceleration"
//   special archetype. Which special applies which delta is NOT yet decoded — this module
//   only APPLIES the tier state; nothing writes BorgRuntime.paramTier.tier ≠ 16 yet.
// - Status timescale: FUN_8005a378 (chunk_0007.c:2817-2898) — base ×1.0; burst/fusion flag
//   ×1.5 (FLOAT_804373d8 — the port's BURST.SPEED_MULTIPLIER, applied in movement.ts's
//   existing burstMult, NOT here, to avoid double-count); haste table ×{0.1,1.25,1.5,1.75}
//   (levels +0x70d/+0x70f); slow table ×{0,0.7,0.4,0.2} (levels +0x70c/+0x70e, hit-inflicted
//   chunk_0003.c:7673/8105/8143); freeze ×0.03 while +0x71c counts down. The slow/haste
//   LEVEL fields and their hit-record writers are not yet modeled on BorgRuntime — the
//   accessors below consume them when present so the writers can land incrementally.

import paramTierTablesData from "./data/paramTierTables.json" with { type: "json" };
import type { BorgRuntime } from "./types.js";

interface TierRow {
  tier: number;
  sizeScale: number;
  animRateScale: number;
  velocityScale: number;
}

type ParamTierTablesFile = {
  _meta: Record<string, unknown>;
  tierTables: Record<string, TierRow[]>;
  statusTimescale: {
    slow_802dd57c: number[];
    haste_802dd58c: number[];
    burstFusionMultiplier_804373d8: number;
    freezeMultiplier_804373dc: number;
    base_804373c8: number;
  };
};

const DATA = paramTierTablesData as ParamTierTablesFile;
// The primary tier table (0x802dd5a0). Which page[0xa3] classes select the second table
// (0x802dd720) is undecoded — every borg uses the primary until that selector is read.
const TIER_TABLE = DATA.tierTables["0x802dd5a0"] ?? [];
export const PARAM_TIER_DEFAULT = 16;

function tierRow(tier: number): TierRow | null {
  const clamped = Math.max(0, Math.min(TIER_TABLE.length - 1, Math.trunc(tier)));
  return TIER_TABLE[clamped] ?? null;
}

/** DERIVED tier velocity multiplier (+0x5f8 model): table row at paramTier.tier. ×1.0 at the
 *  default tier 16, so behavior is unchanged until a special writes a tier delta. */
export function tierVelocityScale(b: BorgRuntime): number {
  const row = tierRow(b.paramTier?.tier ?? PARAM_TIER_DEFAULT);
  return row && row.velocityScale > 0 ? row.velocityScale : 1;
}

/** DERIVED tier size multiplier (+0xb8 target; the ROM lerps ±0.05/frame — consumers may
 *  apply directly until the lerp is modeled). */
export function tierSizeScale(b: BorgRuntime): number {
  const row = tierRow(b.paramTier?.tier ?? PARAM_TIER_DEFAULT);
  return row && row.sizeScale > 0 ? row.sizeScale : 1;
}

/** Optional slow/haste level fields (ROM +0x70c..+0x70f model); writers land separately. */
export interface StatusSpeedLevels {
  slowLevel?: number;
  hasteLevel?: number;
}

/** DERIVED status timescale (+0x5f4 model) WITHOUT the burst ×1.5 term (movement.ts applies
 *  that via BURST.SPEED_MULTIPLIER — same FLOAT_804373d8 value, now DERIVED). Freeze is not
 *  yet modeled (statusId↔freeze mapping is T8-blocked). */
export function statusTimescale(b: BorgRuntime & StatusSpeedLevels): number {
  let scale = DATA.statusTimescale.base_804373c8 || 1;
  const haste = b.hasteLevel ?? 0;
  if (haste > 0) scale *= DATA.statusTimescale.haste_802dd58c[Math.min(3, haste)] ?? 1;
  const slow = b.slowLevel ?? 0;
  if (slow > 0) scale *= DATA.statusTimescale.slow_802dd57c[Math.min(3, slow)] ?? 1;
  return scale;
}

/** Combined actor velocity scale (status × tier), excluding the separately-applied burst
 *  multiplier. ×1.0 for every borg until tier/status writers land. */
export function actorVelocityScale(b: BorgRuntime & StatusSpeedLevels): number {
  return statusTimescale(b) * tierVelocityScale(b);
}
