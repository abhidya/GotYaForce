#!/usr/bin/env node
// Generate compact runtime battle rows from the decompiled borg stat table.
//
// Source evidence:
//   research/decomp/data/borg-hp-stat-rows-802f2988.json
//   zz_0055f90_ @0x80055f90 writes u16[0] to max/current HP.
//   FUN_800562b8 @0x800562b8 writes the same row's weapon slot pairs to +0x774/+0x776.
//
// ATK-020 (level plumbing): each borg now exports its FULL 0x14-row (20-row) table, not just
// the level-0 (default) row, keyed by row offset (0..19) -- the same rows
// borg-hp-stat-rows-802f2988.json already extracted per-variant. The level-BYTE -> row-offset
// indirection (DAT_804339e8) is verified separately by scripts/gen-level-row-offsets.mjs into
// research/decomp/data/level-row-offsets-804339e8.json; this generator does not duplicate that
// table, it just makes every row addressable so sourceBorgStats.ts can select one at read time
// per (ag)'s row arithmetic: row = subIdx + variant*0x14 + DAT_804339e8[level].
// `profiles[id].rows[N]` is that row for offset N; `profiles[id].maxHp`/`weaponSlots` (the
// pre-existing top-level fields) are UNCHANGED and still mirror the level-0 (default) row
// exactly, so all pre-existing consumers keep reading identical values.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const sourcePath = path.join(repoRoot, "research", "decomp", "data", "borg-hp-stat-rows-802f2988.json");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const levelRowOffsetsPath = path.join(repoRoot, "research", "decomp", "data", "level-row-offsets-804339e8.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "borgSourceStats.json");

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function parseId(id) {
  const match = /^pl([0-9a-f]{2})([0-9a-f]{2})$/i.exec(String(id));
  if (!match) return null;
  return { family: match[1].toLowerCase(), variant: match[2].toLowerCase() };
}

function parseCatalogHp(hp) {
  const first = String(hp ?? "").split("/")[0]?.trim();
  const n = Number.parseInt(first ?? "", 10);
  return Number.isFinite(n) ? n : null;
}

const source = JSON.parse(fs.readFileSync(sourcePath, "utf8"));
const borgs = JSON.parse(fs.readFileSync(borgsPath, "utf8")).borgs ?? [];
const baseLevelCode = 0;
const baseRowOffset = source.provenance.levelOffsetTable_DAT_804339e8[baseLevelCode];

if (!Number.isInteger(baseRowOffset)) {
  throw new Error(`invalid base row offset for level code ${baseLevelCode}: ${baseRowOffset}`);
}

// ATK-020: pull in the re-verified DAT_804339e8 table (scripts/gen-level-row-offsets.mjs must
// be run first) and bake it into borgSourceStats.json so sourceBorgStats.ts can do the
// level->row-offset indirection without importing a file outside packages/combat/src's rootDir.
if (!fs.existsSync(levelRowOffsetsPath)) {
  throw new Error(
    `missing ${rel(levelRowOffsetsPath)} -- run scripts/gen-level-row-offsets.mjs first (ATK-020)`,
  );
}
const levelRowOffsetsDoc = JSON.parse(fs.readFileSync(levelRowOffsetsPath, "utf8"));
const levelRowOffsets = levelRowOffsetsDoc.dumpedSigned;
if (levelRowOffsets[baseLevelCode] !== baseRowOffset) {
  throw new Error(
    `level-row-offsets-804339e8.json[${baseLevelCode}]=${levelRowOffsets[baseLevelCode]} does not match ` +
      `borg-hp-stat-rows-802f2988.json's baked levelOffsetTable_DAT_804339e8[${baseLevelCode}]=${baseRowOffset} -- ` +
      "the default-row anchor (G RED HP 200/ammo 5) depends on these agreeing at index 0.",
  );
}

function slotsForRow(row) {
  return [
    { ammoType: row[1], ammoCount: row[2], chargeType: row[3], chargeCount: row[4] },
    { ammoType: row[5], ammoCount: row[6], chargeType: row[7], chargeCount: row[8] },
  ];
}

