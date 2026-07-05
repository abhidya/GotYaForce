// @gf/missions — getSystem.ts
//
// The Borg GET / Gotcha-Box drop pipeline. DERIVED from the fully decoded ROM system
// (research/decomp/items-evidence-inventory-2026-07-05.md — cite inline per section below).
// Every non-table constant/algorithm step here traces to that doc; nothing is guessed.
//
// Pipeline (doc §3):
//   1. registerKill(pool, victimBorgId, victimColorVariant, rng) on every cross-team kill of
//      a "scoring actor" — §2a/2b. Adds a random 1..16 points to the (borgId, colorVariant)
//      pool entry, creating it if absent. The CYBER DEATH DRAGON (pl0503) special case
//      credits its two fusion components instead (§2a, chunk_0003.c:8061-8064).
//   2. snapshotPool()/restorePool() around a battle — win KEEPS the pool progress, lose or
//      abandon REVERTS it to the pre-battle snapshot (§2c, zz_01820d4_/zz_0182110_).
//   3. rollDrops(pool, table, rng) after a WON battle — walks the pool in insertion order;
//      each entry whose points >= threshold[colorVariant] "drops" (points reset to 0, entry
//      stays in the pool at 0 for future re-accrual) and yields a GET (§2d, zz_0182228_).
//
// RNG: injected `() => number` in [0,1) (the @gf/missions seeded-RNG convention — see
// createChallengeRng in challenge.ts). Math.random is banned in sim code; ROM parity for
// the exact byte-RNG (zz_00055fc_) is out of scope for the port (doc §3.6) — only the
// documented VALUE RANGES (1..16 points, uniform 1..N part index) are reproduced.

import dropTableData from "./data/borgGetDropTable.json" with { type: "json" };

// --- Drop table -----------------------------------------------------------------------

export type GetColorVariant = 0 | 1 | 2 | 3 | 4 | 5;

/** Variant order fixed by the DOL/CSV cross-validation (borgGetDropTable.json _meta). */
export const GET_COLOR_VARIANT_NAMES = [
  "normal",
  "altColor",
  "gold",
  "silver",
  "crystal",
  "black",
] as const;

export interface GetDropTableRow {
  borgId: string;
  /** 1 = whole-unit drop; 2..5 = split into N collectible parts. */
  partsKind: number;
  thresholds: {
    normal: number;
    altColor: number;
    gold: number;
    silver: number;
    crystal: number;
    black: number;
  };
}

export interface GetDropTableMeta {
  source: string;
  rowCount: number;
  killCredits: { note: string; pl0503: string[] };
  pointsPerKill: { min: number; max: number; note: string };
  poolCap: number;
  pointsCap: number;
  evidenceDoc: string;
  [key: string]: unknown;
}

export interface GetDropTable {
  _meta: GetDropTableMeta;
  rows: GetDropTableRow[];
}

const DROP_TABLE = dropTableData as unknown as GetDropTable;

/** The 197-row table extracted from boot.dol (scripts/extract-borg-get-drop-table.mjs). */
export const BORG_GET_DROP_TABLE: GetDropTable = DROP_TABLE;

/** poolCap (§2b: DAT_80436354+0x1518, up to 1536 packed entries). */
export const GET_POOL_CAP = DROP_TABLE._meta.poolCap;
/** pointsCap (§2b: points saturate below 0x10000). */
export const GET_POINTS_CAP = DROP_TABLE._meta.pointsCap;
/** pointsPerKill range (§2b: (rng8() & 0xF) + 1). */
export const GET_POINTS_PER_KILL_MIN = DROP_TABLE._meta.pointsPerKill.min;
export const GET_POINTS_PER_KILL_MAX = DROP_TABLE._meta.pointsPerKill.max;

/**
 * DERIVED — chunk_0003.c:8061-8064: killing pl0503 (CYBER DEATH DRAGON, a fusion with no
 * GET row of its own) instead registers a kill for its two fusion components. Read from the
 * extracted table's _meta so the mapping stays data-driven (only pl0503 has an entry today).
 */
