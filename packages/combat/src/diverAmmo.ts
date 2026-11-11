// Bounded source ammo lane for the three Diver forms. Other families retain their
// existing refill policy. See research/decomp/diver-ammo-binding-2026-11-11.md.
import tables from "./data/paramTierTables.json" with { type: "json" };
import type { BorgRuntime, WeaponCell } from "./types.js";
import type { ContactAuraLevels } from "./timescale.js";

export function isDiverAmmoFamily(id: string): boolean {
  return id === "pl0805" || id === "pl080d" || id === "pl080e";
}

export interface DiverRefillContext {
  readonly all: readonly BorgRuntime[];
  readonly auras: ReadonlyMap<string, ContactAuraLevels>;
}

// FLOAT_804376c8 is not in the available committed exports. This neutral fallback
// deliberately omits the additional burst refill boost; it is NOT a decoded 1.0.
export const UNRESOLVED_EXTRA_BURST_REFILL_MULTIPLIER = 1;
const status = tables.statusTimescale;

/** FUN_8005a378 +0x768, not movement's +0x5f4: freeze does not replace this rate.
 * Fusion-role writes are not integrated; explicit runtime seams are honored. A
 * missing partner rate uses baseline instead of inventing an inherited rate. */
export function diverAmmoBaseRate(
  b: BorgRuntime, context?: DiverRefillContext,
): number {
  if (b.fusionState !== 0) return status.base_804373c8;
  if (b.sourceFusionRole === 2) {
    const partner = context?.all.find((other) => other.uid === b.fusionPartnerUid);
    return partner?.sourceAmmoRefillRate ?? status.base_804373c8;
  }
  let rate = b.burstActive ? status.burstFusionMultiplier_804373d8 : status.base_804373c8;
  const aura = context?.auras.get(b.uid);
  for (const level of [aura?.hasteAuraLevel ?? b.hasteAuraLevel ?? 0, b.hasteHitLevel ?? 0]) {
    if (level > 0) rate = Math.fround(rate * (status.haste_802dd58c[Math.min(3, level)] ?? 1));
  }
  if (!b.burstActive && !b.sourceAmmoSlowImmune &&
      !b.sourceFusionCarried && (b.sourceFusionRole ?? 0) === 0) {
    for (const level of [aura?.slowAuraLevel ?? b.slowAuraLevel ?? 0, b.slowHitLevel ?? 0]) {
      if (level > 0) rate = Math.fround(rate * (status.slow_802dd57c[Math.min(3, level)] ?? 1));
    }
  }
  return rate;
}

/** zz_006dcc0_ type 1: subtract rate from debt, then derive INTEGER ammunition.
 * It is not a fractional grant. For the one-charge Diver row, cur stays zero until
 * the timer crosses zero. No freeze, tier-speed multiplier, or busy-state pause. */
export function stepDiverXRefill(cell: WeaponCell, b: BorgRuntime): void {
  if (((b.sourceAmmoRefillPauseMask ?? 0) & 4) !== 0 || cell.timer <= 0) return;
  if (cell.refillType !== 1 || cell.refillParam <= 0) return;
  const rate = (b.sourceAmmoRefillRate ?? status.base_804373c8) *
    (b.burstActive ? UNRESOLVED_EXTRA_BURST_REFILL_MULTIPLIER : 1);
  cell.timer = Math.fround(cell.timer - rate);
  cell.cur = cell.timer <= 0 ? cell.max :
    cell.max - (Math.trunc(Math.fround(cell.timer / cell.refillParam)) + 1);
}

/** Source actor update refills BEFORE rebuilding +0x768 for the next frame:
 * FUN_80055568 -> zz_005568c_ -> zz_006dcc0_, then zz_0059068_ -> FUN_8005a378.
 * Battle calls this after discrete status decay with its frozen contact snapshot. */
export function refreshDiverAmmoRate(b: BorgRuntime, context?: DiverRefillContext): void {
  b.sourceAmmoRefillRate = diverAmmoBaseRate(b, context);
}
