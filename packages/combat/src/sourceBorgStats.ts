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

/** Raw DAT_804339e8 dump, baked from research/decomp/data/level-row-offsets-804339e8.json
 *  (scripts/gen-level-row-offsets.mjs). Exported for reference/validation ONLY. NOTE: this
 *  table's true role is UNCONFIRMED and it is NOT used for stat-row selection -- see the
 *  correction on rowOffsetForLevel(). Its values ([2,2,8,6,0,4,...]) are non-monotonic, so it
 *  cannot be the per-level row offset (that would make HP fall as a borg levels up). The (ag)
 *  reading that treated it as the row offset conflated something; retained here so the true
 *  role can be re-derived later without re-reading the ROM. */
export const LEVEL_ROW_OFFSETS_804339E8: readonly number[] = DATA.levelRowOffsets.table;

/**
 * Map a level BYTE (actor+0x3ec, 0-based: a freshly-obtained "level 1" borg is byte 0, per the
 * (ag) live anchor DAT_804339e8[0] and the save-format decode (au)) to a stat-row index.
 *
 * EMPIRICAL RULE (behavior-notes (av)/(aw), CORRECTED from the (ag)-era DAT_804339e8 reading):
 *   rowIndex = levelByte + 2   (i.e. display level + 1: display-1 -> row 2, display-10 -> row 11)
 * Validated 200/203 across the roster by cross-checking the wiki's lv1/lv10 HP against the
 * extracted rows (row[2]=lv1 HP, row[11]=lv10 HP), and monotonic (G RED: 200,210,...,290). The 3
 * outliers (pl0400/pl0507/pl0d01) are the wiki's non-"Normal Level-up Schedule" borgs -- their
 * per-borg schedules are an open item; this function applies the normal-schedule rule to all.
 * Clamped to the borg's available rows (glitch/out-of-range levels read neighbouring rows per
 * (an) s6; clamping is the safe port choice, not a ROM-read claim).
 */
function rowOffsetForLevel(level: number, rowCount: number): number {
  const idx = Math.trunc(level) + 2;
  return Math.max(0, Math.min(rowCount - 1, idx));
}

/**
 * Look up a borg's source stats, level-aware (ATK-020, row-index CORRECTED). `level` is the raw
 * level BYTE (behavior-notes ak: actor+0x3ec, 0-based). Omitting `level` (or passing undefined)
 * preserves the EXACT pre-ATK-020 default: the baked level-0 default row (row offset 2, e.g.
 * G RED (pl0615) -> HP 200 / ammo 5). Passing level 0 resolves the same row (byte 0 -> row 2),
 * so the default and explicit-level-0 paths agree.
 */
export function sourceStatsForBorgId(id: string, level?: number): BorgSourceStats | null {
  const profile = DATA.profiles[id.toLowerCase()];
  if (!profile) return null;
  if (level === undefined) return profile;
  const rowOffset = rowOffsetForLevel(level, profile.rows.length);
  return profile.rows[rowOffset] ?? profile;
}
