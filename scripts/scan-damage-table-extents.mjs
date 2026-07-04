#!/usr/bin/env node
// Estimate damage-record table extents: symbol-gap analysis + raw DOL record dump.
import fs from "node:fs";
import path from "node:path";
import { execSync } from "node:child_process";

const repoRoot = "D:/GotYaForce";
const dol = fs.readFileSync(path.join(repoRoot, "user-data/GG4E/disc/sys/boot.dol"));

const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
function offsetFor(address) {
  for (let i = 0; i < 18; i++) {
    if (sectionSizes[i] > 0 && address >= sectionAddresses[i] && address < sectionAddresses[i] + sectionSizes[i])
      return sectionOffsets[i] + (address - sectionAddresses[i]);
  }
  return null;
}

// 1. collect all referenced symbol addresses from ghidra export
const exportDir = path.join(repoRoot, "research/decomp/ghidra-export");
const symbols = new Set();
for (const f of fs.readdirSync(exportDir)) {
  if (!f.endsWith(".c")) continue;
  const text = fs.readFileSync(path.join(exportDir, f), "utf8");
  for (const m of text.matchAll(/_([0-9a-f]{8})\b/g)) {
    const a = parseInt(m[1], 16);
    if (a >= 0x80000000 && a < 0x81800000) symbols.add(a);
  }
  // ==== 80xxxxxx function headers too
  for (const m of text.matchAll(/^\/\/ ==== ([0-9a-f]{8})/gm)) symbols.add(parseInt(m[1], 16));
}
const sorted = [...symbols].sort((a, b) => a - b);
function successor(addr) {
  let lo = 0, hi = sorted.length - 1, ans = null;
  while (lo <= hi) {
    const mid = (lo + hi) >> 1;
    if (sorted[mid] > addr) { ans = sorted[mid]; hi = mid - 1; } else lo = mid + 1;
  }
  return ans;
}

const tables = [
  ["DAT_802d46e0", 0x802d46e0, "zz_0072048_ @80072048 (family01 generic) [calibration: known 9 records]"],
  ["DAT_802c4760", 0x802c4760, "zz_008ae60_ @8008ae60 (comhit/generic)"],
  ["DAT_80321ef0", 0x80321ef0, "ctor 80105144"],
  ["DAT_80323208", 0x80323208, "ctor 80106e3c"],
  ["DAT_8032d628", 0x8032d628, "ctor 801223c0 (samurai default)"],
  ["DAT_8032d850", 0x8032d850, "ctor 801223c0 (samurai 0x70c/0x70d)"],
  ["DAT_80365ec0", 0x80365ec0, "ctor 8018ccfc (G RED family)"],
  ["DAT_80375390", 0x80375390, "ctor 8019e414"],
  ["DAT_80376960", 0x80376960, "ctor 8019e9a4"],
  ["DAT_80377ac0", 0x80377ac0, "ctor 801a04f0"],
  ["DAT_803785e8", 0x803785e8, "ctor 801a10e8"],
  ["DAT_803796b0", 0x803796b0, "ctor 801a51cc"],
  ["DAT_80380c90", 0x80380c90, "ctor 801b289c"],
  ["DAT_803810f8", 0x803810f8, "ctor 801b3598"],
  ["DAT_80381448", 0x80381448, "ctor 801b3c6c"],
];

function hex(v) { return "0x" + v.toString(16); }

for (const [name, addr, note] of tables) {
  const succ = successor(addr);
  const gap = succ ? succ - addr : null;
  const off = offsetFor(addr);
  console.log(`\n=== ${name} (${note})`);
  console.log(`  dol offset ${off === null ? "UNMAPPED" : hex(off)}; next referenced symbol ${succ ? hex(succ) : "?"} gap ${gap ? hex(gap) : "?"} => ${gap ? (gap / 0x18).toFixed(2) : "?"} records max`);
  if (off === null) continue;
  // dump records until gap end or 64 records, flag plausibility
  const maxRecs = Math.min(gap ? Math.floor(gap / 0x18) : 64, 64);
  let lines = [];
  for (let i = 0; i < maxRecs; i++) {
    const o = off + i * 0x18;
    const hp = dol.readUInt16BE(o), down = dol.readUInt16BE(o + 2), bal = dol.readUInt16BE(o + 4), combo = dol.readUInt16BE(o + 6);
    const rest = dol.subarray(o + 8, o + 0x18).toString("hex");
    lines.push(`  [${String(i).padStart(2)}] hp=${hp} down=${down} bal=${bal} combo=${combo} rest=${rest}`);
  }
  console.log(lines.join("\n"));
}
