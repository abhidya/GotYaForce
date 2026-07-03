import borgSourceStatsData from "./data/borgSourceStats.json" with { type: "json" };

export interface BorgSourceWeaponSlot {
  ammoType: number;
  ammoCount: number;
  chargeType: number;
  chargeCount: number;
}

export interface BorgSourceStats {
  maxHp: number;
  weaponSlots: [BorgSourceWeaponSlot, BorgSourceWeaponSlot];
}

type BorgSourceStatsRow = {
  maxHp: number;
  weaponSlots: [BorgSourceWeaponSlot, BorgSourceWeaponSlot];
};

type BorgSourceStatsProfile = BorgSourceStats & {
  /** ATK-020: every extracted stat row for this borg (index === row offset, 0..19 per (ag)'s
   *  0x14-row-per-variant stride), so a level-aware caller can select any DAT_804339e8-resolved
   *  offset without re-reading the ROM. `maxHp`/`weaponSlots` above stay pinned to level 0
   *  (row offset 2) for exact backward compatibility with pre-ATK-020 consumers. */
  rows: BorgSourceStatsRow[];
};

type BorgSourceStatsFile = {
  schema: string;
  verification: {
    borgsJsonRows: number;
    runtimeProfiles: number;
    missingRows: string[];
    hpMismatches: Array<{ id: string; catalogHp: number | null; sourceHp: number }>;
  };
  levelRowOffsets: {
    table: number[];
    citation: string;
    discrepancies: unknown[];
  };
  profiles: Record<string, BorgSourceStatsProfile>;
};

const DATA = borgSourceStatsData as unknown as BorgSourceStatsFile;

export const borgSourceStatsSummary = DATA.verification;

/** Re-verified DAT_804339e8 (level byte -> stat-row offset), baked in at generation time from
 *  research/decomp/data/level-row-offsets-804339e8.json (scripts/gen-level-row-offsets.mjs,
 *  citing behavior-notes.md (ak)) by scripts/gen-borg-source-stats.mjs. Exported so
 *  callers/tests can validate row selection against the SAME table this module uses, rather
 *  than a re-typed copy that could drift. */
export const LEVEL_ROW_OFFSETS_804339E8: readonly number[] = DATA.levelRowOffsets.table;

/**
 * Clamp a level byte's table lookup to the table's bounds (32 entries; ticket's "Required
 * behavior": "clamped to the table's 32 entries"). Levels beyond the authored range clamp to
 * the last entry rather than reading out of bounds -- matches (an) section 6's observation that
 * "levels beyond the authored row range read neighboring rows" (i.e. the ROM does not bounds-
 * check either; clamping here is the safe port-side choice, not a ROM-read claim).
 */
function rowOffsetForLevel(level: number): number {
  const table = LEVEL_ROW_OFFSETS_804339E8;
  const idx = Math.max(0, Math.min(table.length - 1, Math.trunc(level)));
  return table[idx] ?? 0;
}

/**
 * Look up a borg's source stats, level-aware (ATK-020). `level` is the raw level BYTE
 * (behavior-notes.md ak: actor+0x3ec), NOT a row offset -- this function performs the
 * DAT_804339e8[level] indirection itself via rowOffsetForLevel(). Omitting `level` (or passing
 * undefined) preserves the EXACT pre-ATK-020 behavior: the baked level-0 / row-offset-2 default
 * row (BorgProfile's default-level anchor, e.g. G RED (pl0615) -> HP 200 / ammo 5).
 */
export function sourceStatsForBorgId(id: string, level?: number): BorgSourceStats | null {
  const profile = DATA.profiles[id.toLowerCase()];
  if (!profile) return null;
  if (level === undefined) return profile;
  const rowOffset = rowOffsetForLevel(level);
  return profile.rows[rowOffset] ?? profile;
}
