#!/usr/bin/env node
// Dumps the GG4E knockback MAGNITUDE strength-indexed tables straight from boot.dol,
// mirroring the DOL-reader pattern in scripts/gen-challenge-flow-tables.mjs.
//
// Evidence: zz_005ec20_ @0x8005ec20 reads horizontal launch speed from
//   `*(float *)(&DAT_802dd8a0 + strength * 4)` (chunk_0007.c:5568); FUN_8005ed38 @0x8005ed38
//   reads velocity magnitude from `*(float *)(&DAT_802d3664 + strength * 4)` (chunk_0007.c:5630),
//   where `strength` = actor+0x702 clamped 0..15 (the hit record's +0x0d severity byte copied
//   to the victim at chunk_0003.c:8047). These are the previously-missing knockback MAGNITUDE
//   source — the DIRECTION (zz_00300bc_) only writes yaw/pitch; magnitude comes from here.
//
// Output: packages/combat/src/data/knockbackStrength.json (consumed verbatim by
// packages/combat/src/damage/sourceKnockback.ts).
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const OUT_PATH = "packages/combat/src/data/knockbackStrength.json";

const ADDRS = {
  horizontalLaunch: 0x802dd8a0, // DAT_802dd8a0 — 16 floats, zz_005ec20_ ground-reaction h-speed
  velocityMagnitude: 0x802d3664, // DAT_802d3664 — 16 floats, FUN_8005ed38 launch velocity
};

const ENTRY_COUNT = 16;

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

function runtimeToFileOffset(dol, addr) {
  for (let index = 0; index < 18; index += 1) {
    const fileOffset = dol.readUInt32BE(index * 4);
    const runtimeAddress = dol.readUInt32BE(0x48 + index * 4);
    const size = dol.readUInt32BE(0x90 + index * 4);
    if (size > 0 && addr >= runtimeAddress && addr < runtimeAddress + size) {
      return fileOffset + (addr - runtimeAddress);
    }
  }
  throw new Error(`DOL address ${hex(addr)} is outside mapped sections`);
}

function readFloatAt(dol, addr) {
  const off = runtimeToFileOffset(dol, addr);
  return dol.readFloatBE(off);
}

function decodeFloatTable(dol, address, count) {
  return Array.from({ length: count }, (_, i) => readFloatAt(dol, address + i * 4));
}

const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");

const horizontalLaunch = decodeFloatTable(dol, ADDRS.horizontalLaunch, ENTRY_COUNT);
const velocityMagnitude = decodeFloatTable(dol, ADDRS.velocityMagnitude, ENTRY_COUNT);

const out = {
  provenance: {
    bootDolPath: BOOT_DOL_PATH,
    bootDolSha1,
    generatedBy: path.basename(import.meta.url),
    evidence:
      "zz_005ec20_ @0x8005ec20 reads *(float*)(&DAT_802dd8a0 + strength*4) (chunk_0007.c:5568); " +
      "FUN_8005ed38 @0x8005ed38 reads *(float*)(&DAT_802d3664 + strength*4) (chunk_0007.c:5630); " +
      "strength = actor+0x702 (the hit record +0x0d severity byte, clamped 0..15).",
    addresses: {
      horizontalLaunch: hex(ADDRS.horizontalLaunch),
      velocityMagnitude: hex(ADDRS.velocityMagnitude),
    },
    entryCount: ENTRY_COUNT,
    expectedForm: {
      horizontalLaunch: "strength * 7.0  (0,7,14,...,105)",
      velocityMagnitude: "(strength + 1) * 8.0  (8,16,...,128)",
    },
  },
  horizontalLaunch,
  velocityMagnitude,
};

writeFileSync(OUT_PATH, JSON.stringify(out, null, 2) + "\n");
console.log(`wrote ${OUT_PATH}`);
console.log(`  DAT_802dd8a0 = ${JSON.stringify(horizontalLaunch)}`);
console.log(`  DAT_802d3664 = ${JSON.stringify(velocityMagnitude)}`);
