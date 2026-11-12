// Source ammo math shared by bounded primary cell0 rows and Diver cell2.
// See research/decomp/primary-ammo-binding-2026-11-11.md and diver-ammo-binding-2026-11-11.md.
import { isNurseX } from "./nurseInput.js";
import tables from "./data/paramTierTables.json" with { type: "json" };
import type { BorgRuntime, WeaponCell } from "./types.js";
import type { ContactAuraLevels } from "./timescale.js";

export function isDiverAmmoFamily(id: string): boolean {
  return id === "pl0805" || id === "pl080d" || id === "pl080e";
}

/** Proven X stat segment maps to source cell 2; browser cell 1 is its HUD alias. */
export function hasSourceXAmmo(id: string): boolean {
  return id === "pl0005" || id === "pl0000" || id === "pl000a" || isNurseX(id) || isDiverAmmoFamily(id) || id === "pl0002" || id === "pl000b" || id === "pl0101" || id === "pl0102" || id === "pl0106" || id === "pl0104" || id === "pl0100" || id === "pl0108";
}

export interface DiverRefillContext {
  readonly all: readonly BorgRuntime[];
  readonly auras: ReadonlyMap<string, ContactAuraLevels>;
}

// FLOAT_804376c8: verified GG4E DOL f32 bits0x41200000 (10.0).
// Byte provenance and DOL SHA256: primary-ammo-binding-2026-11-11.md.
export const SOURCE_EXTRA_BURST_REFILL_MULTIPLIER = 10;
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
  // +0x6fc is the paired/team burst byte, not the initiator-only +0x6fd.
  let rate = b.burstPaired ? status.burstFusionMultiplier_804373d8 : status.base_804373c8;
  const aura = context?.auras.get(b.uid);
  for (const level of [aura?.hasteAuraLevel ?? b.hasteAuraLevel ?? 0, b.hasteHitLevel ?? 0]) {
    if (level > 0) rate = Math.fround(rate * (status.haste_802dd58c[Math.min(3, level)] ?? 1));
  }
  if (!b.burstPaired && !b.sourceAmmoSlowImmune &&
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
  stepSourceAmmoRefill(cell, b, 2);
}

/** zz_006dcc0_ source modes 0/1; callers bind the source slot, not the HUD alias. */
export function stepSourceAmmoRefill(cell: WeaponCell, b: BorgRuntime, sourceSlot: number): void {
  if (((b.sourceAmmoRefillPauseMask ?? 0) & (1 << sourceSlot)) !== 0 || cell.timer <= 0) return;
  if ((cell.refillType !== 0 && cell.refillType !== 1) || cell.refillParam <= 0) return;
  const rate = Math.fround((b.sourceAmmoRefillRate ?? status.base_804373c8) *
    (b.burstPaired ? SOURCE_EXTRA_BURST_REFILL_MULTIPLIER : 1));
  cell.timer = Math.fround(cell.timer - rate);
  if (cell.refillType === 0) {
    if (cell.timer <= 0) { cell.cur = cell.max; cell.timer = 0; }
    return;
  }
  cell.cur = cell.timer <= 0 ? cell.max :
    cell.max - (Math.trunc(Math.fround(cell.timer / cell.refillParam)) + 1);
}

/** Source actor update refills BEFORE rebuilding +0x768 for the next frame:
 * FUN_80055568 -> zz_005568c_ -> zz_006dcc0_, then zz_0059068_ -> FUN_8005a378.
 * Battle calls this after discrete status decay with its frozen contact snapshot. */
export function refreshDiverAmmoRate(b: BorgRuntime, context?: DiverRefillContext): void {
  b.sourceAmmoRefillRate = diverAmmoBaseRate(b, context);
}
