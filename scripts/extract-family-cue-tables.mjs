#!/usr/bin/env node
// Extract per-family cue→state tables from GG4E boot.dol.
//
// Each family ctor writes actor+0x4f0 with a pointer to a 48-entry × 2-byte table
// ([fullBodyState, upperBodyState] per cue id 0..47; -1 = no transition). The attack
// cue (44 → [61, 0]) is fleet-uniform; the other cues vary by family.
//
// The ctor's +0x4f0 write is found by scanning for the `stw rN, 0x4f0(r3)` PPC
// instruction in each family's constructor (the same ctor scan pattern used by
// scripts/gen-command-move-tables.mjs and gen-melee-anim-kinds.mjs).
//
// Output: packages/combat/src/data/familyCueTables.json
//
// Usage: node scripts/extract-family-cue-tables.mjs

import * as fs from "node:fs";
import * as path from "node:path";

const ROOT = path.resolve(import.meta.dirname, "..");
const DOL_PATH = path.join(ROOT, "user-data/GG4E/disc/sys/boot.dol");
const COMMAND_TABLES_PATH = path.join(ROOT, "packages/combat/src/data/commandMoveTables.json");
const OUT_PATH = path.join(ROOT, "packages/combat/src/data/familyCueTables.json");

const dol = fs.readFileSync(DOL_PATH);

// DOL section table (same parser as research/decomp/dol.py).
const offsets = [];
const addrs = [];
const sizes = [];
for (let i = 0; i < 18; i++) {
  offsets.push(dol.readUInt32BE(i * 4));
  addrs.push(dol.readUInt32BE(0x48 + i * 4));
  sizes.push(dol.readUInt32BE(0x90 + i * 4));
}

function addrToOff(a) {
  for (let i = 0; i < 18; i++) {
    if (sizes[i] && addrs[i] <= a && a < addrs[i] + sizes[i]) {
      return offsets[i] + (a - addrs[i]);
    }
  }
  return null;
}

function readU32(a) {
  const o = addrToOff(a);
  return o === null ? null : dol.readUInt32BE(o);
}

function readI8(a) {
  const o = addrToOff(a);
  if (o === null) return null;
  const b = dol[o];
  return b >= 0x80 ? b - 0x100 : b;
}

/**
 * Scan a ctor function body for the `stw rN, 0x4f0(r3)` instruction that writes
 * actor+0x4f0 (the cue-table pointer). PPC `stw rS, d(rA)` = opcode 0x24 (36),
 * encoded as: (36<<26) | (rS<<21) | (rA<<16) | (d & 0xffff).
 * We search for d === 0x4f0 and extract rS (the register holding the table address),
 * then trace it back to the `lis rS, ...; addi rS, rS, ...` pair that loads the
 * 32-bit address.
 */
function findCueTableAddr(ctorAddr) {
  // Scan up to 0x800 bytes of the ctor body.
  const startOff = addrToOff(ctorAddr);
  if (startOff === null) return null;
  for (let off = startOff; off < startOff + 0x800; off += 4) {
    if (off + 4 > dol.length) break;
    const w = dol.readUInt32BE(off);
    const op = (w >>> 26) & 0x3f;
    if (op !== 0x24) continue; // not stw
    const rA = (w >>> 16) & 0x1f;
    const d = w & 0xffff;
    if (rA !== 3 || d !== 0x4f0) continue; // not stw rN, 0x4f0(r3)
    const rS = (w >>> 21) & 0x1f;
    // Trace back: find the most recent lis+addi pair that loads rS.
    let hi = null;
    for (let back = off - 4; back >= startOff; back -= 4) {
      const bw = dol.readUInt32BE(back);
      const bop = (bw >>> 26) & 0x3f;
      const bRS = (bw >>> 21) & 0x1f;
      const bRA = (bw >>> 16) & 0x1f;
      if (bop === 0x0f && bRS === rS && bRA === 0) {
        // lis rS, imm
        hi = (bw & 0xffff) << 16;
      }
      if (bop === 0x0e && bRS === rS && bRA === rS && hi !== null) {
        // addi rS, rS, imm (sign-extended)
        let lo = bw & 0xffff;
        if (lo & 0x8000) lo -= 0x10000;
        return (hi + lo) >>> 0;
      }
    }
  }
  return null;
}

/** Read a 48-entry cue table (96 bytes) from the given address. */
function readCueTable(addr) {
  const table = [];
  for (let cue = 0; cue < 48; cue++) {
    table.push([readI8(addr + cue * 2), readI8(addr + cue * 2 + 1)]);
  }
  return table;
}

// --- Main: scan every family ctor from commandMoveTables.json ---
const cmdTables = JSON.parse(fs.readFileSync(COMMAND_TABLES_PATH, "utf8"));
const borgs = cmdTables.borgs || {};

const out = {
  _meta: {
    source: "user-data/GG4E/disc/sys/boot.dol",
    generator: "scripts/extract-family-cue-tables.mjs",
    evidence: "ctor scan for stw rN, 0x4f0(r3) → lis/addi trace (same pattern as gen-command-move-tables.mjs)",
    layout: "48 entries per family, [fullBodyState, upperBodyState], -1 = no transition",
    note: "cue 44 (attack) → [61, 0] is fleet-uniform across all decoded families. Other cues vary by family.",
  },
  families: {},
};

let count = 0;
let fleetUniformAttack = 0;
for (const [borgId, assignment] of Object.entries(borgs)) {
  const ctorAddr = parseInt(assignment.constructorAddress, 16);
  if (!ctorAddr || !addrToOff(ctorAddr)) continue;
  const cueAddr = findCueTableAddr(ctorAddr);
  if (cueAddr === null) continue;
  const table = readCueTable(cueAddr);
  // Validate: cue 44 should be [61, 0] (attack → state 61).
  if (table[44][0] === 61 && table[44][1] === 0) fleetUniformAttack++;
  out.families[borgId] = {
    cueTableAddr: "0x" + cueAddr.toString(16),
    ctorAddress: assignment.constructorAddress,
    entries: table,
  };
  count++;
}

out._meta.borgsExtracted = count;
out._meta.fleetUniformAttackCue = `${fleetUniformAttack}/${count}`;

fs.writeFileSync(OUT_PATH, JSON.stringify(out, null, 2) + "\n");
console.log(`Extracted ${count} family cue tables → ${path.relative(ROOT, OUT_PATH)}`);
console.log(`Attack cue (44 → [61,0]) uniform in ${fleetUniformAttack}/${count} families.`);
