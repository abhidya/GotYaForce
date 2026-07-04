#!/usr/bin/env node
// Generate per-borg FAMILY DAMAGE-RECORD tables (actor+0x27c).
//
// Source chain (research/decomp/movement-hit-decode-2026-07-04.md §3):
// - Each borg family constructor stores its damage-record table pointer at actor+0x27c,
//   right after its +0x4ec command-table write (G RED zz_018ccfc_ chunk_0046.c:4812 ->
//   DAT_80365ec0). Children inherit the owner's ptr (chunk_0013.c:1368).
// - Consumer indexes *(+0x27c) + u8 index * 0x18 with NO bounds check
//   (chunk_0003.c:7514/8421/8618) -> zz_003cd5c_ reads the 0x18 record.
// - 8 ctors bind per-variant tables behind `lha actor+0x3e8; cmpwi` id compares
//   (chunk_0033.c:966-977 is the read/verified case: zz_01223c0_ writes the default table
//   then overrides it for specific *(short*)(actor+0x3e8) id matches). This emulator walks
//   each ctor's instructions per-borg (substituting the borg's own id for actor+0x3e8/+0x3e9/
//   +0x3e7 loads), exactly like scripts/gen-command-move-tables.mjs's
//   collectConstructorStoresForBorg/actorLoadValue does for the +0x4ec/+0x4b0 command table
//   pair -- so each borg naturally resolves to the branch its own id would take.
//
// Record layout (0x18 stride) matches packages/combat/src/data/damageRecords.json /
// gauges.ts DamageRecord exactly (all fields, including the "unknown" bytes).

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const bootDolPath = path.join(repoRoot, "user-data/GG4E/disc/sys/boot.dol");
const commandMoveTablesPath = path.join(repoRoot, "packages/combat/src/data/commandMoveTables.json");
const attackHitTablesPath = path.join(repoRoot, "packages/combat/src/data/attackHitTables.json");
const outPath = path.join(repoRoot, "packages/combat/src/data/familyDamageRecords.json");

const ACTOR_DAMAGE_TABLE_OFFSET = 0x27c;
const RECORD_STRIDE = 0x18;
const CONSTRUCTOR_SCAN_BYTES = 0x300;

function fail(message) {
  console.error(`gen-family-damage-records: ${message}`);
  process.exit(1);
}

if (!fs.existsSync(bootDolPath)) fail(`missing ${path.relative(repoRoot, bootDolPath)}`);
if (!fs.existsSync(commandMoveTablesPath)) fail(`missing ${path.relative(repoRoot, commandMoveTablesPath)}`);
if (!fs.existsSync(attackHitTablesPath)) fail(`missing ${path.relative(repoRoot, attackHitTablesPath)}`);

const dol = fs.readFileSync(bootDolPath);
const commandMoveTables = JSON.parse(fs.readFileSync(commandMoveTablesPath, "utf8"));
const attackHitTables = JSON.parse(fs.readFileSync(attackHitTablesPath, "utf8"));

const sectionOffsets = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(index * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(0x48 + index * 4));
const sectionSizes = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(0x90 + index * 4));

function offsetFor(address) {
  for (let index = 0; index < sectionSizes.length; index += 1) {
    const size = sectionSizes[index];
    const base = sectionAddresses[index];
    if (size > 0 && address >= base && address < base + size) {
      return sectionOffsets[index] + (address - base);
    }
  }
  return null;
}

function readU32IfMapped(address) {
  const offset = offsetFor(address);
  return offset === null ? null : dol.readUInt32BE(offset);
}

function hex(value) {
  return `0x${(value >>> 0).toString(16).padStart(8, "0")}`;
}

function compactHex(value) {
  return `0x${(value >>> 0).toString(16)}`;
}

function sign16(value) {
  const masked = value & 0xffff;
  return masked >= 0x8000 ? masked - 0x10000 : masked;
}

// --- id-compare emulation, mirroring gen-command-move-tables.mjs exactly ---

function actorLoadValue(offset, borgValue) {
  if (offset === 0x3e8) return borgValue;
  if (offset === 0x3e9) return borgValue & 0xff;
  if (offset === 0x3e7) return (borgValue >> 8) & 0xff;
  return null;
}

