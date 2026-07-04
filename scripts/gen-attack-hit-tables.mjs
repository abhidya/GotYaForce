#!/usr/bin/env node
// Generate the per-borg attack HIT tables from pl####hit.bin.
//
// Source (DERIVED — hit-bin agent census + audit-move-unblockers.mjs decode, verified against
// research/asset-inventory/hit-bin-inventory.json):
//   +0xa20: attack-remap block — 32 kind slots × 4 entry bytes (0xff terminates a slot);
//           `zz_008ac80_(actor, kind)` selects slot <kind>, each entry byte indexes a record.
//   +0xaa0: 64 × 0x50-stride attack hitbox records:
//     +0x00 u8 shape kind        +0x06 s16 active start frame
//     +0x01 u8 bone (|0x80=root) +0x08 s16 active end frame
//     +0x02 u16 collision flags  +0x0c f32[3] local offset
//     +0x04 u16 damage-record ix +0x18 f32[3] half extent
//                                +0x24 f32 radius
// Output: packages/combat/src/data/attackHitTables.json — consumed by
// packages/combat/src/attackHitData.ts (runtime literal-kind wiring).

import fs from "node:fs";
import path from "node:path";
import { unpack as unpackPzz } from "../packages/formats/dist/pzz.js";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const rootDir = path.join(repoRoot, "user-data", region, "afs_data", "root");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const manifestPath = path.join(repoRoot, "research", "asset-inventory", "pzz-member-extraction-manifest.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "attackHitTables.json");

const REMAP_OFFSET = 0xa20;
const REMAP_SLOTS = 32;
const REMAP_STRIDE = 4;
const RECORD_OFFSET = 0xaa0;
const RECORD_COUNT = 64;
const RECORD_SIZE = 0x50;

const borgsFile = JSON.parse(fs.readFileSync(borgsPath, "utf8"));
const roster = Array.isArray(borgsFile) ? borgsFile : borgsFile.borgs;
const ids = [...new Set(roster.map((b) => String(b.id).toLowerCase()))].sort();

let manifestRecords = [];
try {
  const manifest = JSON.parse(fs.readFileSync(manifestPath, "utf8"));
  manifestRecords = manifest.records ?? manifest.members ?? [];
} catch {
  // loose files only
}

function readHitBin(borgId) {
  const loose = path.join(rootDir, `${borgId}hit.bin`);
  if (fs.existsSync(loose)) return fs.readFileSync(loose);
  const pzzPath = path.join(rootDir, `${borgId}.pzz`);
  if (!fs.existsSync(pzzPath)) return null;
  const record = manifestRecords.find(
    (r) =>
      r?.borgId === borgId &&
      String(r?.inferredName ?? "").toLowerCase() === `${borgId}hit.bin` &&
      Number.isInteger(r?.memberIndex),
  );
  if (!record) return null;
  const archive = unpackPzz(fs.readFileSync(pzzPath));
  const member = archive.members[record.memberIndex];
  if (!member || member.payload.byteLength === 0) return null;
  return Buffer.from(member.payload);
}

const round2 = (v) => Math.round(v * 100) / 100;

function parseRecord(buffer, index) {
  const offset = RECORD_OFFSET + index * RECORD_SIZE;
  const raw = buffer.subarray(offset, offset + RECORD_SIZE);
  if (!raw.some((byte) => byte !== 0)) return null;
  const bone = buffer.readUInt8(offset + 0x01);
  return {
    shapeKind: buffer.readUInt8(offset + 0x00),
    boneIndex: bone & 0x7f,
    attachToRoot: (bone & 0x80) !== 0,
    collisionFlags: buffer.readUInt16BE(offset + 0x02),
    damageRecordIndex: buffer.readUInt16BE(offset + 0x04),
    activeStart: buffer.readInt16BE(offset + 0x06),
    activeEnd: buffer.readInt16BE(offset + 0x08),
    localOffset: [0x0c, 0x10, 0x14].map((o) => round2(buffer.readFloatBE(offset + o))),
    halfExtent: [0x18, 0x1c, 0x20].map((o) => round2(buffer.readFloatBE(offset + o))),
    radius: round2(buffer.readFloatBE(offset + 0x24)),
  };
}

const out = {};
const missing = [];
for (const id of ids) {
  const buffer = readHitBin(id);
  if (!buffer || buffer.length < RECORD_OFFSET + RECORD_COUNT * RECORD_SIZE) {
    missing.push(id);
    continue;
  }
  const kinds = {};
  const usedRecordIds = new Set();
  for (let slot = 0; slot < REMAP_SLOTS; slot += 1) {
    const entries = [];
    for (let position = 0; position < REMAP_STRIDE; position += 1) {
      const value = buffer.readUInt8(REMAP_OFFSET + slot * REMAP_STRIDE + position);
      if (value === 0xff) break;
      entries.push(value);
      usedRecordIds.add(value);
    }
    if (entries.length > 0) kinds[slot] = entries;
  }
  const records = {};
  for (const recordId of [...usedRecordIds].sort((a, b) => a - b)) {
    const record = parseRecord(buffer, recordId);
    if (record) records[recordId] = record;
  }
  out[id] = { kinds, records };
}

const totals = Object.values(out).reduce(
  (acc, entry) => {
    acc.kinds += Object.keys(entry.kinds).length;
    acc.entries += Object.values(entry.kinds).reduce((sum, list) => sum + list.length, 0);
    acc.records += Object.keys(entry.records).length;
    return acc;
  },
  { kinds: 0, entries: 0, records: 0 },
);

const payload = {
  _meta: {
    source: "user-data/<region>/afs_data/root/pl####hit.bin (+ .pzz members via extraction manifest)",
    generator: "scripts/gen-attack-hit-tables.mjs",
    evidence:
      "audit-move-unblockers.mjs record layout; research/asset-inventory/hit-bin-inventory.json; zz_008ac80_(actor, kind) selects remap slot <kind>",
    layout: {
      remap: "0xa20: 32 kind slots x 4 entry bytes, 0xff-terminated",
      records: "0xaa0: 64 x 0x50 records (shape/bone/flags/damageRecordIndex/frames/offset/extent/radius)",
    },
    region,
    borgs: Object.keys(out).length,
    totalKinds: totals.kinds,
    totalRemapEntries: totals.entries,
    totalRecords: totals.records,
    missing,
  },
  borgs: out,
};

fs.writeFileSync(outPath, JSON.stringify(payload) + "\n");
console.log(
  `attackHitTables.json: ${Object.keys(out).length}/${ids.length} borgs, ${totals.entries} remap entries, ${totals.records} records; missing: ${missing.join(",") || "none"}`,
);