export const GET_KILL_CREDITS: ReadonlyMap<string, readonly string[]> = new Map(
  Object.entries(DROP_TABLE._meta.killCredits).filter(([key]) => key !== "note") as [string, string[]][],
);

const ROW_BY_BORG_ID: ReadonlyMap<string, GetDropTableRow> = new Map(
  DROP_TABLE.rows.map((row) => [row.borgId, row]),
);

/** Look up a borg's drop-table row, or null if it never drops (no row = never-drop borg). */
export function getDropRowForBorgId(borgId: string): GetDropTableRow | null {
  return ROW_BY_BORG_ID.get(borgId) ?? null;
}

function thresholdForVariant(row: GetDropTableRow, variant: GetColorVariant): number {
  const name = GET_COLOR_VARIANT_NAMES[variant];
  return row.thresholds[name];
}

// --- Pool model -------------------------------------------------------------------------

/** One GET-pool entry: accrued points for one (borgId, colorVariant) pair. */
export interface GetPoolEntry {
  borgId: string;
  colorVariant: GetColorVariant;
  points: number;
}

/**
 * The GET pool: per-(borgId,colorVariant) accrued points, insertion-ordered (§2b/2d — the
 * ROM's roll walks the pool in insertion order and a kill appends a new entry only when the
 * exact (variant, borgId) pair is absent). Plain data — no class — so it round-trips through
 * JSON for localStorage persistence untouched.
 */
export interface GetPool {
  /** Insertion-ordered entries. */
  entries: GetPoolEntry[];
}

/** A fresh, empty GET pool. */
export function createGetPool(): GetPool {
  return { entries: [] };
}

/** Deep-clone a pool (used for the pre-battle snapshot, §2c). */
export function clonePool(pool: GetPool): GetPool {
  return { entries: pool.entries.map((e) => ({ ...e })) };
}

function findEntry(pool: GetPool, borgId: string, colorVariant: GetColorVariant): GetPoolEntry | undefined {
  return pool.entries.find((e) => e.borgId === borgId && e.colorVariant === colorVariant);
}

/**
 * DERIVED — zz_018214c_ (§2b, chunk_0045.c:4727-4762): random 1..16 points via
 * `(rng8() & 0xF) + 1`. `rng` is the injected [0,1) generator (missions RNG convention).
 */
export function rollPointsGain(rng: () => number): number {
  const span = GET_POINTS_PER_KILL_MAX - GET_POINTS_PER_KILL_MIN + 1;
  return GET_POINTS_PER_KILL_MIN + Math.floor(clamp01(rng()) * span);
}

/**
 * DERIVED — zz_0182228_'s part-index roll (§2d, chunk_0045.c:4806-4810):
 * `(rng8()>>4) mod N`, then `+1` for a 1-based part index. Uniform over 1..partsCount.
 */
export function rollPartIndex(rng: () => number, partsCount: number): number {
  if (partsCount <= 1) return 1;
  return 1 + Math.floor(clamp01(rng()) * partsCount);
}

function clamp01(x: number): number {
  return Math.max(0, Math.min(0.999999999, x));
}

/**
 * Register one kill's GET accrual (§2a/2b). Adds `rollPointsGain(rng)` points to the
 * (victimBorgId, victimColorVariant) pool entry, creating it if absent (capped at
 * GET_POOL_CAP total entries — the ROM's 1536-entry cap, §2b). Points saturate at
 * GET_POINTS_CAP (never wrap).
 *
 * Special case (§2a, chunk_0003.c:8061-8064): killing pl0503 (CYBER DEATH DRAGON) instead
 * registers a kill for BOTH of its fusion components (pl0505 DEATH HEAD, pl0506 CYBER
 * DRAGON) at the SAME victimColorVariant — each independently rolls its own 1..16 gain
 * (matches the ROM calling zz_018214c_ twice, once per credited id).
 *
 * Mutates `pool` in place and returns it (for chaining/clarity at call sites).
 */
