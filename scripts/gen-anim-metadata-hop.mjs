#!/usr/bin/env node
// Dumps the +0x1d88 family anim-metadata bank (familyAnimDescBank) for every borg
// family straight from boot.dol. Output consumed by
// packages/combat/src/data/animMetadataHop.generated.json.
//
// The playAnim stream op's operands are (metaBank=b1, metaAnim=b2) — NOT the
// motion-file (group, slot). The ROM resolves them via a two-hop s16 relative-offset
// table at actor+0x1d88: groupTable = bank + s16 bank[metaBank*2];
// record = groupTable + s16 groupTable[metaAnim*2]. Record part0 @rec[4,5] =
// (motionFile, animInFile). The actual animation is motionSet[motionFile&0x7f]
// [animInFile]; motionFile bit7 selects own vs shared motion set.
//
// Evidence: research/decomp/title-intro-residuals-decode-2026-07-06.md §1. The ctor
// dispatch table PTR_PTR_802d3224 @0x802d3224 → 16 family sub-tables → each borg's
// ctor. Each ctor stores a literal address into actor+0x1d88 via lis+addi+stw.
//
// Validation: NORMAL NINJA (pl0000) +0x1d88=0x802bd780; G RED (pl0615) +0x1d88=
// 0x80367460. NN battle meta-g0 records (0,0x0e)/(0,0x17) match the baked clips
// anim_g00_s14 / anim_g00_s23 exactly.
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const ACTION_STREAM_TABLES_PATH = "packages/combat/src/data/actionStreamTables.json";
const OUT_PATH = "packages/combat/src/data/animMetadataHop.generated.json";

const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");

// DOL section table (same parser as research/decomp/dol.py + sibling scripts).
const offsets = [];
const addrs = [];
const sizes = [];
for (let i = 0; i < 18; i += 1) {
  offsets.push(dol.readUInt32BE(i * 4));
  addrs.push(dol.readUInt32BE(0x48 + i * 4));
  sizes.push(dol.readUInt32BE(0x90 + i * 4));
}

function addrToOff(a) {
  for (let i = 0; i < 18; i += 1) {
    if (sizes[i] && addrs[i] <= a && a < addrs[i] + sizes[i]) {
      return offsets[i] + (a - addrs[i]);
    }
  }
  return null;
}

function readU8(runtimeAddr) {
  const off = addrToOff(runtimeAddr);
  return off === null ? null : dol[off];
}

function readS16(runtimeAddr) {
  const off = addrToOff(runtimeAddr);
  return off === null ? null : dol.readInt16BE(off);
}

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

/**
 * Forward-simulate the PPC register file from the ctor entry to the first blr,
 * tracking lis/addi/addic register writes, and return the value that rS holds at
 * the `stw rS, fieldOff(r3)` instruction. Returns null when:
 *  - the field store isn't found in the ctor body
 *  - the stored register holds null/0 at the store site (bank intentionally absent)
 *
 * The ctor address comes from actionStreamTables.json (constructorAddress), which
 * itself was derived from PTR_PTR_802d3224 @0x802d3224.
 */
function scanCtorField(ctorAddr, fieldOff) {
  const start = addrToOff(ctorAddr);
  if (start === null) return null;
  const reg = new Array(32).fill(null);
  for (let i = 0; i < 0x800; i += 4) {
    const off = start + i;
    if (off + 4 > dol.length) break;
    const w = dol.readUInt32BE(off);
    const op = (w >>> 26) & 0x3f;
    const rS = (w >>> 21) & 0x1f;
    const rA = (w >>> 16) & 0x1f;
    const imm = w & 0xffff;
    const sim = imm & 0x8000 ? imm - 0x10000 : imm;
    if (w === 0x4e800020) break; // blr — ctor body ends
    if (op === 0x0f) {
      // lis rS, imm
      reg[rS] = (imm << 16) >>> 0;
    } else if (op === 0x0e) {
      // addi rS, rA, simm (rA=0 ⇒ li)
      const base = rA === 0 ? 0 : reg[rA];
      reg[rS] = base === null ? null : (base + sim) >>> 0;
    } else if (op === 0x0c) {
      // addic rS, rA, simm
      const base = reg[rA];
      reg[rS] = base === null ? null : (base + sim) >>> 0;
    }
    if (op === 0x24 && rA === 3 && (w & 0xffff) === fieldOff) {
      return reg[rS];
    }
  }
  return null;
}

/**
 * Walk a family anim-metadata bank (+0x1d88). The bank is a two-level big-endian s16
 * relative-offset table:
 *   group directory = s16[N] at bank+0, terminated by -1 (0xffff)
 *   groupTable(g) = bank + s16 bank[g*2]
 *   slot directory = s16[M] at groupTable+0, terminated by -1
 *   record(s) = groupTable + s16 groupTable[s*2]
 *   part0 @rec[4] = motionFile byte, @rec[5] = animInFile byte
 *
 * Returns { groupCount, slots: Map<`${g},${s}`, { motionFile, animInFile }> }.
 */
const MAX_GROUPS = 16;
const MAX_SLOTS = 64;

