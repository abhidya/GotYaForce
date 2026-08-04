#!/usr/bin/env node
// gen-bespoke-port-queue.mjs — Bespoke engine port-work-queue refresher.
//
// Re-fingerprints the bespoke port work queue against current TS source.
//
// METHODOLOGY (documented honestly):
//  - The phase-function INVENTORY (addresses, instruction lengths, family
//    groupings, phase-table structure, decomp chunk files) is the FROZEN
//    corpus fingerprint captured 2026-07-06 and stored in
//    research/tasks/bespoke-port-work-queue.json. The original generator
//    (referenced as scripts/.../classify_fleet + a fingerprinting driver in
//    bespoke-engine-port-plan.md) is NOT in the repo and never was (verified
//    via `git log --diff-filter=D` — zero deleted matches). The boot.dol PPC
//    disassembly pipeline it used to compute instruction-level fingerprints
//    ("immediates + branch targets masked") is therefore unreproducible here.
//  - This script reuses the frozen inventory verbatim (it is immutable: the
//    decomp corpus is unchanged) and recomputes ONLY the part that changed:
//    the "ported" detection, by harvesting phase-function address citations
//    from current TS source.
//  - Ported detection is AUGMENTED over the plan's "0x80xxxxxx literals"
//    prescription: ported family modules cite phase functions as `FUN_80xxxxxx`
//    and `zz_<hex>_` (Ghidra decompiler names) far more often than as bare hex.
//    All three citation forms are harvested, normalized to `0x80xxxxxx`, and
//    intersected with the inventory address set.
//  - Two counting units are reported: ADDRESS-level (exactly reproducible) and
//    C-BODY-FINGERPRINT shapes (reconstructed from the decomp C corpus; ~15%
//    more granular than the plan's PPC-instruction shapes). The plan's original
//    1161 PPC-shape count is unreproducible and only cited for reference.
//
// Inputs : research/tasks/bespoke-port-work-queue.json (frozen inventory)
//          research/tasks/bespoke-port-batches.json    (family→batch grouping)
//          research/decomp/ghidra-export/_index.tsv + chunk_*.c (decomp corpus)
//          packages/combat/src/families/*.ts (ported-address source of truth)
//          packages/combat/src/rom/*.ts, packages/combat/src/bridge.ts
// Outputs: research/tasks/bespoke-port-work-queue.json (refreshed `done` flags)
//          research/tasks/bespoke-port-batches.json    (refreshed counts)
//          stdout report (headline numbers)
//
// Re-run : node scripts/gen-bespoke-port-queue.mjs

import fs from "node:fs";
import path from "node:path";
import { execSync } from "node:child_process";

const ROOT = "D:/GotYaForce";
const Q_PATH = `${ROOT}/research/tasks/bespoke-port-work-queue.json`;
const B_PATH = `${ROOT}/research/tasks/bespoke-port-batches.json`;
const IDX_PATH = `${ROOT}/research/decomp/ghidra-export/_index.tsv`;
const CHUNK_DIR = `${ROOT}/research/decomp/ghidra-export`;
const TS_DIRS = [`${ROOT}/packages/combat/src/families`, `${ROOT}/packages/combat/src/rom`];
const TS_EXTRA = [`${ROOT}/packages/combat/src/bridge.ts`];

// ---------- 1. Load frozen inventory ----------
// The work-queue JSON is BOTH the inventory source AND the output we refresh.
// To stay idempotent across re-runs, the OLD (2026-07-06) `done` baseline is
// read from the git-committed version (HEAD); the working-tree inventory
// (addresses/lens/families/tables) is identical to HEAD for those fields.
const queue = JSON.parse(fs.readFileSync(Q_PATH, "utf8"));
const batchesOld = JSON.parse(fs.readFileSync(B_PATH, "utf8"));
let queueBaseline;
try {
  const headJson = execSync("git -C \"" + ROOT + "\" show HEAD:" +
    "research/tasks/bespoke-port-work-queue.json", { maxBuffer: 1 << 26 }).toString("utf8");
  queueBaseline = JSON.parse(headJson);
} catch {
  // not a git repo or file untracked: fall back to working tree
  queueBaseline = queue;
}
const baselineDone = new Set(); // addr -> done (from committed 2026-07-06 flags)
for (const fam of queueBaseline) for (const t of fam.detail) for (const f of t.fns) {
  if (f.done) baselineDone.add(f.fn.toLowerCase());
}

