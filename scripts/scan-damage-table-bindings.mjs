#!/usr/bin/env node
// Scan boot.dol for stw rN, 0x27c(r3) in each borg constructor (following bl one level+),
// mirroring scripts/gen-command-move-tables.mjs's collectConstructorStoresForBorg approach.
import fs from "node:fs";

const dol = fs.readFileSync("D:/GotYaForce/user-data/GG4E/disc/sys/boot.dol");
const cmd = JSON.parse(fs.readFileSync("D:/GotYaForce/packages/combat/src/data/commandMoveTables.json", "utf8"));
const hit = JSON.parse(fs.readFileSync("D:/GotYaForce/packages/combat/src/data/attackHitTables.json", "utf8"));

const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
function offsetFor(a) {
  for (let i = 0; i < 18; i++)
    if (sectionSizes[i] > 0 && a >= sectionAddresses[i] && a < sectionAddresses[i] + sectionSizes[i])
      return sectionOffsets[i] + (a - sectionAddresses[i]);
  return null;
}
const readU32 = (a) => { const o = offsetFor(a); return o === null ? null : dol.readUInt32BE(o); };
const sign16 = (v) => (v & 0x8000 ? (v & 0xffff) - 0x10000 : v & 0xffff);
const hex = (v) => "0x" + (v >>> 0).toString(16);

// max damageRecordIndex per ctor (lower bound on table size)
const maxIdxByCtor = new Map();
{
  const walk = (node) => {
    let max = -1;
    const visit = (v) => {
      if (Array.isArray(v)) v.forEach(visit);
      else if (v && typeof v === "object") {
        if (typeof v.damageRecordIndex === "number" && v.damageRecordIndex !== 0xffff && v.damageRecordIndex > max) max = v.damageRecordIndex;
        Object.values(v).forEach(visit);
      }
    };
    visit(node);
    return max;
  };
  for (const [id, node] of Object.entries(hit.borgs ?? {})) {
    const ctor = cmd.borgs?.[id]?.constructorAddress;
    if (!ctor) continue;
    const m = walk(node);
    const cur = maxIdxByCtor.get(ctor) ?? -1;
    if (m > cur) maxIdxByCtor.set(ctor, m);
  }
}

// scan: linear walk with lis/addi tracking; follow bl (depth<=3); take conditional branches BOTH not-taken path only is wrong;
// keep it simple: don't follow conditional branches (fall through), follow unconditional b, follow bl by recursion.
function scanCtor(entry, depth, visited, results, path) {
  if (depth > 3 || visited.has(entry)) return;
  visited.add(entry);
  const regs = Array.from({ length: 32 }, () => null);
  let pc = entry;
  for (let steps = 0; steps < 800; steps++) {
    const word = readU32(pc);
    if (word === null) return;
    const op = word >>> 26;
    const rt = (word >>> 21) & 31;
    const ra = (word >>> 16) & 31;
    const simm = sign16(word);
    let next = pc + 4;
    if (op === 15 && ra === 0) regs[rt] = (word & 0xffff) << 16 >>> 0; // lis
    else if (op === 14) regs[rt] = ra === 0 ? simm >>> 0 : regs[ra] !== null ? (regs[ra] + simm) >>> 0 : null; // addi
    else if (op === 32) { // lwz
      regs[rt] = regs[ra] !== null ? readU32((regs[ra] + simm) >>> 0) : null;
    } else if (op === 36) { // stw
      if (ra === 3 && simm === 0x27c) results.push({ pc, value: regs[rt], via: path });
    } else if (op === 18) { // b/bl
      let li = word & 0x03fffffc;
      if (li & 0x02000000) li -= 0x04000000;
      const target = (word & 2) ? li >>> 0 : (pc + li) >>> 0;
      if (word & 1) {
        scanCtor(target, depth + 1, visited, results, [...path, hex(target)]);
        // assume volatile regs clobbered except we keep r13-r31? conservative: clear r0-r12
        for (let r = 0; r <= 12; r++) if (r !== 3) regs[r] = null;
      } else {
        next = target;
        if (target <= pc) return; // avoid loops backwards
      }
    } else if (op === 19 && (word & 0xfc0007fe) === 0x4c000020) { // bclr
      const bo = (word >>> 21) & 31;
      if (bo === 20) return; // blr
    } else if (op !== 16 && op !== 10 && op !== 11) {
      // other ops: clobber rt for loads/arith we don't model
      if ([34, 40, 42, 46].includes(op)) regs[rt] = null;
      else if (op === 31) regs[rt] = null;
    }
    pc = next;
  }
}

const ctors = [...new Set(Object.values(cmd.borgs).map((b) => b.constructorAddress))].sort();
const byTable = new Map();
const unresolved = [];
for (const ctorHex of ctors) {
  const entry = parseInt(ctorHex, 16);
  const results = [];
  scanCtor(entry, 0, new Set(), results, []);
  const good = results.filter((r) => r.value !== null && r.value >= 0x80000000);
  const borgs = Object.values(cmd.borgs).filter((b) => b.constructorAddress === ctorHex).map((b) => b.id);
  const maxIdx = maxIdxByCtor.get(ctorHex) ?? -1;
  if (good.length === 0) {
    unresolved.push({ ctor: ctorHex, borgs, maxIdx, raw: results.length });
    continue;
  }
  // last store wins (ctor overrides base)
  const last = good[good.length - 1];
  const key = hex(last.value);
  const cur = byTable.get(key) ?? { ctors: [], borgs: [], maxIdx: -1, stores: new Set() };
  cur.ctors.push(ctorHex);
  cur.borgs.push(...borgs);
  cur.maxIdx = Math.max(cur.maxIdx, maxIdx);
  cur.stores.add(`${hex(last.pc)}${last.via.length ? " via " + last.via.join(">") : ""}`);
  if (good.length > 1) cur.multi = (cur.multi ?? 0) + 1;
  byTable.set(key, cur);
}

console.log("=== tables found:", byTable.size, " ctors resolved:", ctors.length - unresolved.length, "/", ctors.length);
for (const [table, v] of [...byTable.entries()].sort()) {
  console.log(`\ntable ${table}: maxDamageRecordIndex=${v.maxIdx} => >= ${v.maxIdx + 1} records`);
  console.log(`  ctors (${v.ctors.length}): ${v.ctors.join(", ")}`);
  console.log(`  borgs (${v.borgs.length}): ${v.borgs.slice(0, 20).join(",")}${v.borgs.length > 20 ? "..." : ""}`);
  console.log(`  store sites: ${[...v.stores].slice(0, 3).join("; ")}`);
}
console.log("\n=== unresolved ctors:", unresolved.length);
for (const u of unresolved) console.log(`  ${u.ctor} borgs=${u.borgs.join(",")} maxIdx=${u.maxIdx} rawStores=${u.raw}`);