const profiles = {};
const missingRows = [];
const hpMismatches = [];

for (const borg of borgs) {
  const id = String(borg.id).toLowerCase();
  const parsed = parseId(id);
  const allRows = parsed ? source.tables[parsed.family]?.variants?.[parsed.variant] : null;
  const row = allRows ? allRows[baseRowOffset] : null;
  if (!row) {
    missingRows.push(id);
    continue;
  }

  const maxHp = row[0];
  const catalogHp = parseCatalogHp(borg.hp);
  if (catalogHp !== maxHp) {
    hpMismatches.push({ id, catalogHp, sourceHp: maxHp });
  }

  // rows: every extracted row (offset 0..19) for this borg, so a level-aware caller can select
  // any DAT_804339e8-resolved offset without re-reading the ROM. Index === row offset, matching
  // borg-hp-stat-rows-802f2988.json's own per-variant row array order.
  const rows = allRows.map((r) => ({ maxHp: r[0], weaponSlots: slotsForRow(r) }));

  profiles[id] = {
    maxHp,
    weaponSlots: slotsForRow(row),
    rows,
  };
}

if (missingRows.length > 0 || hpMismatches.length > 0) {
  console.error("source borg stat generation failed verification");
  console.error(JSON.stringify({ missingRows, hpMismatches: hpMismatches.slice(0, 20) }, null, 2));
  process.exit(1);
}

const out = {
  schema: "gotyaforce.borgSourceStats.v1",
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  source: {
    path: rel(sourcePath),
    hpReader: "zz_0055f90_ @0x80055f90",
    weaponSlotReader: "FUN_800562b8 @0x800562b8",
    levelCode: baseLevelCode,
    levelOffset: baseRowOffset,
    rowFields:
      "u16[0]=max HP; slot0 u16[1]/[2]=ammo type/count and u16[3]/[4]=charge pair; " +
      "slot1 u16[5]/[6]=ammo type/count and u16[7]/[8]=charge pair.",
    levelRowIndexing:
      "ATK-020: row = subIdx + variant*0x14 + DAT_804339e8[level] (behavior-notes.md ag). " +
      "The verified DAT_804339e8 table lives in " +
      "research/decomp/data/level-row-offsets-804339e8.json (scripts/gen-level-row-offsets.mjs) " +
      "-- profiles[id].rows[N] below is addressable by that table's resolved offset N. " +
      "Top-level maxHp/weaponSlots stay pinned to levelCode 0 / levelOffset 2 for backward compat.",
  },
  verification: {
    borgsJsonRows: borgs.length,
    runtimeProfiles: Object.keys(profiles).length,
    missingRows,
    hpMismatches,
  },
  // ATK-020: the re-verified DAT_804339e8 level-byte -> row-offset table, baked in from
  // research/decomp/data/level-row-offsets-804339e8.json (scripts/gen-level-row-offsets.mjs,
  // citing behavior-notes.md ak) so sourceStatsForBorgId(id, level) can resolve a row offset
  // without an out-of-rootDir import. See that file for the full provenance/discrepancy record
  // (this script asserts index 0 agrees with it above; the discrepancy at index 15 vs (ak)'s
  // single-pass dump is carried through verbatim in levelRowOffsets.discrepancies).
  levelRowOffsets: {
    table: levelRowOffsets,
    citation: rel(levelRowOffsetsPath),
    discrepancies: levelRowOffsetsDoc.reconciliation.discrepancies,
  },
  profiles,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(out, null, 2)}\n`);

console.log(
  [
    `wrote ${rel(outPath)}`,
    `profiles ${Object.keys(profiles).length}`,
    `levelCode ${baseLevelCode}`,
    `levelOffset ${baseRowOffset}`,
    `rowsPerProfile ${profiles[Object.keys(profiles)[0]]?.rows.length ?? 0}`,
    "hp verified against borgs.json",
  ].join("; "),
);