// distinct address -> instruction length (first occurrence wins; lengths are
// stable per address across the inventory)
const addrLen = new Map();
for (const fam of queue) for (const t of fam.detail) for (const f of t.fns) {
  if (!addrLen.has(f.fn)) addrLen.set(f.fn, f.len);
}
const ALL_ADDRS = new Set(addrLen.keys());

// ---------- 2. Harvest ported addresses from current TS ----------
const RE_HEX = /\b0x(80[0-9a-fA-F]{6})\b/g;
const RE_FUN = /\bFUN_(80[0-9a-fA-F]{6})\b/g;
const RE_ZZ = /\bzz_0*([0-9a-fA-F]{6,7})_/g;
const cited = new Set();
function note(hex8) { cited.add("0x" + hex8.toLowerCase()); }
function scanText(txt) {
  let m;
  while ((m = RE_HEX.exec(txt))) note(m[1]);
  while ((m = RE_FUN.exec(txt))) note(m[1]);
  while ((m = RE_ZZ.exec(txt))) {
    const d = m[1].toLowerCase();
    if (d.length === 7) note("80" + d.slice(1)); // drop leading 0 -> 6 digits
    else if (d.length === 6) note("80" + d);
  }
}
let scannedFiles = 0;
for (const d of TS_DIRS) {
  if (!fs.existsSync(d)) continue;
  for (const f of fs.readdirSync(d)) {
    if (!f.endsWith(".ts")) continue;
    scannedFiles++;
    scanText(fs.readFileSync(path.join(d, f), "utf8"));
  }
}
for (const f of TS_EXTRA) if (fs.existsSync(f)) { scannedFiles++; scanText(fs.readFileSync(f, "utf8")); }

// PRIMARY ported detection = cited phase-function addresses. Calibrated
// against the slot-level audit (family-state-machine-classifications.reviewed:
// ported=191/partial=132): address-only yields 227 fully-ported phase tables,
// the closest match. (A broader "phase-table citation" rule was tested and
// rejected: it marks every fn in any cited table as ported and overshoots to
// 354 full tables vs the audit's 191 — many table addresses are cited in
// documentary comments for fallback/shared paths, not bespoke porting. It is
// still computed below as an OPTIMISTIC UPPER BOUND for transparency.)
const portedAddrs = new Set();
for (const a of ALL_ADDRS) if (cited.has(a)) portedAddrs.add(a);
const isPorted = (a) => portedAddrs.has(a);

// OPTIMISTIC variant: address citation + whole-table citation.
const portedAddrsOpt = new Set(portedAddrs);
let optTablesCited = 0;
for (const fam of queue) for (const t of fam.detail) {
  if (cited.has(t.table.toLowerCase())) {
    optTablesCited++;
    for (const f of t.fns) portedAddrsOpt.add(f.fn.toLowerCase());
  }
}

