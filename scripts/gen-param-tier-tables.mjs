#!/usr/bin/env node
// Dump the actor param-tier and status-timescale tables from boot.dol.
//
// Evidence (research/decomp/movement-hit-decode-2026-07-04.md §1, DERIVED):
// - refresh_actor_param_tier_table @0x8006826c reads PTR_DAT_804339e0[page[0xa3]] + tier*0xc:
//   33 rows x 3 f32 [sizeScale, animRateScale, velocityScale]; tier byte actor+0x74a
//   defaults 16 (row 16 = 1,1,1). Tables at 0x802dd5a0 and 0x802dd720.
// - Status timescale (+0x5f4, FUN_8005a378 chunk_0007.c:2817-2898): haste table
//   DAT_802dd58c = 4 f32 (idx +0x70d/+0x70f), slow table DAT_802dd57c = 4 f32
//   (idx +0x70c/+0x70e); burst/fusion flag x1.5 (FLOAT_804373d8); freeze x0.03
//   (FLOAT_804373dc) while +0x71c > 0.
//
// Output: packages/combat/src/data/paramTierTables.json (consumed by timescale.ts).

import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");
const dol = fs.readFileSync(path.join(repoRoot, "user-data", "GG4E", "disc", "sys", "boot.dol"));

const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x00 + i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
function fileOffset(address) {
  for (let i = 0; i < 18; i += 1) {
    if (sectionSizes[i] > 0 && address >= sectionAddresses[i] && address < sectionAddresses[i] + sectionSizes[i]) {
      return sectionOffsets[i] + (address - sectionAddresses[i]);
    }
  }
  throw new Error(`address 0x${address.toString(16)} not in any DOL section`);
}

const round = (v) => Math.round(v * 1e6) / 1e6;

function dumpTierTable(address, rows) {
  const off = fileOffset(address);
  return Array.from({ length: rows }, (_, tier) => {
    const base = off + tier * 0xc;
    return {
      tier,
      sizeScale: round(dol.readFloatBE(base)),
      animRateScale: round(dol.readFloatBE(base + 4)),
      velocityScale: round(dol.readFloatBE(base + 8)),
    };
  });
}

function dumpFloats(address, count) {
  const off = fileOffset(address);
  return Array.from({ length: count }, (_, i) => round(dol.readFloatBE(off + i * 4)));
}

const payload = {
  _meta: {
    source: "user-data/GG4E/disc/sys/boot.dol",
    generator: "scripts/gen-param-tier-tables.mjs",
    evidence: "research/decomp/movement-hit-decode-2026-07-04.md §1 (refresh_actor_param_tier_table @0x8006826c; FUN_8005a378)",
    tierDefault: 16,
    rowLayout: "[sizeScale, animRateScale, velocityScale] per tier, stride 0xc",
  },
  tierTables: {
    "0x802dd5a0": dumpTierTable(0x802dd5a0, 33),
    "0x802dd720": dumpTierTable(0x802dd720, 33),
  },
  statusTimescale: {
    // DAT_802dd57c: slow multipliers (idx actor+0x70c/+0x70e; hit-inflicted).
    slow_802dd57c: dumpFloats(0x802dd57c, 4),
    // DAT_802dd58c: haste multipliers (idx actor+0x70d/+0x70f).
    haste_802dd58c: dumpFloats(0x802dd58c, 4),
    burstFusionMultiplier_804373d8: dumpFloats(0x804373d8, 1)[0],
    freezeMultiplier_804373dc: dumpFloats(0x804373dc, 1)[0],
    base_804373c8: dumpFloats(0x804373c8, 1)[0],
  },
};

const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "paramTierTables.json");
fs.writeFileSync(outPath, JSON.stringify(payload, null, 1) + "\n");
const t = payload.tierTables["0x802dd5a0"];
console.log(
  `paramTierTables.json written. Table 0x802dd5a0 sanity: tier16=${JSON.stringify(t[16])} tier20 vel=${t[20].velocityScale}; ` +
    `haste=${payload.statusTimescale.haste_802dd58c.join(",")} slow=${payload.statusTimescale.slow_802dd57c.join(",")} ` +
    `burst=${payload.statusTimescale.burstFusionMultiplier_804373d8} freeze=${payload.statusTimescale.freezeMultiplier_804373dc}`,
);
