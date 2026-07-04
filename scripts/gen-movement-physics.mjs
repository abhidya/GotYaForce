#!/usr/bin/env node
// Generate the per-borg movement-physics table from pl####data.bin.
//
// Source (DERIVED, behavior-notes (bc) / research/decomp/data/movement-physics-constants.json):
// each borg's 432-byte pl####data.bin parameter page (loaded to actor+0x4ac via
// DAT_803c4d94[borgType]) carries big-endian floats:
//   +0x2c max horizontal speed clamp        +0x58 knockdown launch h-speed
//   +0x44 ground-accel magnitude (0 = snap) +0x5c knockdown launch accel
//   +0x48 jump / vertical impulse           +0x68 gravity slot A (ground/turn)
//   +0x50 min/turn speed (= guide 'speed')  +0x6c gravity slot B (airborne fall — true gravity)
//                                           +0x70 gravity slot C
// Offsets verified against the (bc) sample dump (pl0615: 12 / 0.8 / 15 / 6 / 30 / -0.05 /
// 0 / -1 / -0.07). Files come loose from afs_data/root or from the borg's .pzz (member
// resolved via the pzz extraction manifest, same convention as bake-all-borg-anims.mjs).
//
// Also reads two u16 status-immunity masks (DERIVED, research/decomp/status-effects-decode-
// 2026-07-04.md §B): +0xa8 statusImmunityA (checked vs a hit record's flagsA) and +0xaa
// statusImmunityB (checked vs flagsB) — static per-borg masks copied to actor+0x59c/+0x59e
// (chunk_0007.c:24-25). A matching bit blocks that status write; the shared bit 0x400 of
// immunityB blocks BOTH aura types (contact-slow and contact-haste).
//
// Also reads the per-borg gameplay camera block (DERIVED, behavior-notes.md §ad /
// chunk_0007.c:171-176): +0xb8/+0xbc copy to actor+0x88c/+0x890 target-height slots;
// +0xc0/+0xc4 copy to actor+0x894/+0x898 follow min/max for camera slot 0;
// +0xc8/+0xcc copy to actor+0x89c/+0x8a0 follow min/max for camera slot 1.
//
// Output: packages/combat/src/data/movementPhysics.json — consumed by
// packages/combat/src/movementData.ts (the scale-reconciled runtime adapter).

import fs from "node:fs";
import path from "node:path";
// dist build (plain-node runner convention, see run-*-tests.mjs): `pnpm -r build` first.
import { unpack as unpackPzz } from "../packages/formats/dist/pzz.js";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const rootDir = path.join(repoRoot, "user-data", region, "afs_data", "root");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const manifestPath = path.join(repoRoot, "research", "asset-inventory", "pzz-member-extraction-manifest.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "movementPhysics.json");

const FIELDS = [
  ["maxHSpeed", 0x2c],
  ["groundAccel", 0x44],
  ["jumpImpulse", 0x48],
  ["minTurnSpeed", 0x50],
  // +0x58..+0x64 are the DASH page block, seeded verbatim by the dash states
  // FUN_80061560 (chunk_0007.c:7231-7238) and FUN_80063230 (chunk_0008.c:1220-1223, 1631-1634):
  // actor+0x44 (h speed) = +0x58, +0x4c (per-frame accel, negative decay) = +0x5c,
  // +0x48 (v speed, air-dash path) = +0x60, +0x568 (duration counter, ticked by the
  // status timescale) = +0x64. Previously mislabeled knockdownLaunch*.
  ["dashHSpeed", 0x58],
  ["dashAccel", 0x5c],
  ["dashVSpeed", 0x60],
  ["dashDurationFrames", 0x64],
  ["gravityGround", 0x68],
  ["gravityFall", 0x6c],
  ["gravityC", 0x70],
  ["cameraHeightSlot0", 0xb8],
  ["cameraHeightSlot1", 0xbc],
  ["cameraFollowMinSlot0", 0xc0],
  ["cameraFollowMaxSlot0", 0xc4],
  ["cameraFollowMinSlot1", 0xc8],
  ["cameraFollowMaxSlot1", 0xcc],
];

// u16 status-immunity masks — read separately from FIELDS (those are f32 read via
// readFloatBE; these are u16 read via readUInt16BE).
const U16_FIELDS = [
  ["statusImmunityA", 0xa8],
  ["statusImmunityB", 0xaa],
];

const borgsFile = JSON.parse(fs.readFileSync(borgsPath, "utf8"));
const roster = Array.isArray(borgsFile) ? borgsFile : borgsFile.borgs;
const ids = [...new Set(roster.map((b) => String(b.id).toLowerCase()))].sort();

let manifestRecords = [];
try {
  const manifest = JSON.parse(fs.readFileSync(manifestPath, "utf8"));
  manifestRecords = manifest.records ?? manifest.members ?? [];
} catch {
  // no manifest: loose files only
}

function readDataBin(borgId) {
  const loose = path.join(rootDir, `${borgId}data.bin`);
  if (fs.existsSync(loose)) return { buf: fs.readFileSync(loose), source: "loose" };
  const pzzPath = path.join(rootDir, `${borgId}.pzz`);
  if (!fs.existsSync(pzzPath)) return null;
  const record = manifestRecords.find(
    (r) =>
      r?.borgId === borgId &&
      String(r?.inferredName ?? "").toLowerCase() === `${borgId}data.bin` &&
      Number.isInteger(r?.memberIndex),
  );
  if (!record) return null;
  const archive = unpackPzz(fs.readFileSync(pzzPath));
  const member = archive.members[record.memberIndex];
  if (!member || member.payload.byteLength === 0) return null;
  return { buf: Buffer.from(member.payload), source: `pzz[${record.memberIndex}]` };
}

const out = {};
const missing = [];
let fromPzz = 0;
for (const id of ids) {
  const data = readDataBin(id);
  if (!data || data.buf.length < 0x74) {
    missing.push(id);
    continue;
  }
  if (data.source !== "loose") fromPzz += 1;
  const entry = {};
  for (const [name, offset] of FIELDS) {
    // Round to 6 decimals: the source floats are exact f32; this only trims JSON noise.
    entry[name] = Math.round(data.buf.readFloatBE(offset) * 1e6) / 1e6;
  }
  // Immunity masks live further into the page (+0xa8/+0xaa); guard separately so a page
  // shorter than 0xac (shouldn't happen at the real 432-byte size, but keep it honest)
  // degrades to 0 (no immunity) instead of throwing.
  for (const [name, offset] of U16_FIELDS) {
    entry[name] = data.buf.length >= offset + 2 ? data.buf.readUInt16BE(offset) : 0;
  }
  out[id] = entry;
}

const payload = {
  _meta: {
    source: "user-data/<region>/afs_data/root/pl####data.bin (+ .pzz members via extraction manifest)",
    generator: "scripts/gen-movement-physics.mjs",
    evidence:
      "research/decomp/behavior-notes.md (bc); research/decomp/data/movement-physics-constants.json perBorgMovementFields_pldata_bin; research/decomp/status-effects-decode-2026-07-04.md §B (statusImmunityA/B)",
    fieldOffsets: Object.fromEntries(
      [...FIELDS, ...U16_FIELDS].map(([name, offset]) => [name, `0x${offset.toString(16)}`]),
    ),
    region,
    borgs: Object.keys(out).length,
    missing,
  },
  borgs: out,
};

fs.writeFileSync(outPath, JSON.stringify(payload, null, 1) + "\n");
console.log(
  `movementPhysics.json: ${Object.keys(out).length}/${ids.length} borgs (${fromPzz} via pzz), missing: ${missing.join(",") || "none"}`,
);