// ---------- 3. C-body fingerprint shapes (reconstructed) ----------
const idxLines = fs.readFileSync(IDX_PATH, "utf8").split(/\r?\n/);
const idx = new Map(); // 8hex(no 0x) -> {name,chunk}
for (const line of idxLines) {
  if (!line.trim()) continue;
  const [addr, name, chunk] = line.split("\t");
  if (addr && chunk) idx.set(addr.toLowerCase(), { name: name || "", chunk });
}
const chunkCache = new Map();
const chunkBodies = new Map(); // chunk -> Map(8hex -> bodyText)
function bodiesForChunk(c) {
  if (chunkBodies.has(c)) return chunkBodies.get(c);
  let txt;
  try { txt = fs.readFileSync(`${CHUNK_DIR}/${c}`, "utf8"); }
  catch { chunkBodies.set(c, new Map()); return chunkBodies.get(c); }
  const map = new Map();
  const parts = txt.split(/\r?\n\/\/ ==== ([0-9a-f]{8})\s+/);
  for (let i = 1; i < parts.length; i += 2) map.set(parts[i].toLowerCase(), parts[i + 1] || "");
  chunkBodies.set(c, map);
  return map;
}
function fp(body) {
  let s = body
    .replace(/\bFUN_[0-9a-f]{8}/g, "FN")
    .replace(/\bzz_[0-9a-f]+_/g, "ZZ")
    .replace(/\b(?:DOUBLE|FLOAT|PTR|LAB|switchD|UNIQUE)[_0-9a-fA-Fx]+/g, "MEM")
    .replace(/\b0x[0-9a-fA-F]+\b/g, "H")
    .replace(/\b\d+\b/g, "D");
  return s.toLowerCase().replace(/\s+/g, " ").trim();
}
const addrShape = new Map(); // addr -> shapeId (for addresses we can fingerprint)
let fpMissing = 0;
for (const a of ALL_ADDRS) {
  const rec = idx.get(a.replace(/^0x/, ""));
  if (!rec) { fpMissing++; continue; }
  const body = bodiesForChunk(rec.chunk).get(a.replace(/^0x/, ""));
  if (body == null) { fpMissing++; continue; }
  addrShape.set(a, fp(body));
}
const shapeOf = (a) => addrShape.get(a) || `__NOSHAPE__:${a}`; // missing -> singleton

// shape ported: a shape is ported if ANY of its addresses is ported
const allShapes = new Set();
for (const a of ALL_ADDRS) allShapes.add(shapeOf(a));
const portedShapes = new Set();
for (const a of ALL_ADDRS) if (isPorted(a)) portedShapes.add(shapeOf(a));

// ---------- 4. OLD ported set (frozen 2026-07-06 done flags, from git HEAD) ----------
const oldPortedAddrs = new Set(baselineDone);
const oldIsPorted = (a) => oldPortedAddrs.has(a);
const oldPortedShapes = new Set();
for (const a of ALL_ADDRS) if (oldIsPorted(a)) oldPortedShapes.add(shapeOf(a));

// ---------- 5. Headline numbers ----------
function headline(portedSet, portedShapeSet) {
  const unportedAddrs = ALL_ADDRS.size - portedSet.size;
  let unportedInstr = 0;
  for (const a of ALL_ADDRS) if (!portedSet.has(a)) unportedInstr += addrLen.get(a);
  const unportedShapes = allShapes.size - portedShapeSet.size;
  return { totalAddrs: ALL_ADDRS.size, portedAddrs: portedSet.size, unportedAddrs, unportedInstr, totalShapes: allShapes.size, portedShapes: portedShapeSet.size, unportedShapes };
}
const OLD = headline(oldPortedAddrs, oldPortedShapes);
const NEW = headline(portedAddrs, portedShapes);
// optimistic upper bound (address + table citation)
const optPortedShapes = new Set();
for (const a of ALL_ADDRS) if (portedAddrsOpt.has(a)) optPortedShapes.add(shapeOf(a));
const OPT = headline(portedAddrsOpt, optPortedShapes);

// ---------- 6. Phase-table coverage (slot reconciliation proxy) ----------
function tableCoverageFor(portedSet) {
  let full = 0, partial = 0, untouched = 0, empty = 0;
  for (const fam of queue) for (const t of fam.detail) {
    if (!t.fns.length) { empty++; continue; }
    let dn = 0;
    for (const f of t.fns) if (portedSet.has(f.fn.toLowerCase())) dn++;
    if (dn === 0) untouched++;
    else if (dn === t.fns.length) full++;
    else partial++;
  }
  return { full, partial, untouched, empty };
}
const TAB_OLD = tableCoverageFor(oldPortedAddrs);
const TAB_NEW = tableCoverageFor(portedAddrs);