function walkBank(bankAddr) {
  const slots = {};
  let groupCount = 0;
  for (let g = 0; g < MAX_GROUPS; g += 1) {
    const gRel = readS16(bankAddr + g * 2);
    if (gRel === null) break;
    if (gRel === -1) break; // group directory terminator
    groupCount = g + 1;
    const groupTable = bankAddr + gRel;
    for (let s = 0; s < MAX_SLOTS; s += 1) {
      const sRel = readS16(groupTable + s * 2);
      if (sRel === null) break;
      if (sRel === -1) break; // slot directory terminator
      const recAddr = groupTable + sRel;
      const motionFile = readU8(recAddr + 4);
      const animInFile = readU8(recAddr + 5);
      if (motionFile === null || animInFile === null) break;
      slots[`${g},${s}`] = { motionFile, animInFile };
    }
  }
  return { groupCount, slots };
}

// ----------------------------------------------------------------------------

const actionStreamTables = JSON.parse(readFileSync(ACTION_STREAM_TABLES_PATH, "utf8"));
const borgCtor = {};
for (const [borgId, b] of Object.entries(actionStreamTables.borgs || {})) {
  borgCtor[borgId] = b.constructorAddress;
}

// Collect unique ctors → members.
const ctorMembers = {};
for (const [borgId, ctor] of Object.entries(borgCtor)) {
  if (!ctor) continue;
  (ctorMembers[ctor] ||= []).push(borgId);
}

// Scan each ctor for +0x1d88 (and +0x1d80 for cross-validation).
const families = {};
const borgRemap = {};
let banksFound = 0;
let banksNull = 0;
let identityBorgCount = 0;
let remappedBorgCount = 0;
let totalEntries = 0;

for (const [ctor, members] of Object.entries(ctorMembers)) {
  const ctorAddr = parseInt(ctor, 16);
  const metaBank = scanCtorField(ctorAddr, 0x1d88);
  const streamBank = scanCtorField(ctorAddr, 0x1d80);

  const familyEntry = {
    ctor: hex(ctorAddr),
    members,
    streamBank: streamBank ? hex(streamBank) : null,
    metaBank: metaBank ? hex(metaBank) : null,
    streamBankMatchesActionStream:
      streamBank !== null &&
      members.every((id) => actionStreamTables.borgs[id]?.familyBank === hex(streamBank)),
    groupCount: null,
    slotCount: 0,
  };

  if (metaBank === null || metaBank === 0) {
    banksNull += 1;
    families[hex(ctorAddr)] = familyEntry;
    continue;
  }

  const walked = walkBank(metaBank);
  familyEntry.groupCount = walked.groupCount;
  familyEntry.slotCount = Object.keys(walked.slots).length;
  families[hex(ctorAddr)] = familyEntry;
  banksFound += 1;

  // Emit per-borg remap. All family members share the same bank.
  let isIdentity = true;
  for (const [key, rec] of Object.entries(walked.slots)) {
    const [g, s] = key.split(",").map(Number);
    if (rec.motionFile !== g || rec.animInFile !== s) isIdentity = false;
    totalEntries += 1;
  }

  for (const borgId of members) {
    if (Object.keys(walked.slots).length === 0) continue;
    borgRemap[borgId] = {};
    for (const [key, rec] of Object.entries(walked.slots)) {
      const [g, s] = key.split(",").map(Number);
      borgRemap[borgId][String(g)] = borgRemap[borgId][String(g)] || {};
      borgRemap[borgId][String(g)][String(s)] = {
        motionFile: rec.motionFile,
        animInFile: rec.animInFile,
        shared: (rec.motionFile & 0x80) !== 0,
      };
    }
    if (isIdentity) identityBorgCount += 1;
    else remappedBorgCount += 1;
  }
}

const source = {
  bootDolPath: BOOT_DOL_PATH,
  bootDolSha1,
  evidence:
    "research/decomp/title-intro-residuals-decode-2026-07-06.md §1. " +
    "PTR_PTR_802d3224 @0x802d3224 → 16 family sub-tables → each borg's ctor. " +
    "Each ctor stores a literal address into actor+0x1d88 (familyAnimDescBank) via " +
    "lis+addi+stw. Bank walk: groupTable = bank + s16 bank[g*2]; " +
    "record = groupTable + s16 groupTable[s*2]; part0 @rec[4,5] = (motionFile, animInFile).",
  addresses: {
    ctorDispatchTable: hex(0x802d3224),
    nnBankValidation: "pl0000 ctor 0x8006f4f8 → +0x1d88 = 0x802bd780",
    gredBankValidation: "pl0615 ctor 0x8018ccfc → +0x1d88 = 0x80367460",
  },
  generatedBy: path.basename(import.meta.url),
  stats: {
    uniqueCtors: Object.keys(ctorMembers).length,
    ctorsWithMetaBank: banksFound,
    ctorsWithoutMetaBank: banksNull,
    borgsWithRemap: remappedBorgCount + identityBorgCount,
    borgsWithIdentityMap: identityBorgCount,
    borgsWithNonTrivialRemap: remappedBorgCount,
    borgsWithoutRemap:
      Object.keys(borgCtor).filter((id) => !borgRemap[id]).length,
    totalEntries,
  },
};

const out = {
  _source: source,
  families,
  borgs: borgRemap,
};

writeFileSync(OUT_PATH, JSON.stringify(out, null, 2) + "\n");
console.log(`wrote ${OUT_PATH}`);
console.log(
  `  ctors: ${banksFound} with meta-bank, ${banksNull} without (fallback to direct lookup)`,
);
console.log(
  `  borgs: ${remappedBorgCount} non-trivial remap, ${identityBorgCount} identity, ` +
    `${source.stats.borgsWithoutRemap} fallback`,
);
