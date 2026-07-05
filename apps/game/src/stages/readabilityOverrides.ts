// Per-stage battle-readability overrides.
//
// Source of truth: research/asset-coverage/stage-readability.{md,json}, produced by
// scripts/audit-stage-readability.mjs (rtk proxy node scripts/audit-stage-readability.mjs).
// That script derives, per stage, purely from the authored render-state.json + STIH collision
// bins: background/fog luma, ambient+directional light intensity sum, fog near/far vs the
// arena's own collision footprint diagonal, visual-vs-collision bounds sanity, and spawn-floor
// sanity. It flags a small composite risk set (too-dark / too-flat / fog-clip / bounds-mismatch
// / spawn-empty); as of the audit run recorded below, 40/40 stages pass everything EXCEPT the
// three fog-clip cases handled here.
//
// This module is the ONLY place minimal fixes for audit-flagged stages live. Every entry below
// is TUNED and must cite the exact audit line that justified it. Stages the audit does not flag
// are NOT touched here — the authored render-state.json stays the sole source for them, applied
// via stages/lighting.ts with no override layer in between.
//
// Overrides apply ON TOP of the resolved render-state (see applyStageReadabilityOverrides),
// never replacing the HSD-authored ambient/directional colors or camera fov/near.

import type { ResolvedStageLighting } from "./lighting";

export type StageReadabilityOverride = {
  /** Free-text audit citation — the exact stage-readability.md line that justified this entry. */
  justification: string;
  /**
   * Fog-far floor (world units). Applied only when the resolved fog.far is BELOW this value,
   * i.e. this only ever pushes the fog wall further out, never pulls it in.
   */
  fogFarMin?: number;
};

// DERIVED — research/asset-coverage/stage-readability.json (generatedAt 2026-07-05T04:54:12.132Z),
// thresholds { FOG_CLIP_MARGIN: 1 } (fog.end must be >= 1x the arena's tight collision XZ
// diagonal). All three GREATER TRICITY AREA family stages (st0x/st2x/st4x variant of stage byte
// 0x09) share the same authored render-state fog (start 2000, end 25000) against a collision
// footprint diagonal of ~28284 — the far fog plane sits INSIDE the arena, so a player standing
// near one edge sees the opposite side fade into the fog/background color before reaching the
// visual boundary. TUNED fix: clamp fog.far up to the arena diagonal (rounded up) so the fog
// wall sits at or beyond the true collision footprint; near/color/camera and every other stage
// are untouched.
export const STAGE_READABILITY_OVERRIDES: Readonly<Record<string, StageReadabilityOverride>> = {
  st09: {
    justification:
      "research/asset-coverage/stage-readability.md#st09 — fog-clip: fog.end=25000.000 < arena collision XZ diagonal=28284.271",
    fogFarMin: 28285,
  },
  st29: {
    justification:
      "research/asset-coverage/stage-readability.md#st29 — fog-clip: fog.end=25000.000 < arena collision XZ diagonal=28284.271",
    fogFarMin: 28285,
  },
  st49: {
    justification:
      "research/asset-coverage/stage-readability.md#st49 — fog-clip: fog.end=25000.000 < arena collision XZ diagonal=28284.271",
    fogFarMin: 28285,
  },
};

/**
 * Apply this stage's readability override (if any) on top of an already-resolved lighting
 * state. Pure function; never mutates its input. Stages with no override entry are returned
 * unchanged (same object reference) so callers can rely on referential no-ops for the 37/40
 * stages the audit does not flag.
 */
export function applyStageReadabilityOverrides(
  stageId: string,
  resolved: ResolvedStageLighting,
): ResolvedStageLighting {
  const override = STAGE_READABILITY_OVERRIDES[stageId];
  if (!override) return resolved;

  let { fog } = resolved;
  if (override.fogFarMin !== undefined && fog && fog.far < override.fogFarMin) {
    fog = { ...fog, far: override.fogFarMin };
  }

  if (fog === resolved.fog) return resolved;
  return { ...resolved, fog };
}