// ---------- 7. Per-family ranking by unported instructions ----------
const famDebt = [];
for (const fam of queue) {
  let ua = 0, ui = 0;
  const seen = new Set();
  for (const t of fam.detail) for (const f of t.fns) {
    if (seen.has(f.fn)) continue; seen.add(f.fn);
    if (!isPorted(f.fn)) { ua++; ui += f.len; }
  }
  famDebt.push({ label: fam.label, unportedAddrs: ua, unportedInstrs: ui });
}
famDebt.sort((a, b) => b.unportedInstrs - a.unportedInstrs);

// ---------- 8. Refresh work-queue JSON (flip `done`, recompute per-family) ----------
const portedAddrsLower = new Set([...portedAddrs].map((a) => a.toLowerCase()));
for (const fam of queue) {
  const seenP = new Set(), seenU = new Set();
  for (const t of fam.detail) {
    for (const f of t.fns) {
      f.done = portedAddrsLower.has(f.fn.toLowerCase());
    }
  }
  for (const t of fam.detail) for (const f of t.fns) {
    if (f.done) seenP.add(f.fn.toLowerCase()); else seenU.add(f.fn.toLowerCase());
  }
  fam.portedFnCount = seenP.size;
  fam.unportedFnCount = seenU.size;
  fam.unportedInstrs = 0;
  const seenLen = new Set();
  for (const t of fam.detail) for (const f of t.fns) {
    if (f.done) continue;
    if (seenLen.has(f.fn)) continue; seenLen.add(f.fn);
    fam.unportedInstrs += f.len;
  }
}

// ---------- 9. Refresh batches JSON (borg labels -> families -> unported union) ----------
const borgToFam = new Map();
for (const f of queue) for (const b of f.borgs) if (!borgToFam.has(b)) borgToFam.set(b, f.label);
const famByName = new Map(queue.map((f) => [f.label, f]));
const batchesNew = batchesOld.map((b) => {
  const famSet = new Set();
  for (const lbl of b.labels) { const fl = borgToFam.get(lbl); if (fl) famSet.add(fl); }
  const union = new Set();
  for (const fl of famSet) {
    const fam = famByName.get(fl);
    if (!fam) continue;
    for (const t of fam.detail) for (const f of t.fns) if (!isPorted(f.fn)) union.add(f.fn);
  }
  let instrs = 0;
  for (const a of union) instrs += addrLen.get(a) || 0;
  return { labels: b.labels, borgCount: b.borgCount, shapeCount: union.size, instrs };
});

// ---------- 10. Write outputs (LF, 1-space indent to match original) ----------
const oldQ = fs.readFileSync(Q_PATH, "utf8");
fs.writeFileSync(Q_PATH, JSON.stringify(queue, null, 1).replace(/\r?\n/g, "\n") + "\n", "utf8");
fs.writeFileSync(B_PATH, JSON.stringify(batchesNew, null, 1).replace(/\r?\n/g, "\n") + "\n", "utf8");

// ---------- 11. Report ----------
const retired = batchesNew.filter((b) => b.shapeCount === 0);
const retiredNames = retired.map((b) => b.labels.join(" / "));

