#!/usr/bin/env node
// Extract the Borg GET / Gotcha-Box drop table (DAT_8035b2dc, boot.dol) into
// packages/missions/src/data/borgGetDropTable.json.
//
// DECODED (research/decomp/items-evidence-inventory-2026-07-05.md §2d): the post-battle
// drop roll zz_0182228_ @0x80182228 (chunk_0045.c:4766-4817) scans rows of 8 big-endian
// s16 (16 bytes) starting at DAT_8035b2dc, terminated by a negative first short:
//
//   [0]     borgId          (12-bit id, matches the pool entry's high field)
//   [1]     partsKind       1 = whole-unit drop; 2..5 = split into N collectible parts;
//                           a row-less borg (no entry at all) never drops.
//   [2..7]  threshold[v]    GET-point threshold per color variant v = 0..5
//                           (normal, alt color, gold, silver, crystal, black);
//                           -1 = that variant can never drop this borg.
//
// Section-mapping pattern follows scripts/scan-damage-table-bindings.mjs:10-18 (18 DOL
// section header triples: file offsets @0x00, VAs @0x48, sizes @0x90).
//
// killCredits (chunk_0003.c:8061-8064): killing pl0503 (CYBER DEATH DRAGON, a fusion with
// no GET row of its own) instead credits its two fusion components, pl0505 (DEATH HEAD)
// and pl0506 (CYBER DRAGON).
//
// pointsPerKill (chunk_0045.c:4754-4757, zz_018214c_): +(rng8() & 0xF) + 1 = random 1..16
// points per registered kill, via the global 8-bit RNG zz_00055fc_ @0x800055fc.
//
// ASSERTS byte-exact 197/197 against research/symbols/eu_borgs_GET_values.csv and hard-fails
// otherwise (columns Normal/Another Color/Gold/Silver/Crystal/Black = variant 0..5).

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const DOL_PATH = path.join(ROOT, "user-data/GG4E/disc/sys/boot.dol");
const CSV_PATH = path.join(ROOT, "research/symbols/eu_borgs_GET_values.csv");
const OUT_PATH = path.join(ROOT, "packages/missions/src/data/borgGetDropTable.json");

const TABLE_VA = 0x8035b2dc;
const ROW_BYTES = 16; // 8 x s16 BE
const VARIANT_NAMES = ["normal", "altColor", "gold", "silver", "crystal", "black"];

function fail(message) {
  console.error(`extract-borg-get-drop-table: FAIL — ${message}`);
  process.exit(1);
}

function buildSectionMap(dol) {
  const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
  const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
  const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
  return function offsetFor(addr) {
    for (let i = 0; i < 18; i++) {
      if (sectionSizes[i] > 0 && addr >= sectionAddresses[i] && addr < sectionAddresses[i] + sectionSizes[i]) {
        return sectionOffsets[i] + (addr - sectionAddresses[i]);
      }
    }
    return null;
  };
}

function borgIdHex(id) {
  return `pl${id.toString(16).padStart(4, "0")}`;
}

function extractRows(dol, offsetFor) {
  const off0 = offsetFor(TABLE_VA);
  if (off0 === null) fail(`table VA 0x${TABLE_VA.toString(16)} is not mapped by any DOL section`);

  const rows = [];
  let off = off0;
  for (let i = 0; i < 4096; i++) {
    const first = dol.readInt16BE(off);
    if (first < 0) break; // terminator row
    const shorts = Array.from({ length: 8 }, (_, k) => dol.readInt16BE(off + k * 2));
    const [borgId, partsKind, ...thresholds] = shorts;
    rows.push({
      borgId: borgIdHex(borgId),
      partsKind,
      thresholds: Object.fromEntries(VARIANT_NAMES.map((name, v) => [name, thresholds[v]])),
    });
    off += ROW_BYTES;
  }
  return { rows, fileOffset: off0 };
}

function loadCsvRows() {
  const text = fs.readFileSync(CSV_PATH, "utf8");
  const lines = text.split(/\r?\n/).filter((l) => l.length > 0);
  const header = lines[0].split(",");
  // filename,borgname,Normal,Another Color,Gold,Silver,Crystal,Black
  const expectedHeader = ["filename", "borgname", "Normal", "Another Color", "Gold", "Silver", "Crystal", "Black"];
  for (let i = 0; i < expectedHeader.length; i++) {
    if (header[i] !== expectedHeader[i]) {
      fail(`CSV header column ${i} is "${header[i]}", expected "${expectedHeader[i]}"`);
    }
  }
  return lines.slice(1).map((line) => {
    const cols = line.split(",");
    return {
      borgId: cols[0],
      name: cols[1],
      thresholds: {
        normal: Number(cols[2]),
        altColor: Number(cols[3]),
        gold: Number(cols[4]),
        silver: Number(cols[5]),
        crystal: Number(cols[6]),
        black: Number(cols[7]),
      },
    };
  });
}

