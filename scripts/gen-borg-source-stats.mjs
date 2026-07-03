#!/usr/bin/env node
// Generate compact runtime battle rows from the decompiled borg stat table.
//
// Source evidence:
//   research/decomp/data/borg-hp-stat-rows-802f2988.json
//   zz_0055f90_ @0x80055f90 writes u16[0] to max/current HP.
//   FUN_800562b8 @0x800562b8 writes the same row's weapon slot pairs to +0x774/+0x776.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const sourcePath = path.join(repoRoot, "research", "decomp", "data", "borg-hp-stat-rows-802f2988.json");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
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

const profiles = {};
const missingRows = [];
const hpMismatches = [];

for (const borg of borgs) {
  const id = String(borg.id).toLowerCase();
  const parsed = parseId(id);
  const row = parsed ? source.tables[parsed.family]?.variants?.[parsed.variant]?.[baseRowOffset] : null;
  if (!row) {
    missingRows.push(id);
    continue;
  }

  const maxHp = row[0];
  const catalogHp = parseCatalogHp(borg.hp);
  if (catalogHp !== maxHp) {
    hpMismatches.push({ id, catalogHp, sourceHp: maxHp });
  }

  profiles[id] = {
    maxHp,
    weaponSlots: [
      {
        ammoType: row[1],
        ammoCount: row[2],
        chargeType: row[3],
        chargeCount: row[4],
      },
      {
        ammoType: row[5],
        ammoCount: row[6],
        chargeType: row[7],
        chargeCount: row[8],
      },
    ],
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
  },
  verification: {
    borgsJsonRows: borgs.length,
    runtimeProfiles: Object.keys(profiles).length,
    missingRows,
    hpMismatches,
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
    "hp verified against borgs.json",
  ].join("; "),
);
