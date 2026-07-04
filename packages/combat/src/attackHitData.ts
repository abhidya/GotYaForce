// Per-borg attack HIT tables (pl####hit.bin) — runtime adapter.
//
// Source: data/attackHitTables.json (scripts/gen-attack-hit-tables.mjs). The ROM's attack
// pipeline selects a HIT "kind" via zz_008ac80_(actor, kind); the borg's remap block
// (+0xa20, 32 slots × 4 entries) maps the kind to up to four 0x50-stride hitbox records
// carrying the REAL per-move data the port previously faked with generic archetypes:
//   - damageRecordIndex: which damage record the hit uses (per-borg range, superset of the
//     9 global family records in data/damageRecords.json),
//   - activeStart/activeEnd: the exact active frame window of the attack,
//   - shape/bone/localOffset/halfExtent/radius: the authored hitbox volume.
//
// Only accessors here — WHICH kind an attack context uses is wired in combat.ts from the
// decoded literal zz_008ac80_ call sites; undecoded (dynamic) kinds stay unconsumed.

import attackHitTablesData from "./data/attackHitTables.json" with { type: "json" };

export interface AttackHitRecord {
  /** u8 +0x00 — hit shape kind (0 = box/segment family, 2 = swept sphere family; semantics
   *  per hit-bin census — consume radius/halfExtent, don't branch on unproven shapes). */
  shapeKind: number;
  /** u8 +0x01 low 7 bits — bone the hitbox attaches to. */
  boneIndex: number;
  /** u8 +0x01 bit 0x80 — attach to actor root instead of a bone. */
  attachToRoot: boolean;
  /** u16 +0x02 — collision flags (semantics undecoded; carried for future wiring). */
  collisionFlags: number;
  /** u16 +0x04 — damage-record index (per-borg record table; the 9 global family records
   *  in damageRecords.json are the family fallback the port already models). */
  damageRecordIndex: number;
  /** s16 +0x06 — first active frame of the attack state. */
  activeStart: number;
  /** s16 +0x08 — last active frame (inclusive); -1/-2 sentinels = open/none. */
  activeEnd: number;
  /** f32[3] +0x0c — hitbox offset local to the bone/root. */
  localOffset: readonly [number, number, number];
  /** f32[3] +0x18 — hitbox half extents. */
  halfExtent: readonly [number, number, number];
  /** f32 +0x24 — hitbox radius. */
  radius: number;
}

export interface BorgAttackHitTable {
  /** kind (0..31) -> ordered record indices from the remap block. */
  kinds: Record<string, number[]>;
  /** record index -> decoded record (nonzero records only). */
  records: Record<string, AttackHitRecord>;
}

type AttackHitTablesFile = {
  _meta: Record<string, unknown>;
  borgs: Record<string, BorgAttackHitTable>;
};

const DATA = attackHitTablesData as unknown as AttackHitTablesFile;

/** The borg's full decoded HIT table, or null when no pl####hit.bin exists. */
export function attackHitTableForBorgId(id: string): BorgAttackHitTable | null {
  return DATA.borgs[id.toLowerCase()] ?? null;
}

/** Decoded hitbox records for one HIT kind, in remap order (empty when kind unused). */
export function attackHitRecordsForKind(id: string, kind: number): AttackHitRecord[] {
  const table = attackHitTableForBorgId(id);
  if (!table) return [];
  const entries = table.kinds[String(kind)] ?? [];
  const records: AttackHitRecord[] = [];
  for (const recordId of entries) {
    const record = table.records[String(recordId)];
    if (record) records.push(record);
  }
  return records;
}

/** Aggregate active frame window across a kind's records: [minStart, maxEnd] or null.
 *  Records with activeEnd < activeStart (open/sentinel windows) are skipped. */
export function attackHitActiveWindowForKind(
  id: string,
  kind: number,
): { start: number; end: number } | null {
  let start = Number.POSITIVE_INFINITY;
  let end = Number.NEGATIVE_INFINITY;
  for (const record of attackHitRecordsForKind(id, kind)) {
    if (record.activeEnd < record.activeStart) continue;
    if (record.activeStart < start) start = record.activeStart;
    if (record.activeEnd > end) end = record.activeEnd;
  }
  return Number.isFinite(start) && Number.isFinite(end) ? { start, end } : null;
}

/**
 * DERIVED projectile hit radius for a borg's B-shot: the ROM's generic shot-child init arms
 * HIT kind 0 (literal call sites FUN_80099bb4/FUN_800a2850/FUN_800c1750 — see
 * research/decomp/movement-hit-decode-2026-07-04.md §2), so the kind-0 record's largest
 * extent/radius is the authored projectile hit volume (raw world units). Null when the borg
 * has no active kind-0 record (callers keep the profile fallback).
 */
export function shotHitRadiusForBorgId(id: string): number | null {
  let radius: number | null = null;
  for (const record of attackHitRecordsForKind(id, 0)) {
    const extent = Math.max(...record.halfExtent, record.radius);
    if (extent > 0 && (radius === null || extent > radius)) radius = extent;
  }
  // Plausibility gate: kind 0 is also the literal slot of some big deployable/field children
  // (chunk_0020.c:608, chunk_0052.c:427 — borg-body attacks), whose volumes reach thousands
  // of units. Those are NOT the B-shot projectile; without the per-family variant tables the
  // borg-level kind-0 lookup can't tell them apart, so only projectile-scale volumes are
  // consumed (roster median 20, G RED 20) and oversized records fall back to the profile.
  return radius !== null && radius <= SHOT_HIT_RADIUS_PLAUSIBLE_MAX ? radius : null;
}

/** Upper bound for a plausible projectile hit volume (see shotHitRadiusForBorgId). */
const SHOT_HIT_RADIUS_PLAUSIBLE_MAX = 150;

/** Longest hitbox reach of a kind's records (|offset| + max(extent, radius) on the local Z
 *  forward axis approximation): a scalar the port's distance-based melee check can consume
 *  until full oriented-volume hit testing lands. */
export function attackHitMaxReachForKind(id: string, kind: number): number | null {
  let reach = null;
  for (const record of attackHitRecordsForKind(id, kind)) {
    const [ox, oy, oz] = record.localOffset;
    const offsetLen = Math.hypot(ox, oy, oz);
    const extent = Math.max(...record.halfExtent, record.radius);
    const value = offsetLen + extent;
    if (reach === null || value > reach) reach = value;
  }
  return reach;
}
