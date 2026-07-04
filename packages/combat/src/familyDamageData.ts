// Per-family damage-record tables — runtime adapter.
//
// Source: data/familyDamageRecords.json (scripts/gen-family-damage-records.mjs): every borg
// family constructor binds its OWN 0x18-stride damage-record table at actor+0x27c (per-borg
// resolved through the ctor's id-compare branches; 208/208 borgs, 124 distinct tables). The
// hit pipeline resolves a hit's record as `*(hitbox+0x2c) + hitboxRecord.damageRecordIndex *
// 0x18` with no bounds check (chunk_0003.c:7514) — i.e. the attack hitbox record's u16+0x04
// indexes THIS table, not the 9-record generic family-01 table in data/damageRecords.json
// (which remains the archetype fallback for hits without exact hitbox records).
// Evidence: research/decomp/movement-hit-decode-2026-07-04.md §3.

import familyDamageRecordsData from "./data/familyDamageRecords.json" with { type: "json" };
import type { DamageRecord } from "./gauges.js";

type FamilyDamageRecordsFile = {
  _meta: Record<string, unknown>;
  tables: Record<string, { address: string; records: DamageRecord[] }>;
  borgs: Record<string, { tableAddress: string; recordCount: number }>;
};

const DATA = familyDamageRecordsData as unknown as FamilyDamageRecordsFile;

/** The borg's family damage record at `index` (the attack hitbox record's damageRecordIndex),
 *  or null when the borg/table/index is unknown — callers keep the archetype fallback. */
export function familyDamageRecordForBorg(borgId: string, index: number): DamageRecord | null {
  const binding = DATA.borgs[borgId.toLowerCase()];
  if (!binding) return null;
  const table = DATA.tables[binding.tableAddress];
  if (!table) return null;
  const record = table.records[index];
  return record ?? null;
}

/** Number of records in the borg's family table (0 when unknown). */
export function familyDamageRecordCountForBorg(borgId: string): number {
  const binding = DATA.borgs[borgId.toLowerCase()];
  return binding?.recordCount ?? 0;
}
