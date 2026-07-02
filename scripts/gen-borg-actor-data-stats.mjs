#!/usr/bin/env node
// Generate the combat-stat subset decoded from original pl####data.bin actor data.
//
// The four byte offsets below were found by exact cross-check against every borg that
// has both a 432-byte actor-data record and packages/assets/data/borgs.json metadata.
// They are not inferred from names or ranges: each offset matched all metadata rows.

import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = "GG4E";
const assetRoot = path.join(repoRoot, "user-data", region, "afs_data", "root");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "actorDataStats.json");

const RECORD_SIZE = 432;
const OFFSETS = {
  defense: 0x1a4,
  shot: 0x1a5,
  attack: 0x1a6,
  speed: 0x1a7,
};

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

function hex(value) {
  return `0x${value.toString(16).padStart(3, "0")}`;
}

function readBorgs() {
  const parsed = JSON.parse(fs.readFileSync(borgsPath, "utf8"));
  return parsed.borgs ?? [];
}

function byteStats(buffer) {
  return {
    defense: buffer.readUInt8(OFFSETS.defense),
    shot: buffer.readUInt8(OFFSETS.shot),
    attack: buffer.readUInt8(OFFSETS.attack),
    speed: buffer.readUInt8(OFFSETS.speed),
  };
}

const borgs = readBorgs();
const metadataById = new Map(borgs.map((borg) => [String(borg.id).toLowerCase(), borg]));
const files = fs
  .readdirSync(assetRoot)
  .filter((name) => /^pl[0-9a-f]{4}data\.bin$/i.test(name))
  .sort();

const profiles = {};
const mismatches = [];
let matchedMetadataRows = 0;

for (const name of files) {
  const id = name.slice(0, 6).toLowerCase();
  const abs = path.join(assetRoot, name);
  const buffer = fs.readFileSync(abs);
  if (buffer.length !== RECORD_SIZE) continue;

  const stats = byteStats(buffer);
  const meta = metadataById.get(id);
  if (meta) {
    matchedMetadataRows += 1;
    for (const field of Object.keys(OFFSETS)) {
      if (stats[field] !== meta[field]) {
        mismatches.push({
          id,
          field,
          offset: hex(OFFSETS[field]),
          actorData: stats[field],
          borgsJson: meta[field],
        });
      }
    }
  }

  profiles[id] = {
    ...stats,
    sourcePath: rel(abs),
    sourceSha1: sha1(buffer),
  };
}

if (mismatches.length > 0) {
  console.error("actor data stat offsets are not exact; refusing to generate runtime data");
  console.error(JSON.stringify(mismatches.slice(0, 20), null, 2));
  process.exit(1);
}

const out = {
  schema: "gotyaforce.actorDataCombatStats.v1",
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  source: {
    region,
    root: rel(assetRoot),
    pattern: "pl####data.bin",
    recordSize: RECORD_SIZE,
    offsets: Object.fromEntries(Object.entries(OFFSETS).map(([field, offset]) => [field, hex(offset)])),
    fields: "defense/shot/attack/speed are unsigned bytes at offsets 0x1a4..0x1a7.",
  },
  verification: {
    borgsJsonRows: borgs.length,
    actorDataFiles: files.length,
    runtimeProfiles: Object.keys(profiles).length,
    matchedMetadataRows,
    exactMatches: {
      defense: matchedMetadataRows,
      shot: matchedMetadataRows,
      attack: matchedMetadataRows,
      speed: matchedMetadataRows,
    },
    mismatches,
  },
  profiles,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(out, null, 2)}\n`);

console.log(
  [
    `wrote ${rel(outPath)}`,
    `profiles ${Object.keys(profiles).length}`,
    `metadata rows ${matchedMetadataRows}`,
    `exact defense/shot/attack/speed ${matchedMetadataRows}`,
  ].join("; "),
);
