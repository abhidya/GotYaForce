// Exact per-borg melee attack data: action-script-armed HIT kind → hit.bin record
// (frame window + reach) → family damage record.
//
// Sources (all DERIVED):
// - data/meleeAnimKinds.json (scripts/gen-melee-anim-kinds.mjs): the DOL action-script banks
//   (actor+0x1d80/+0x1d84) whose op-0x0a events call zz_008ac80_(actor, kind) — the set of
//   HIT kinds each borg's move scripts arm (pl0615 validation: 27/27 kinds present in its
//   hit.bin remap).
// - data/attackHitTables.json: kind → hitbox records (activeStart/End vs the anim frame,
//   offsets/extents, damageRecordIndex).
// - data/familyDamageRecords.json: damageRecordIndex → the borg family's 0x18 damage record.
//
// SELECTION CAVEAT (the one non-derived link): WHICH script kind is the B-close first swing
// is chosen heuristically as the LOWEST script-armed kind ≥ 1 with a valid frame window
// (kind 0 is the generic shot child's slot). For G RED that picks kind 1 — record f10..12,
// family damage record 2 (hp 30, matching the melee archetype) — consistent with the audit's
// kind ladder reading (kinds 1..7 = the melee chain). The exact command-cue → script
// (group,slot) mapping (actor+0x4f0 state chain) is undecoded; when it lands, per-combo-step
// records replace this single-swing selection. Marked TUNED-selection over DERIVED data.

import meleeAnimKindsData from "./data/meleeAnimKinds.json" with { type: "json" };
import { attackHitMaxReachForKind, attackHitRecordsForKind } from "./attackHitData.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import type { DamageRecord } from "./gauges.js";

type MeleeAnimKindsFile = {
  _meta: Record<string, unknown>;
  banks: Record<string, unknown>;
  borgs: Record<string, { familyBank: string | null; sharedBank: string | null; hitKinds: number[] }>;
};

const DATA = meleeAnimKindsData as unknown as MeleeAnimKindsFile;

export interface ExactMeleeAttack {
  /** The script-armed HIT kind selected as the first B-close swing (see header caveat). */
  kind: number;
  /** First active frame of the swing (hit.bin record +0x06, vs the anim frame clock). */
  activeStart: number;
  /** Last active frame (inclusive, +0x08). */
  activeEnd: number;
  /** Longest hitbox reach across the kind's records (|offset| + max extent/radius). */
  reach: number;
  /** The borg family's exact damage record for this swing, or null if unresolved. */
  damageRecord: DamageRecord | null;
}

const cache = new Map<string, ExactMeleeAttack | null>();

/** Exact first-swing melee data for a borg, or null (callers keep the TUNED profile). */
export function exactMeleeForBorgId(id: string): ExactMeleeAttack | null {
  const key = id.toLowerCase();
  const cached = cache.get(key);
  if (cached !== undefined) return cached;

  const entry = DATA.borgs[key];
  let result: ExactMeleeAttack | null = null;
  if (entry) {
    for (const kind of [...entry.hitKinds].sort((a, b) => a - b)) {
      if (kind < 1) continue; // kind 0 = the generic shot child's slot
      const records = attackHitRecordsForKind(key, kind);
      const windowed = records.find((record) => record.activeEnd >= record.activeStart && record.activeStart >= 0);
      if (!windowed) continue;
      const reach = attackHitMaxReachForKind(key, kind);
      result = {
        kind,
        activeStart: windowed.activeStart,
        activeEnd: windowed.activeEnd,
        reach: reach ?? 0,
        damageRecord: familyDamageRecordForBorg(key, windowed.damageRecordIndex),
      };
      break;
    }
  }
  cache.set(key, result);
  return result;
}
