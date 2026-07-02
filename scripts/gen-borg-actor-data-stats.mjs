#!/usr/bin/env node
// Generate the combat-stat subset decoded from original pl####data.bin actor data.
//
// The byte offsets below were found by exact cross-check against every borg that
// has both a 432-byte actor-data record and packages/assets/data/borgs.json metadata.
// They are not inferred from names or ranges: each offset matched all metadata rows
// in its verifiable domain (see research/format-specs/pl-data-bin-layout.md).

import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = "GG4E";
// user-data is untracked; fall back to the main checkout when running from a worktree.
const assetRootCandidates = [
  path.join(repoRoot, "user-data", region, "afs_data", "root"),
  path.join("D:\\GotYaForce", "user-data", region, "afs_data", "root"),
];
const assetRoot = assetRootCandidates.find((p) => fs.existsSync(p)) ?? assetRootCandidates[0];
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "actorDataStats.json");

const RECORD_SIZE = 432;
const OFFSETS = {
  typeCode: 0x1a0,
  airJump: 0x1a3,
  defense: 0x1a4,
  shot: 0x1a5,
  attack: 0x1a6,
  speed: 0x1a7,
};

// Byte 0x1a0 is a borg-type enum. Proven bijective against borgs.json "type" (case
// normalized) across all 190 borgs that have both an actor-data record and metadata
// (see research/format-specs/pl-data-bin-layout.md).
const TYPE_CODES = {
  "long range type": 0,
  "short range type": 1,
  "speed type": 2,
  "almighty type": 3,
  "support type": 4,
};

// Byte 0x1a3 is the air-jump count. Cross-checkable domains:
//   "Air jump level N" -> byte === N (all 78 such borgs)
//   "Boost jump"       -> byte === 0 (all 97 such borgs)
// "N/A" borgs are OBSERVED as 0xff (14) or 0 (pl0f00 only) but have no numeric
// metadata to check against, so they are excluded from verification.
function expectedAirJump(jump) {
  const j = String(jump ?? "").trim().toLowerCase();
  const m = /^air jump level\s*(\d+)$/.exec(j);
  if (m) return Number(m[1]);
  if (j === "boost jump") return 0;
  return null; // unverifiable domain (N/A etc.)
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

// Source files are relativized against the checkout that actually holds user-data, so
// the generated JSON is identical whether generated from the main checkout or a worktree.
const sourceRoot = path.resolve(assetRoot, "..", "..", "..", "..");
function relSource(file) {
  return path.relative(sourceRoot, file).replaceAll(path.sep, "/");
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
    typeCode: buffer.readUInt8(OFFSETS.typeCode),
    airJump: buffer.readUInt8(OFFSETS.airJump),
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
const exactMatches = { typeCode: 0, airJump: 0, defense: 0, shot: 0, attack: 0, speed: 0 };
let airJumpUnverifiable = 0;

for (const name of files) {
  const id = name.slice(0, 6).toLowerCase();
  const abs = path.join(assetRoot, name);
  const buffer = fs.readFileSync(abs);
  if (buffer.length !== RECORD_SIZE) continue;

  const stats = byteStats(buffer);
  const meta = metadataById.get(id);
  if (meta) {
    matchedMetadataRows += 1;
    for (const field of ["defense", "shot", "attack", "speed"]) {
      if (stats[field] !== meta[field]) {
        mismatches.push({
          id,
          field,
          offset: hex(OFFSETS[field]),
          actorData: stats[field],
          borgsJson: meta[field],
        });
      } else {
        exactMatches[field] += 1;
      }
    }

    // type enum at 0x1a0: every metadata type string must map, and the byte must match.
    const typeKey = String(meta.type ?? "").trim().toLowerCase();
    const expectedType = TYPE_CODES[typeKey];
    if (expectedType === undefined || stats.typeCode !== expectedType) {
      mismatches.push({
        id,
        field: "typeCode",
        offset: hex(OFFSETS.typeCode),
        actorData: stats.typeCode,
        borgsJson: meta.type,
        expected: expectedType,
      });
    } else {
      exactMatches.typeCode += 1;
    }

    // air-jump count at 0x1a3: checked on the "air jump level N" / "boost jump" domains.
    const expectedJump = expectedAirJump(meta.jump);
    if (expectedJump === null) {
      airJumpUnverifiable += 1;
    } else if (stats.airJump !== expectedJump) {
      mismatches.push({
        id,
        field: "airJump",
        offset: hex(OFFSETS.airJump),
        actorData: stats.airJump,
        borgsJson: meta.jump,
        expected: expectedJump,
      });
    } else {
      exactMatches.airJump += 1;
    }
  }

  profiles[id] = {
    ...stats,
    sourcePath: relSource(abs),
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
    root: relSource(assetRoot),
    pattern: "pl####data.bin",
    recordSize: RECORD_SIZE,
    offsets: Object.fromEntries(Object.entries(OFFSETS).map(([field, offset]) => [field, hex(offset)])),
    fields:
      "defense/shot/attack/speed are unsigned bytes at 0x1a4..0x1a7. typeCode (0x1a0) is the borg-type enum " +
      "(0=long range, 1=short range, 2=speed, 3=almighty, 4=support). airJump (0x1a3) is the raw air-jump " +
      "count byte: N for 'Air jump level N' borgs, 0 for 'Boost jump' borgs, 0xff observed for most 'N/A' flyers.",
    typeCodes: TYPE_CODES,
  },
  verification: {
    borgsJsonRows: borgs.length,
    actorDataFiles: files.length,
    runtimeProfiles: Object.keys(profiles).length,
    matchedMetadataRows,
    exactMatches,
    airJumpUnverifiable,
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
    `exact ${Object.entries(exactMatches)
      .map(([k, v]) => `${k}=${v}`)
      .join(" ")}`,
    `airJump unverifiable ${airJumpUnverifiable}`,
  ].join("; "),
);