function assertCrossValidation(rows) {
  const csvRows = loadCsvRows();
  if (csvRows.length !== 197) fail(`CSV row count is ${csvRows.length}, expected 197`);
  if (rows.length !== 197) fail(`extracted row count is ${rows.length}, expected 197`);

  const byId = new Map(rows.map((r) => [r.borgId, r]));
  let matched = 0;
  const mismatches = [];
  for (const csvRow of csvRows) {
    const extracted = byId.get(csvRow.borgId);
    if (!extracted) {
      mismatches.push(`${csvRow.borgId} (${csvRow.name}): missing from extracted table`);
      continue;
    }
    let rowOk = true;
    for (const name of VARIANT_NAMES) {
      if (extracted.thresholds[name] !== csvRow.thresholds[name]) {
        rowOk = false;
        mismatches.push(
          `${csvRow.borgId} (${csvRow.name}): ${name} extracted=${extracted.thresholds[name]} csv=${csvRow.thresholds[name]}`,
        );
      }
    }
    if (rowOk) matched += 1;
  }

  if (matched !== 197 || mismatches.length > 0) {
    fail(
      `cross-validation against eu_borgs_GET_values.csv: ${matched}/197 rows matched byte-exact\n` +
        mismatches.slice(0, 20).join("\n"),
    );
  }
  console.log(`extract-borg-get-drop-table: cross-validation PASS — 197/197 rows byte-exact vs ${path.relative(ROOT, CSV_PATH)}`);
}

function main() {
  if (!fs.existsSync(DOL_PATH)) fail(`boot.dol not found at ${DOL_PATH}`);
  const dol = fs.readFileSync(DOL_PATH);
  const offsetFor = buildSectionMap(dol);
  const { rows, fileOffset } = extractRows(dol, offsetFor);

  assertCrossValidation(rows);

  const partsKindCounts = {};
  for (const row of rows) partsKindCounts[row.partsKind] = (partsKindCounts[row.partsKind] ?? 0) + 1;

  const output = {
    _meta: {
      source: `boot.dol@0x${TABLE_VA.toString(16)}`,
      dolPath: "user-data/GG4E/disc/sys/boot.dol",
      dolFileOffset: `0x${fileOffset.toString(16)}`,
      sectionMappingPattern: "scripts/scan-damage-table-bindings.mjs:10-18",
      rowLayout: "8 x big-endian s16 (16 bytes): [borgId, partsKind, threshold[0..5]]",
      terminator: "negative first short",
      rowCount: rows.length,
      partsKindCounts,
      variantOrder: VARIANT_NAMES,
      variantOrderSource:
        "research/symbols/eu_borgs_GET_values.csv header (Normal, Another Color, Gold, Silver, Crystal, Black)",
      crossValidation: {
        dataset: "research/symbols/eu_borgs_GET_values.csv",
        result: "197/197 byte-exact",
      },
      partsKindSemantics:
        "1 = whole-unit drop ('UNIT GET'); 2..5 = split into N collectible parts ('PARTS GET', random part 1..N); a borg with no row never drops (never-drop borgs: pl0503/0507/050f/0513/0615/0602/060a/060c/060e/0629/062a).",
      thresholdSemantics: "threshold -1 means that color variant can never drop for this borg.",
      killCredits: {
        note:
          "chunk_0003.c:8061-8064 — killing pl0503 (CYBER DEATH DRAGON, a fusion with no GET row) instead " +
          "registers a kill for its two fusion components.",
        pl0503: ["pl0505", "pl0506"],
      },
      pointsPerKill: {
        min: 1,
        max: 16,
        note: "chunk_0045.c:4754-4757 (zz_018214c_): +(rng8() & 0xF) + 1 via the global 8-bit RNG zz_00055fc_.",
      },
      poolCap: 1536,
      pointsCap: 65535,
      evidenceDoc: "research/decomp/items-evidence-inventory-2026-07-05.md",
    },
    rows,
  };

  fs.mkdirSync(path.dirname(OUT_PATH), { recursive: true });
  fs.writeFileSync(OUT_PATH, JSON.stringify(output, null, 2) + "\n");
  console.log(`extract-borg-get-drop-table: wrote ${rows.length} rows -> ${path.relative(ROOT, OUT_PATH)}`);
}

main();
