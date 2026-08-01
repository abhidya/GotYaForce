#!/usr/bin/env node
// Dumps per-record projectile muzzle offset + speed straight from boot.dol's shot-variant
// spawner tables. Mirrors scripts/gen-challenge-flow-tables.mjs's DOL-reader pattern.
//
// Evidence: each spawner-table row carries the projectile's muzzle offset and spawn speed at
// FIXED byte offsets shared across the row shapes — muzzleOffset f32[3] @ +0x04 and speed
// f32 @ +0x10 (research/decomp/organized/game/systems/80082824_zz_0082824.c shows the sibling
// spawner applying a per-record velocity scale; the per-row muzzle/speed fields are the static
// companions read by the shot-child init at spawn). shotVariantKinds.json already proves, per
// borg, WHICH table+variant row its B-shot fires (borgShotKinds[].table/id, joined to the
// resolved HIT kind by shotKindForBorgId's mode/tie-break). This script re-reads those exact
// rows from boot.dol and decodes the two undumped fields, emitting a borgId -> {muzzleOffset,
// speed} map consumed by addRomProjectile (battle.ts). Rows whose +0x04/+0x10 decode
// implausibly (wrong row shape, e.g. stride-68 tables whose speed lives at a different offset)
// are SKIPPED so callers fall back to the shared MUZZLE_OFFSET constant + findVariantByKind.
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const SHOT_VARIANT_KINDS_PATH = "packages/combat/src/data/shotVariantKinds.json";
const OUT_PATH = "packages/combat/src/data/shotMuzzleSpeed.generated.json";

const SVK = JSON.parse(readFileSync(SHOT_VARIANT_KINDS_PATH, "utf8"));
const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");

const MUZZLE_OFFSET_F32_OFF = 0x04; // f32[3]
const SPEED_F32_OFF = 0x10; // f32

// Plausibility gates: keep only decodes that look like real projectile numbers. Wide enough to
// admit deployable arcs (offsets up to ~400, speeds up to ~600) while rejecting the wrong-row-
// shape garbage (stride-68 tables read 0.0 at +0x10 because their speed field lives elsewhere).
const SPEED_MIN = 1;
const SPEED_MAX = 4000;
const OFFSET_ABS_MAX = 8000;

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

function runtimeToFileOffset(addr) {
  for (let index = 0; index < 18; index += 1) {
    const fileOffset = dol.readUInt32BE(index * 4);
    const runtimeAddress = dol.readUInt32BE(0x48 + index * 4);
    const size = dol.readUInt32BE(0x90 + index * 4);
    if (size > 0 && addr >= runtimeAddress && addr < runtimeAddress + size) {
      return fileOffset + (addr - runtimeAddress);
    }
  }
  return null;
}

function readF32BE(off) {
  return dol.readFloatBE(off);
}

/** Mirrors attackHitData.ts shotKindForBorgId exactly: among remapHasKind entries, pick the
 *  MODE kind, tie-broken by first occurrence in attribution order. */
function resolvedKindForBorg(entries) {
  const usable = entries.filter((e) => e.remapHasKind);
  if (usable.length === 0) return null;
  const counts = new Map();
  for (const e of usable) counts.set(e.kind, (counts.get(e.kind) ?? 0) + 1);
  let bestKind = usable[0].kind;
  let bestCount = 0;
  for (const e of usable) {
    const count = counts.get(e.kind);
    if (count > bestCount) {
      bestCount = count;
      bestKind = e.kind;
    }
  }
  return bestKind;
}

const records = {};
const perStride = {};
const counts = {
  borgsTotal: 0,
  borgsWithResolvedKind: 0,
  borgsDecodedBoth: 0,
  borgsFallback: 0,
  rowsExamined: 0,
  rowsPlausibleBoth: 0,
};