const rpt = [];
rpt.push("=== BESPOKE PORT QUEUE REFRESH ===");
rpt.push(`scanned TS files: ${scannedFiles} | cited 0x80xxxxxx addrs: ${cited.size} | inventory fns detected ported: ${portedAddrs.size}`);
rpt.push(`C-fingerprint bodies found: ${ALL_ADDRS.size - fpMissing}/${ALL_ADDRS.size} (missing ${fpMissing} → singleton shapes)`);
rpt.push("");
rpt.push("--- HEADLINE (address-level, exactly reproducible) ---");
rpt.push(`                        OLD(2026-07-06)    NEW(2026-08-03)    DELTA`);
rpt.push(`total addresses         ${String(OLD.totalAddrs).padStart(10)}        ${String(NEW.totalAddrs).padStart(10)}        ${String(NEW.totalAddrs-OLD.totalAddrs).padStart(8)}`);
rpt.push(`ported addresses        ${String(OLD.portedAddrs).padStart(10)}        ${String(NEW.portedAddrs).padStart(10)}        ${String(NEW.portedAddrs-OLD.portedAddrs).padStart(8)}`);
rpt.push(`unported addresses      ${String(OLD.unportedAddrs).padStart(10)}        ${String(NEW.unportedAddrs).padStart(10)}        ${String(NEW.unportedAddrs-OLD.unportedAddrs).padStart(8)}`);
rpt.push(`unported instructions   ${String(OLD.unportedInstr).padStart(10)}        ${String(NEW.unportedInstr).padStart(10)}        ${String(NEW.unportedInstr-OLD.unportedInstr).padStart(8)}`);
rpt.push("");
rpt.push("--- HEADLINE (C-body-fingerprint shapes; reconstructed) ---");
rpt.push(`total shapes (C-fp)     ${String(OLD.totalShapes).padStart(10)}        ${String(NEW.totalShapes).padStart(10)}        (plan's PPC unit: 1161)`);
rpt.push(`ported shapes (C-fp)    ${String(OLD.portedShapes).padStart(10)}        ${String(NEW.portedShapes).padStart(10)}`);
rpt.push(`unported shapes (C-fp)  ${String(OLD.unportedShapes).padStart(10)}        ${String(NEW.unportedShapes).padStart(10)}        (plan's PPC unit: 1123)`);
rpt.push("");
rpt.push("--- OPTIMISTIC UPPER BOUND (address + phase-table citation; over-claims) ---");
rpt.push(`ported addrs=${OPT.portedAddrs} unported addrs=${OPT.unportedAddrs} unported instrs=${OPT.unportedInstr} | tables-cited=${optTablesCited}`);
rpt.push(`(rejected as primary: yields ${tableCoverageFor(portedAddrsOpt).full} fully-ported tables vs audit's 191 full slots)`);
rpt.push("");
rpt.push("--- SLOT RECONCILIATION (phase-table coverage proxy) ---");
rpt.push(`tables fully ported : OLD ${TAB_OLD.full}  NEW ${TAB_NEW.full}`);
rpt.push(`tables partial      : OLD ${TAB_OLD.partial}  NEW ${TAB_NEW.partial}`);
rpt.push(`tables untouched    : OLD ${TAB_OLD.untouched}  NEW ${TAB_NEW.untouched}`);
rpt.push(`audit slot overlay  : ported=191 partial=132 missing=2 (family-state-machine-classifications.reviewed.json)`);
rpt.push("");
rpt.push("--- TOP-10 FAMILIES BY UNPORTED INSTRUCTIONS (new) ---");
famDebt.slice(0, 10).forEach((f, i) => rpt.push(`${String(i + 1).padStart(2)}. ${f.label.padEnd(26)} addrs=${String(f.unportedAddrs).padStart(4)} instrs=${String(f.unportedInstrs).padStart(6)}`));
rpt.push("");
rpt.push("--- BATCHES NOW FULLY RETIRED (unported addr-union == 0) ---");
rpt.push(`count: ${retired.length}`);
retired.forEach((b, i) => rpt.push(`  ${String(i + 1).padStart(2)}. ${b.labels.join(" / ")}  (was ${batchesOld.find(o=>o.labels.join()===b.labels.join())?.shapeCount} shapes)  borgs=${b.borgCount}`));
rpt.push("");
rpt.push(`batches total: ${batchesNew.length} | retired: ${retired.length} | remaining: ${batchesNew.length - retired.length}`);
console.log(rpt.join("\n"));
