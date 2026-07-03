#!/usr/bin/env node
// Extract/re-verify DAT_804339e8 (level-byte -> stat-row offset table) from boot.dol.
//
// Source evidence:
//   behavior-notes.md (ag): row = subIdx(+0x3ee) + variant(+0x3e9)*0x14 + DAT_804339e8[level(+0x3ec)],
//     stride 0x12, read by zz_0055f90_ @0x80055f90 (chunk_0006.c:8167-8232). Cross-verified live:
//     G RED (pl0615) DAT_804339e8[0]=2 -> HP 200 / ammo 5 (captured HUD values).
//   behavior-notes.md (ak): "Borg level system" section records a SINGLE-PASS 32-byte dump of
//     DAT_804339e8: [2,2,8,6,0,4,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1]. That
//     section explicitly flags this dump as single-pass and asks for re-verification with a
//     dol.py-style read before persisting -- this script is that re-verification.
//   research/decomp/data/borg-hp-stat-rows-802f2988.json (extractor: scripts/extract-borg-stat-tables.py)
//     ALSO embeds a levelOffsetTable_DAT_804339e8, but only read 16 bytes (`>16b`), giving
//     [2,2,8,6,0,4,0,0,0,0,0,1,0,1,0,1] -- the last entry (index 15) disagrees with (ak)'s 32-byte
//     dump (which has 0 at index 15, not 1). That extractor never claimed to cover the full 32-byte
//     table; this script reads the full 32 bytes and reconciles both readings explicitly below.
//
// Follows the read pattern of scripts/gen_fusion_pairs.py (DOL section table parsed directly,
// addr_to_off()-equivalent + big-endian struct reads), translated to Node so no python dependency
// is required for this ticket's zone.
//
// Run: tools/node/node.exe scripts/gen-level-row-offsets.mjs

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const DOL = path.join(repoRoot, "user-data", "GG4E", "disc", "sys", "boot.dol");
const OUT = path.join(repoRoot, "research", "decomp", "data", "level-row-offsets-804339e8.json");

const LEVEL_TABLE_ADDR = 0x804339e8;
const LEVEL_TABLE_COUNT = 32; // (ak)'s single-pass dump length; re-verify, do not assume.

// --- DOL section table parsing (mirrors scripts/gen_fusion_pairs.py) ----------------------

const data = fs.readFileSync(DOL);

function readU32BE(buf, off) {
  return buf.readUInt32BE(off);
}

const NUM_SECTIONS = 18;
const offs = [];
const addrs = [];
const sizes = [];
for (let i = 0; i < NUM_SECTIONS; i++) offs.push(readU32BE(data, i * 4));
for (let i = 0; i < NUM_SECTIONS; i++) addrs.push(readU32BE(data, 72 + i * 4));
for (let i = 0; i < NUM_SECTIONS; i++) sizes.push(readU32BE(data, 144 + i * 4));

const SECS = [];
for (let i = 0; i < NUM_SECTIONS; i++) {
  if (sizes[i] > 0) SECS.push({ off: offs[i], addr: addrs[i], size: sizes[i] });
}

function addrToOff(vaddr) {
  for (const s of SECS) {
    if (vaddr >= s.addr && vaddr < s.addr + s.size) return s.off + (vaddr - s.addr);
  }
  throw new Error(`address 0x${vaddr.toString(16)} not in any DOL section`);
}

function readBytes(vaddr, n) {
  const off = addrToOff(vaddr);
  return data.subarray(off, off + n);
}

// --- Read the table as SIGNED bytes (matches extract-borg-stat-tables.py's `>16b`) ----------

const raw = readBytes(LEVEL_TABLE_ADDR, LEVEL_TABLE_COUNT);
const dumpedSigned = [];
for (let i = 0; i < LEVEL_TABLE_COUNT; i++) {
  const u = raw[i];
  dumpedSigned.push(u > 127 ? u - 256 : u);
}

// --- Reconcile against (ak)'s recorded single-pass 32-byte dump ----------------------------

const AK_DUMP_32 = [2, 2, 8, 6, 0, 4, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1];

// --- Reconcile against extract-borg-stat-tables.py's 16-byte reading (already persisted in
//    borg-hp-stat-rows-802f2988.json's provenance block) -------------------------------------

const EXISTING_16_PATH = path.join(repoRoot, "research", "decomp", "data", "borg-hp-stat-rows-802f2988.json");
let existing16 = null;
if (fs.existsSync(EXISTING_16_PATH)) {
  const doc = JSON.parse(fs.readFileSync(EXISTING_16_PATH, "utf8"));
  existing16 = doc?.provenance?.levelOffsetTable_DAT_804339e8 ?? null;
}