for (const [borgKey, entries] of Object.entries(SVK.borgShotKinds)) {
  counts.borgsTotal += 1;
  if (!Array.isArray(entries) || entries.length === 0) continue;
  const resolvedKind = resolvedKindForBorg(entries);
  if (resolvedKind === null) continue;
  counts.borgsWithResolvedKind += 1;

  // Walk the resolved-kind entries in attribution order; take the first row that decodes.
  let muzzle = null;
  let speed = null;
  let provenance = null;
  for (const entry of entries) {
    if (entry.kind !== resolvedKind) continue;
    const table = SVK.tables[entry.table];
    if (!table) continue;
    counts.rowsExamined += 1;
    const stride = table.stride;
    const rowAddr = Number.parseInt(entry.table, 16) + entry.id * stride;
    const off = runtimeToFileOffset(rowAddr);
    if (off === null) continue;
    // Need bytes through SPEED_F32_OFF + 4.
    if (rowAddr + SPEED_F32_OFF + 4 > rowAddr + stride && stride < SPEED_F32_OFF + 4) continue;
    const mx = readF32BE(off + MUZZLE_OFFSET_F32_OFF + 0);
    const my = readF32BE(off + MUZZLE_OFFSET_F32_OFF + 4);
    const mz = readF32BE(off + MUZZLE_OFFSET_F32_OFF + 8);
    const sp = readF32BE(off + SPEED_F32_OFF);
    const muzzleOk =
      Number.isFinite(mx) && Number.isFinite(my) && Number.isFinite(mz) &&
      Math.abs(mx) <= OFFSET_ABS_MAX && Math.abs(my) <= OFFSET_ABS_MAX && Math.abs(mz) <= OFFSET_ABS_MAX;
    const speedOk = Number.isFinite(sp) && sp >= SPEED_MIN && sp <= SPEED_MAX;
    perStride[stride] = perStride[stride] || { examined: 0, both: 0 };
    perStride[stride].examined += 1;
    // Require BOTH fields plausible: rows whose speed lives at a different offset (e.g. stride-68
    // tables read 0.0 at +0x10) have a DIFFERENT byte layout, so their +0x04 muzzle is equally
    // untrusted — emit nothing and let the caller fall back wholesale.
    if (muzzleOk && speedOk) {
      perStride[stride].both += 1;
      muzzle = [mx, my, mz];
      speed = sp;
      provenance = { table: entry.table, variant: entry.id, stride, fireFn: entry.fireFn, chunkLine: entry.chunkLine };
      counts.rowsPlausibleBoth += 1;
      break;
    }
  }

  if (muzzle !== null && speed !== null) {
    records[borgKey] = {
      kind: resolvedKind,
      muzzleOffset: muzzle.map((v) => +v.toFixed(6)),
      speed: +speed.toFixed(6),
      provenance,
    };
    counts.borgsDecodedBoth += 1;
  } else {
    counts.borgsFallback += 1;
  }
}

const source = {
  bootDolPath: BOOT_DOL_PATH,
  bootDolSha1,
  shotVariantKindsPath: SHOT_VARIANT_KINDS_PATH,
  evidence:
    "Per-row muzzleOffset f32[3]@+0x04 + speed f32@+0x10 read directly from boot.dol spawner " +
    "tables (shotVariantKinds.json tables[].rows). Borg->row attribution reuses borgShotKinds " +
    "(scripts/gen-shot-variant-kinds.mjs) with shotKindForBorgId's mode/tie-break kind resolve. " +
    "Sibling spawner zz_0082824_ (80082824_zz_0082824.c) applies DAT_802d7b30's per-record " +
    "velocity scale at spawn; the static muzzle/speed fields are its row companions.",
  fieldOffsets: { muzzleOffset: hex(MUZZLE_OFFSET_F32_OFF), speed: hex(SPEED_F32_OFF) },
  plausibilityGates: { speedMin: SPEED_MIN, speedMax: SPEED_MAX, offsetAbsMax: OFFSET_ABS_MAX },
  generatedBy: path.basename(import.meta.url),
};

const out = {
  _meta: {
    source,
    counts,
    perStride,
    note: "Keyed by the runtime borg-id guard value (same key space as shotVariantKinds.json " +
      "borgShotKinds; borgIdToShotKindKey in attackHitData.ts maps pl#### <-> this key). " +
      "Absent borg -> caller keeps the shared MUZZLE_OFFSET constant + findVariantByKind fallback.",
  },
  records,
};

writeFileSync(OUT_PATH, JSON.stringify(out, null, 2) + "\n");
console.log(
  `wrote ${OUT_PATH}: ${counts.borgsDecodedBoth} decoded (muzzle+speed), ${counts.borgsFallback} fallback ` +
    `(of ${counts.borgsWithResolvedKind} resolved-kind borgs, ${counts.borgsTotal} total)`,
);