export function registerKill(
  pool: GetPool,
  victimBorgId: string,
  victimColorVariant: GetColorVariant,
  rng: () => number,
): GetPool {
  const credited = GET_KILL_CREDITS.get(victimBorgId) ?? [victimBorgId];
  for (const creditedBorgId of credited) {
    addPoints(pool, creditedBorgId, victimColorVariant, rollPointsGain(rng));
  }
  return pool;
}

function addPoints(pool: GetPool, borgId: string, colorVariant: GetColorVariant, gain: number): void {
  const existing = findEntry(pool, borgId, colorVariant);
  if (existing) {
    existing.points = Math.min(GET_POINTS_CAP, existing.points + gain);
    return;
  }
  if (pool.entries.length >= GET_POOL_CAP) return; // ROM pool is a fixed 1536-entry array.
  pool.entries.push({ borgId, colorVariant, points: Math.min(GET_POINTS_CAP, gain) });
}

// --- Snapshot / restore (lose or abandon revert, §2c) ------------------------------------

/**
 * Pre-battle snapshot for the lose/abandon revert (§2c, zz_01820d4_/zz_0182110_): the ROM
 * backs up the WHOLE pool buffer+count before a battle and restores it wholesale on a
 * non-win outcome. `clonePool` already deep-copies, so the returned snapshot is independent
 * of subsequent mutation of `pool`.
 */
export function snapshotPool(pool: GetPool): GetPool {
  return clonePool(pool);
}

/**
 * Revert `pool` in place to `snapshot` (lose/abandon path, §2c). Returns the same `pool`
 * object (mutated) so call sites can keep a single stable reference across battles.
 */
export function restorePool(pool: GetPool, snapshot: GetPool): GetPool {
  pool.entries = snapshot.entries.map((e) => ({ ...e }));
  return pool;
}

// --- Drop roll (§2d) ----------------------------------------------------------------------

export type GetDropKind = "unit" | "parts";

/** One rolled drop (§2d: (borgId, variant, partIndex); partIndex 0 = whole unit). */
export interface GetDrop {
  borgId: string;
  colorVariant: GetColorVariant;
  kind: GetDropKind;
  /** 0 for a whole-unit drop; 1-based part index (1..partsCount) for a parts drop. */
  partIndex: number;
  /** partsKind's N for a parts drop (undefined for a whole-unit drop). */
  partsCount?: number;
}

/**
 * Roll every qualifying drop out of `pool` (§2d, zz_0182228_): scans entries in insertion
 * order; an entry whose points >= threshold[colorVariant] for its row "drops" — points
 * reset to 0 (the entry itself is KEPT, at 0, so it can re-accrue toward its next drop —
 * matches the ROM keeping the pool slot and only clearing the low 16 bits, chunk_0045.c:
 * 4793-4794) — and yields a GetDrop. Entries with no drop-table row (never-drop borgs)
 * or a -1 threshold for their variant never qualify.
 *
 * The ROM's zz_0182228_ returns ONE drop per call and the caller loops; this port's
 * rollDrops does the whole loop itself and returns every drop from this roll, in the same
 * scan order, for caller simplicity (equivalent output, no behavior difference visible to
 * callers since nothing reads the pool between drops mid-loop).
 */
export function rollDrops(pool: GetPool, rng: () => number): GetDrop[] {
  const drops: GetDrop[] = [];
  for (const entry of pool.entries) {
    const row = getDropRowForBorgId(entry.borgId);
    if (!row) continue; // never-drop borg (no table row).
    const threshold = thresholdForVariant(row, entry.colorVariant);
    if (threshold < 0) continue; // this color variant can never drop for this borg.
    if (entry.points < threshold) continue; // hasn't accrued enough yet.

    entry.points = 0; // DERIVED: points reset to 0 on drop (chunk_0045.c:4793-4794).

    if (row.partsKind <= 1) {
      drops.push({ borgId: entry.borgId, colorVariant: entry.colorVariant, kind: "unit", partIndex: 0 });
    } else {
      const partsCount = row.partsKind;
      const partIndex = rollPartIndex(rng, partsCount);
      drops.push({
        borgId: entry.borgId,
        colorVariant: entry.colorVariant,
        kind: "parts",
        partIndex,
        partsCount,
      });
    }
  }
  return drops;
}