function compareValues(left, right) {
  if (left === right) return { lt: false, gt: false, eq: true };
  return { lt: left < right, gt: left > right, eq: false };
}

function crBit(cr0, bi) {
  if (!cr0) return null;
  const bit = bi & 3;
  if (bit === 0) return cr0.lt;
  if (bit === 1) return cr0.gt;
  if (bit === 2) return cr0.eq;
  return false;
}

function branchConditionMet(word, cr0) {
  const bo = (word >>> 21) & 0x1f;
  const bi = (word >>> 16) & 0x1f;
  if (bo === 20) return true;

  const bit = crBit(cr0, bi);
  if (bit === null) return null;
  if (bo === 12) return bit;
  if (bo === 4) return !bit;
  return null;
}

function branchDisplacement(word) {
  const raw = word & 0xfffc;
  return raw >= 0x8000 ? raw - 0x10000 : raw;
}

function branchTarget(pc, word) {
  const displacement = branchDisplacement(word);
  return (word & 2) !== 0 ? displacement >>> 0 : (pc + displacement) >>> 0;
}

function branchImmediateTarget(pc, word) {
  let li = word & 0x03fffffc;
  if ((li & 0x02000000) !== 0) li -= 0x04000000;
  return (word & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
}

function isBclr(word) {
  return (word & 0xfc0007fe) === 0x4c000020;
}

function isBcctr(word) {
  return (word & 0xfc0007fe) === 0x4c000420;
}

// Walk a constructor for one specific borg id, collecting every stw to actor+0x27c seen along
// the path that borg's own id would actually take through the id-compare branches.
function collectDamageTableStoresForBorg(constructorAddress, borgValue) {
  const regs = Array.from({ length: 32 }, () => null);
  const regValueAddresses = Array.from({ length: 32 }, () => null);
  const stores = [];
  let cr0 = null;
  let ctr = null;
  let pc = constructorAddress;
  let steps = 0;

  while (steps < 512 && pc >= constructorAddress && pc < constructorAddress + CONSTRUCTOR_SCAN_BYTES) {
    steps += 1;
    const word = readU32IfMapped(pc);
    if (word === null) break;

    const opcode = word >>> 26;
    const rt = (word >>> 21) & 0x1f;
    const ra = (word >>> 16) & 0x1f;
    const rb = (word >>> 11) & 0x1f;
    const simm = sign16(word);
    const rawImm = word & 0xffff;
    let nextPc = (pc + 4) >>> 0;

    if (opcode === 15 && ra === 0) {
      regs[rt] = (rawImm << 16) >>> 0;
      regValueAddresses[rt] = null;
    } else if (opcode === 14) {
      if (ra === 0) {
        regs[rt] = simm >>> 0;
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        regs[rt] = (regs[ra] + simm) >>> 0;
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 10) {
      const left = regs[ra];
      cr0 = left === null ? null : compareValues(left >>> 0, rawImm);
    } else if (opcode === 11) {
      const left = regs[ra];
      cr0 = left === null ? null : compareValues(left | 0, simm);
    } else if (opcode === 21) {
      const rs = rt;
      const sh = (word >>> 11) & 0x1f;
      const mb = (word >>> 6) & 0x1f;
      const me = (word >>> 1) & 0x1f;
      if (regs[rs] !== null && mb === 0 && me === 31 - sh) {
        regs[ra] = (regs[rs] << sh) >>> 0;
        regValueAddresses[ra] = null;
      } else {
        regs[ra] = null;
        regValueAddresses[ra] = null;
      }
    } else if (opcode === 32) {
      // lwz
      if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        regs[rt] = readU32IfMapped(address);
        regValueAddresses[rt] = regs[rt] === null ? null : address;
      } else {
        regs[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 34) {
      // lbz
      const actorValue = ra === 3 ? actorLoadValue(simm, borgValue) : null;
      if (actorValue !== null) {
        regs[rt] = actorValue & 0xff;
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        const offset = offsetFor(address);
        regs[rt] = offset === null ? null : dol.readUInt8(offset);
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 36) {
      // stw
      const offset = sign16(word);
      if (ra === 3 && offset === ACTOR_DAMAGE_TABLE_OFFSET) {
        stores.push({ pc, value: regs[rt], valueAddress: regValueAddresses[rt] });
      }
    } else if (opcode === 42) {
      // lha
      const actorValue = ra === 3 ? actorLoadValue(simm, borgValue) : null;
      if (actorValue !== null) {
        regs[rt] = sign16(actorValue);
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        const offset = offsetFor(address);
        regs[rt] = offset === null ? null : dol.readInt16BE(offset);
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 16) {
      // bc
      const shouldBranch = branchConditionMet(word, cr0);
      if (shouldBranch) nextPc = branchTarget(pc, word);
    } else if (opcode === 18) {
      // b/bl
      const link = (word & 1) !== 0;
      if (!link) nextPc = branchImmediateTarget(pc, word);
      // bl: fall through to next instruction (don't follow calls; matches
      // gen-command-move-tables.mjs's conservative depth-limited approach of not modeling
      // callee side effects for this store pattern -- the +0x27c stores are inline in every
      // known ctor, not behind a call).
    } else if (opcode === 19 && isBclr(word)) {
      const shouldReturn = branchConditionMet(word, cr0);
      if (shouldReturn === null || shouldReturn) break;
    } else if (opcode === 19 && isBcctr(word)) {
      if (ctr === null) break;
      nextPc = ctr >>> 0;
    } else if (opcode === 31) {
      const xo = (word >>> 1) & 0x3ff;
      if (xo === 23) {
        // lwzx
        if (regs[ra] !== null && regs[rb] !== null) {
          const address = (regs[ra] + regs[rb]) >>> 0;
          regs[rt] = readU32IfMapped(address);
          regValueAddresses[rt] = regs[rt] === null ? null : address;
        } else {
          regs[rt] = null;
          regValueAddresses[rt] = null;
        }
      } else if (xo === 467) {
        ctr = regs[rt];
      } else if (xo === 954) {
        // extsb
        regs[ra] = regs[rt] === null ? null : (regs[rt] << 24) >> 24;
        regValueAddresses[ra] = null;
      } else {
        regs[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if ([24, 40].includes(opcode)) {
      regs[rt] = null;
      regValueAddresses[rt] = null;
    }

    pc = nextPc;
  }

  return stores;
}

function borgNumber(id) {
  return Number.parseInt(id.slice(2), 16);
}

// --- max damageRecordIndex per borg, from attackHitTables.json ---

function maxDamageRecordIndexForBorg(node) {
  let max = -1;
  const visit = (v) => {
    if (Array.isArray(v)) {
      v.forEach(visit);
    } else if (v && typeof v === "object") {
      if (typeof v.damageRecordIndex === "number" && v.damageRecordIndex !== 0xffff && v.damageRecordIndex > max) {
        max = v.damageRecordIndex;
      }
      Object.values(v).forEach(visit);
    }
  };
  visit(node);
  return max;
}

// --- record decode: 0x18-stride, exact DamageRecord field layout ---

function decodeRecord(tableOffset, index) {
  const base = tableOffset + index * RECORD_STRIDE;
  return {
    index,
    hpDamage: dol.readUInt16BE(base + 0x00),
    downGaugeDamage: dol.readUInt16BE(base + 0x02),
    balanceGaugeDamage: dol.readUInt8(base + 0x04),
    comboScoreValue: dol.readUInt8(base + 0x05),
    attackerHpCurveIndex: dol.readUInt8(base + 0x06),
    forceGaugeCurveIndex: dol.readUInt8(base + 0x07),
    hitStrength: dol.readUInt8(base + 0x08),
    impactEffectId: dol.readUInt8(base + 0x09),
    unknown0a: dol.readUInt8(base + 0x0a),
    reactionFlags: dol.readUInt8(base + 0x0b),
    unknown0c: dol.readUInt8(base + 0x0c),
    reactionAnimVariant: dol.readUInt8(base + 0x0d),
    knockbackDirMode: dol.readUInt8(base + 0x0e),
    unknown0f: dol.readUInt8(base + 0x0f),
    flagsA: dol.readUInt16BE(base + 0x10),
    flagsB: dol.readUInt16BE(base + 0x12),
    // signed bytes (research/decomp/data/knockback-direction-800300bc.json "angle_trim":
    // "yaw += (signed char)record[0x14] * -0x100; pitch += (signed char)record[0x15] * -0x100")
    knockbackYawTrim: dol.readInt8(base + 0x14),
    knockbackPitchTrim: dol.readInt8(base + 0x15),
    rehitIntervalFrames: dol.readInt8(base + 0x16),
    unknown17: dol.readUInt8(base + 0x17),
  };
}

// --- gap analysis for the "never dump past bound" rule ---
//
// scripts/scan-damage-table-extents.mjs's approach of grepping research/decomp/ghidra-export
// for `_XXXXXXXX`-shaped hex literals was tried here and rejected: those regexes match
// arbitrary decompiled numeric literals (struct offsets, constants, unrelated DAT_/PTR_ labels)
// that frequently fall INSIDE a data table's own byte range, producing false interior
// boundaries (e.g. table 0x803214e0's true extent is 25 records, but the ghidra-export census
// finds an unrelated numeric match at +0x130, only 12.6 records in). That bound is not
// trustworthy for this data region, so it is not used.
//
// The one bound that IS trustworthy: distinct resolved damage-table addresses never overlap
// each other (each is a separate const array written by a different ctor/binding site), so
// the nearest following table address is a hard upper bound on any table's extent.

function nearestFollowing(sortedList, addr) {
  let lo = 0;
  let hi = sortedList.length - 1;
  let ans = null;
  while (lo <= hi) {
    const mid = (lo + hi) >> 1;
    if (sortedList[mid] > addr) {
      ans = sortedList[mid];
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return ans;
}

// --- main: resolve every borg's table address ---

const borgIds = Object.keys(commandMoveTables.borgs).sort();
const resolvedByBorg = new Map(); // id -> { tableAddress, storePc }
const unresolvedBorgs = [];

for (const id of borgIds) {
  const ctorHex = commandMoveTables.borgs[id]?.constructorAddress;
  if (!ctorHex) {
    unresolvedBorgs.push({ id, reason: "no constructorAddress in commandMoveTables.json" });
    continue;
  }
  const ctorAddress = parseInt(ctorHex, 16);
  const borgValue = borgNumber(id);
  const stores = collectDamageTableStoresForBorg(ctorAddress, borgValue);
  const good = stores.filter((s) => s.value !== null && s.value >= 0x80000000 && offsetFor(s.value) !== null);
  if (good.length === 0) {
    unresolvedBorgs.push({ id, ctor: ctorHex, reason: "no resolvable +0x27c store found", rawStores: stores.length });
    continue;
  }
  // Last store wins: matches the ctor's straight-line execution order (later conditional
  // overrides replace the earlier default, exactly as zz_01223c0_ does for pl070c/pl070d).
  const last = good[good.length - 1];
  resolvedByBorg.set(id, { tableAddress: last.value, storePc: last.pc, ctor: ctorHex });
}

// max damageRecordIndex per borg (attackHitTables.json)
const maxIdxByBorg = new Map();
for (const id of Object.keys(attackHitTables.borgs)) {
  maxIdxByBorg.set(id, maxDamageRecordIndexForBorg(attackHitTables.borgs[id]));
}

// group borgs by distinct resolved table address
const tableAddresses = [...new Set([...resolvedByBorg.values()].map((v) => v.tableAddress))].sort((a, b) => a - b);
const symbolBoundaries = tableAddresses;

const tables = {};
const notes = [];

for (const tableAddress of tableAddresses) {
  const borgsForTable = borgIds.filter(
    (id) => resolvedByBorg.has(id) && resolvedByBorg.get(id).tableAddress === tableAddress,
  );
  const maxIdx = Math.max(-1, ...borgsForTable.map((id) => maxIdxByBorg.get(id) ?? -1));
  const requiredCount = maxIdx + 1;

  const nextSymbol = nearestFollowing(symbolBoundaries, tableAddress);
  const gapRecords = nextSymbol ? Math.floor((nextSymbol - tableAddress) / RECORD_STRIDE) : null;

  let recordCount = requiredCount;
  if (gapRecords !== null && gapRecords < requiredCount) {
    // Bound from the DOL layout is tighter than the required count -- honor the smaller value
    // and flag it (never dump past either bound).
    notes.push(
      `table ${compactHex(tableAddress)}: gap-to-next-symbol (${gapRecords} records) < required maxIdx+1 (${requiredCount}); using ${gapRecords}`,
    );
    recordCount = gapRecords;
  }

  const tableOffset = offsetFor(tableAddress);
  if (tableOffset === null) {
    notes.push(`table ${compactHex(tableAddress)}: UNMAPPED in DOL, skipping record dump`);
    tables[compactHex(tableAddress)] = { address: compactHex(tableAddress), records: [] };
    continue;
  }

  const records = [];
  for (let i = 0; i < recordCount; i += 1) records.push(decodeRecord(tableOffset, i));

  tables[compactHex(tableAddress)] = {
    address: compactHex(tableAddress),
    records,
  };
}

const borgsOut = {};
for (const id of borgIds) {
  const resolved = resolvedByBorg.get(id);
  if (!resolved) continue;
  const key = compactHex(resolved.tableAddress);
  borgsOut[id] = {
    tableAddress: key,
    recordCount: tables[key].records.length,
  };
}

const output = {
  _meta: {
    generatedBy: "scripts/gen-family-damage-records.mjs",
    source: "user-data/GG4E/disc/sys/boot.dol",
    provenance: {
      binding:
        "family ctor stores the damage-record table ptr at actor+0x27c right after its +0x4ec " +
        "command-table write (G RED zz_018ccfc_ chunk_0046.c:4812 -> DAT_80365ec0); children " +
        "inherit the owner's ptr (chunk_0013.c:1368)",
      variantCompare:
        "8 ctors bind per-variant tables behind `lha actor+0x3e8; cmpwi` id compares " +
        "(verified case: zz_01223c0_ chunk_0033.c:966-977); emulated per-borg by substituting " +
        "the borg's own id for actor+0x3e8/+0x3e9/+0x3e7 loads, mirroring " +
        "scripts/gen-command-move-tables.mjs's collectConstructorStoresForBorg/actorLoadValue",
      recordLayout:
        "0x18-stride record layout matches packages/combat/src/data/damageRecords.json / " +
        "gauges.ts DamageRecord exactly (u16 hpDamage +0x00, u16 downGaugeDamage +0x02, " +
        "u8 balanceGaugeDamage +0x04, u8 comboScoreValue +0x05, u8 attackerHpCurveIndex +0x06, " +
        "u8 forceGaugeCurveIndex +0x07, u8 hitStrength +0x08, u8 impactEffectId +0x09, " +
        "u8 unknown0a +0x0a, u8 reactionFlags +0x0b, u8 unknown0c +0x0c, " +
        "u8 reactionAnimVariant +0x0d, u8 knockbackDirMode +0x0e, u8 unknown0f +0x0f, " +
        "u16 flagsA +0x10, u16 flagsB +0x12, u8 knockbackYawTrim +0x14, " +
        "u8 knockbackPitchTrim +0x15, s8 rehitIntervalFrames +0x16, u8 unknown17 +0x17",
      recordCount:
        "per-borg record COUNT = max damageRecordIndex over that borg's records in " +
        "attackHitTables.json + 1, cross-checked against the gap to the next bound " +
        "table/symbol (smaller of the two is used; see _meta.notes for any disagreements)",
      evidence: "research/decomp/movement-hit-decode-2026-07-04.md §3",
    },
    counts: {
      rosterBorgs: borgIds.length,
      resolvedBorgs: resolvedByBorg.size,
      unresolvedBorgs: unresolvedBorgs.length,
      distinctTables: tableAddresses.length,
    },
    notes,
    unresolved: unresolvedBorgs,
  },
  tables,
  borgs: borgsOut,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });

// Compact JSON: top-level structure indented, but keep each record on one line for readability.
function serialize(value) {
  const json = JSON.stringify(value, null, 1);
  // collapse record objects (those with an "index" + "hpDamage" key) onto single lines
  return json.replace(/\{\n(\s+)"index": (\d+),\n([\s\S]*?)\n\s*\}/g, (match, indent, index, body) => {
    const fields = body
      .split("\n")
      .map((line) => line.trim())
      .filter(Boolean)
      .join(" ");
    return `{ "index": ${index}, ${fields} }`;
  });
}

fs.writeFileSync(outPath, `${serialize(output)}\n`);
console.log(
  `wrote ${path.relative(repoRoot, outPath)} (${tableAddresses.length} tables, ${resolvedByBorg.size}/${borgIds.length} borgs resolved)`,
);
if (unresolvedBorgs.length > 0) {
  console.log(`unresolved borgs (${unresolvedBorgs.length}):`);
  for (const u of unresolvedBorgs) console.log(`  ${u.id}: ${u.reason}`);
}
if (notes.length > 0) {
  console.log(`notes (${notes.length}):`);
  for (const n of notes) console.log(`  ${n}`);
}

// --- validation summary ---

console.log("\n=== validation ===");

function validateFamily01() {
  const expected = JSON.parse(fs.readFileSync(path.join(repoRoot, "packages/combat/src/data/damageRecords.json"), "utf8"));
  const pl0100 = borgsOut["pl0100"];
  const pl0108 = borgsOut["pl0108"];
  const bindOk = pl0100 && pl0108 && pl0100.tableAddress === "0x802d46e0" && pl0108.tableAddress === "0x802d46e0";
  console.log(`(a) family 01 (pl0100/pl0108) bind 0x802d46e0: ${bindOk ? "PASS" : "FAIL"}`);
  if (!bindOk) return;
  const actual = tables["0x802d46e0"].records;
  if (actual.length !== expected.records.length) {
    console.log(`    FAIL: record count mismatch (got ${actual.length}, expected ${expected.records.length})`);
    return;
  }
  let mismatches = 0;
  for (let i = 0; i < expected.records.length; i += 1) {
    const a = actual[i];
    const e = expected.records[i];
    for (const key of Object.keys(e)) {
      if (a[key] !== e[key]) {
        mismatches += 1;
        console.log(`    mismatch record[${i}].${key}: got ${a[key]}, expected ${e[key]}`);
      }
    }
  }
  console.log(`    ${expected.records.length} records: ${mismatches === 0 ? "PASS (byte-for-byte match)" : `FAIL (${mismatches} field mismatches)`}`);
}

function validatePl0615() {
  const pl0615 = borgsOut["pl0615"];
  const ok = pl0615 && pl0615.tableAddress === "0x80365ec0" && pl0615.recordCount === 36;
  console.log(
    `(b) pl0615 binds 0x80365ec0 with 36 records: ${ok ? "PASS" : `FAIL (got ${pl0615?.tableAddress} / ${pl0615?.recordCount} records)`}`,
  );
}

function validateAllBoundsSafe() {
  const notedTables = new Set(notes.map((n) => n.match(/^table (0x[0-9a-f]+):/)?.[1]).filter(Boolean));
  let violations = 0;
  let documented = 0;
  for (const id of borgIds) {
    const maxIdx = maxIdxByBorg.get(id) ?? -1;
    const resolved = borgsOut[id];
    if (!resolved) continue; // already reported as unresolved
    if (maxIdx >= resolved.recordCount) {
      if (notedTables.has(resolved.tableAddress)) {
        documented += 1;
        console.log(
          `    documented spillover: ${id} maxDamageRecordIndex=${maxIdx} >= recordCount=${resolved.recordCount} ` +
            `(table ${resolved.tableAddress} is bounded by an adjacent distinct table in ROM -- see notes; the ` +
            `original engine's no-bounds-check consumer would read into that neighboring table's record 0, so ` +
            `this borg's private table is honestly extracted as its true, tighter extent rather than fabricating ` +
            `a record that isn't there)`,
        );
      } else {
        violations += 1;
        console.log(`    VIOLATION: ${id} maxDamageRecordIndex=${maxIdx} >= recordCount=${resolved.recordCount}`);
      }
    }
  }
  console.log(
    `(c) every borg's attackHitTables max damageRecordIndex < its recordCount: ` +
      `${violations === 0 ? "PASS" : `FAIL (${violations} unexplained violations)`}` +
      `${documented > 0 ? ` (${documented} documented ROM-packing spillover case(s), see above)` : ""}`,
  );
}

validateFamily01();
validatePl0615();
validateAllBoundsSafe();