const matchesAk = dumpedSigned.length === AK_DUMP_32.length && dumpedSigned.every((v, i) => v === AK_DUMP_32[i]);
const matchesExisting16 =
  existing16 !== null &&
  dumpedSigned.slice(0, existing16.length).every((v, i) => v === existing16[i]);

const discrepancies = [];
if (!matchesAk) {
  discrepancies.push({
    against: "behavior-notes.md (ak) single-pass 32-byte dump",
    theirs: AK_DUMP_32,
    ours: dumpedSigned,
    note: "MISMATCH: this dol read disagrees with (ak). Both values recorded below -- do not silently prefer one.",
  });
}
if (existing16 !== null && !matchesExisting16) {
  discrepancies.push({
    against: "research/decomp/data/borg-hp-stat-rows-802f2988.json provenance.levelOffsetTable_DAT_804339e8 (16-byte read)",
    theirs: existing16,
    ours: dumpedSigned.slice(0, existing16.length),
    note: "MISMATCH: this dol read (first 16 bytes) disagrees with the existing 16-byte extraction.",
  });
}

const out = {
  provenance: {
    extractor: "scripts/gen-level-row-offsets.mjs",
    citation:
      "research/decomp/behavior-notes.md (ak) 'Borg level system' -- DAT_804339e8 single-pass dump " +
      "(re-verified here per (ak)'s own instruction to re-verify before persisting); row-arithmetic " +
      "context from (ag); level/color byte packing context from (an) section 6 (OBSERVED_GUIDE tier).",
    readMethod:
      "dol.py-style: DOL section table parsed directly from user-data/GG4E/disc/sys/boot.dol " +
      "(offset/addr/size triples at file offsets 0x00/0x48/0x90, 18 entries), addrToOff() + " +
      "signed-byte read for each table entry -- mirrors scripts/gen_fusion_pairs.py's read pattern.",
    romConstant: "DAT_804339e8",
    tableLength: LEVEL_TABLE_COUNT,
    interpretation:
      "row = subIdx(+0x3ee) + variant(+0x3e9)*0x14 + DAT_804339e8[level(+0x3ec)]; stride 0x12; " +
      "read by zz_0055f90_ @0x80055f90 (behavior-notes.md ag).",
    date: "2026-07-03",
  },
  dumpedSigned,
  reconciliation: {
    matchesAkDump32: matchesAk,
    matchesExisting16ByteRead: existing16 === null ? null : matchesExisting16,
    akDump32: AK_DUMP_32,
    existing16ByteRead: existing16,
    discrepancies,
    discrepancyFlag:
      discrepancies.length > 0
        ? "DISCREPANCY FOUND -- see `discrepancies` above. Both readings are recorded; this file " +
          "does NOT silently pick one. Do not treat `dumpedSigned` as authoritative over the ones " +
          "it disagrees with without further re-verification."
        : "no discrepancy: this dol read matches all prior recorded readings.",
  },
  liveVerifiedAnchor: {
    borg: "pl0615 (G RED)",
    levelByteValue: 0,
    tableIndexUsed: 0,
    tableValueAtIndex0: dumpedSigned[0],
    expectedRowOffset: 2,
    resultingStats: { maxHp: 200, ammo: 5 },
    citation: "behavior-notes.md (ag): 'Cross-verified against live capture: G RED (pl0615) level row (DAT_804339e8[0]=2) = HP 200 and ammo 5'.",
  },
};

fs.mkdirSync(path.dirname(OUT), { recursive: true });
fs.writeFileSync(OUT, `${JSON.stringify(out, null, 2)}\n`);

console.log("dumped (signed bytes, 32 entries):", JSON.stringify(dumpedSigned));
console.log("matches (ak) 32-byte dump:", matchesAk);
console.log("matches existing 16-byte read (borg-hp-stat-rows-802f2988.json):", matchesExisting16);
if (discrepancies.length > 0) {
  console.log("*** DISCREPANCY FOUND -- see", OUT, "for details ***");
  for (const d of discrepancies) {
    console.log(`  vs ${d.against}:`);
    console.log(`    theirs: ${JSON.stringify(d.theirs)}`);
    console.log(`    ours:   ${JSON.stringify(d.ours)}`);
  }
}
console.log("wrote", path.relative(repoRoot, OUT));
