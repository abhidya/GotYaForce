#!/usr/bin/env node
// Q12 sweep (2026-10-20): classify every record of the per-borg hit-bin attack-region
// extraction (packages/combat/src/data/attackHitTables.json) by its activeEnd sentinel,
// cross-reference remap-kind usage, script-armed kinds (meleeAnimKinds.json), and resolved
// family damage values for the guide-claimed contact-damage borgs.
// Findings: research/decomp/contact-damage-q12-sweep-2026-10-20.md
// Window semantics (FUN_8008a65c, chunk_0013.c:1125-1249): activeEnd == -1 = persistent
// (no frame expiry, survives anim change); activeEnd == -2 = open-window (no frame expiry,
// dies on anim change); >= 0 = frame window.
import fs from "node:fs";
import path from "node:path";

const root = path.resolve(".");
const tables = JSON.parse(fs.readFileSync(path.join(root, "packages/combat/src/data/attackHitTables.json"), "utf8"));
const fam = JSON.parse(fs.readFileSync(path.join(root, "packages/combat/src/data/familyDamageRecords.json"), "utf8"));
const animKinds = JSON.parse(fs.readFileSync(path.join(root, "packages/combat/src/data/meleeAnimKinds.json"), "utf8"));

function dmgFor(borg, idx) {
  const binding = fam.borgs[borg];
  if (!binding) return null;
  return fam.tables[binding.tableAddress]?.records?.[idx] ?? null;
}

let total = 0;
const endHist = new Map();
let neg1 = 0, neg2 = 0, neg1Unreferenced = 0, neg1Bone0 = 0;
const kindRefs = { neg1: new Map(), neg2: new Map() };
for (const [borg, table] of Object.entries(tables.borgs)) {
  const used = new Set();
  for (const recIds of Object.values(table.kinds)) for (const rid of recIds) used.add(String(rid));
  for (const [rid, rec] of Object.entries(table.records)) {
    total++;
    endHist.set(rec.activeEnd, (endHist.get(rec.activeEnd) ?? 0) + 1);
    if (rec.activeEnd === -1 || rec.activeEnd === -2) {
      const m = rec.activeEnd === -1 ? kindRefs.neg1 : kindRefs.neg2;
      if (rec.activeEnd === -1) {
        neg1++;
        if (!used.has(rid)) neg1Unreferenced++;
        if (rec.boneIndex === 0) neg1Bone0++;
      } else neg2++;
      for (const [kind, recIds] of Object.entries(table.kinds)) {
        if (recIds.some((r) => String(r) === rid)) m.set(Number(kind), (m.get(Number(kind)) ?? 0) + 1);
      }
    }
  }
}
console.log(`borgs=${Object.keys(tables.borgs).length} records=${total}`);
console.log(`activeEnd==-1: ${neg1} (unreferenced: ${neg1Unreferenced}, bone0: ${neg1Bone0})`);
console.log(`activeEnd==-2: ${neg2}`);
const fmt = (m) => [...m.entries()].sort((a, b) => a[0] - b[0]).map(([k, v]) => `k${k}:${v}`).join(" ");
console.log(`-1 kind refs: ${fmt(kindRefs.neg1)}`);
console.log(`-2 kind refs: ${fmt(kindRefs.neg2)}`);

const claimed = ["pl0500", "pl050a", "pl0509", "pl0504", "pl050c", "pl0515", "pl0516", "pl0510", "pl0004"];
for (const borg of claimed) {
  const t = tables.borgs[borg];
  if (!t) continue;
  const values = new Set();
  for (const rec of Object.values(t.records)) {
    const d = dmgFor(borg, rec.damageRecordIndex);
    if (d?.hpDamage !== undefined) values.add(d.hpDamage);
  }
  console.log(
    `${borg}: scriptArmedKinds=${JSON.stringify(animKinds.borgs[borg]?.hitKinds ?? [])} ` +
    `resolvedDamageValues=${JSON.stringify([...values].sort((a, b) => a - b))} ` +
    `has22=${values.has(22)} has44=${values.has(44)}`,
  );
}
