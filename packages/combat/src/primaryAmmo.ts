// Source-backed primary cell 0 only. X bindings and unsupported refill modes are unchanged.
import { sourceStatsForBorgId } from "./sourceBorgStats.js";

/** FUN_800562b8: first row segment binds source cell0. Limit to full-start,
 * finite, positive-parameter rows with decoded refill modes (zz_006dcc0_). */
export function hasSourcePrimaryAmmo(id: string, level?: number): boolean {
  const row = sourceStatsForBorgId(id, level)?.weaponSlots[0];
  return !!row && row.ammoCount > 0 && row.ammoType === row.ammoCount &&
    row.chargeCount > 0 && (row.chargeType === 0 || row.chargeType === 1);
}
