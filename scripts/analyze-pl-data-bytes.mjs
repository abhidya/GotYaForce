#!/usr/bin/env node
// Correlation analysis over the 432-byte pl####data.bin actor-data records.
//
// Goal: find MORE byte offsets whose meaning can be PROVEN by exact cross-check
// against independent per-borg metadata (borgs.json + research/symbols/NTSC_Borgs.csv),
// using the same zero-exception standard as scripts/gen-borg-actor-data-stats.mjs.
//
// Output: report to stdout. Proof bar:
//   - numeric field: exact equality or exact affine map (col = a*gt + b) across ALL
//     borgs that have both an actor-data record and metadata, with the ground-truth
//     column taking >= 4 distinct values (rejects degenerate fits).
//   - categorical field: column constant within category AND distinct across
//     categories (a bijective enum encoding), across ALL matched borgs.
// Anything weaker is reported under LEADS and must not be wired into the port.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = "GG4E";
const assetRootCandidates = [
  path.join(repoRoot, "user-data", region, "afs_data", "root"),
  path.join("D:\\GotYaForce", "user-data", region, "afs_data", "root"),
];
const assetRoot = assetRootCandidates.find((p) => fs.existsSync(p));
if (!assetRoot) throw new Error("no user-data asset root found");
const borgsPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const csvPath = path.join(repoRoot, "research", "symbols", "NTSC_Borgs.csv");

const RECORD_SIZE = 432;

// ---------------------------------------------------------------- ground truth

function parseCsvLine(line) {
  // naive CSV: the file uses quotes around fields containing commas
  const out = [];
  let cur = "";
  let inQ = false;
  for (const ch of line) {
    if (inQ) {
      if (ch === '"') inQ = false;
      else cur += ch;
    } else if (ch === '"') inQ = true;
    else if (ch === ",") {
      out.push(cur);
      cur = "";
    } else cur += ch;
  }
  out.push(cur);
  return out;
}

function loadCsv() {
  const lines = fs.readFileSync(csvPath, "utf8").split(/\r?\n/).filter((l) => l.trim() !== "");
  const header = parseCsvLine(lines[0]);
  const rows = lines.slice(1).map((l) => {
    const cells = parseCsvLine(l);
    const row = {};
    header.forEach((h, i) => (row[h] = cells[i] ?? ""));
    return row;
  });
  return rows;
}

const borgs = JSON.parse(fs.readFileSync(borgsPath, "utf8")).borgs ?? [];
const borgById = new Map(borgs.map((b) => [String(b.id).toLowerCase(), b]));
const csvById = new Map(loadCsv().map((r) => [String(r.filename).trim().toLowerCase(), r]));

// ---------------------------------------------------------------- records

const files = fs
  .readdirSync(assetRoot)
  .filter((n) => /^pl[0-9a-f]{4}data\.bin$/i.test(n))
  .sort();

const records = [];
for (const name of files) {
  const buf = fs.readFileSync(path.join(assetRoot, name));
  if (buf.length !== RECORD_SIZE) continue;
  const id = name.slice(0, 6).toLowerCase();
  records.push({ id, buf, meta: borgById.get(id), csv: csvById.get(id) });
}
const withMeta = records.filter((r) => r.meta);
const withCsv = records.filter((r) => r.csv);
console.log(`records=${records.length} withBorgsJson=${withMeta.length} withCsv=${withCsv.length}`);

// ---------------------------------------------------------------- ground-truth columns

function hpParts(hp) {
  const m = /^(\d+)\s*\/\s*(\d+)$/.exec(String(hp ?? "").trim());
  return m ? [Number(m[1]), Number(m[2])] : [null, null];
}

// numeric ground truth: id -> number (null = unavailable for that borg)
const numericGT = {
  energy: (r) => r.meta?.energy ?? null,
  number: (r) => r.meta?.number ?? null,
  hpL1: (r) => hpParts(r.meta?.hp)[0],
  hpL10: (r) => hpParts(r.meta?.hp)[1],
  crystals: (r) => {
    const v = r.csv?.["Data Crystals Required"];
    return v != null && /^\d+$/.test(String(v).trim()) ? Number(v) : null;
  },
  defense: (r) => r.meta?.defense ?? null,
  shot: (r) => r.meta?.shot ?? null,
  attack: (r) => r.meta?.attack ?? null,
  speed: (r) => r.meta?.speed ?? null,
  // subdomain field: only defined for borgs whose jump is "air jump level N".
  // a hit is proven only for that subdomain and must be documented as such.
  airJumpLevel: (r) => {
    const m = /^air jump level\s*(\d+)$/i.exec(String(r.meta?.jump ?? "").trim());
    return m ? Number(m[1]) : null;
  },
};

const norm = (v) => (v == null ? null : String(v).trim().toLowerCase());

const categoricalGT = {
  rarity: (r) => norm(r.meta?.rarity),
  tribe: (r) => norm(r.meta?.tribe),
  type: (r) => norm(r.meta?.type),
  jump: (r) => norm(r.meta?.jump),
  schedule: (r) => {
    const v = r.csv?.["Level-up Schedule"];
    return v ? String(v).trim().toLowerCase() : null;
  },
};

// ---------------------------------------------------------------- encodings

function* columns() {
  for (let off = 0; off < RECORD_SIZE; off += 1) {
    yield { enc: "u8", off, read: (b) => b.readUInt8(off) };
  }
  for (let off = 0; off + 2 <= RECORD_SIZE; off += 2) {
    yield { enc: "u16be", off, read: (b) => b.readUInt16BE(off) };
    yield { enc: "s16be", off, read: (b) => b.readInt16BE(off) };
  }
  for (let off = 0; off + 4 <= RECORD_SIZE; off += 4) {
    yield { enc: "u32be", off, read: (b) => b.readUInt32BE(off) };
    yield { enc: "f32be", off, read: (b) => b.readFloatBE(off) };
  }
}

function hex(v) {
  return `0x${v.toString(16).padStart(3, "0")}`;
}

// ---------------------------------------------------------------- tests

function distinctCount(values) {
  return new Set(values).size;
}

// exact affine fit col = a*gt + b over pairs; returns {a,b} or null
// integer encodings use a near-exact absolute tolerance; float encodings use a
// relative tolerance (columns are pre-filtered to plausible magnitudes).
function affineFit(pairs, isFloat) {
  // find two points with distinct gt
  let p0 = null;
  let p1 = null;
  for (const p of pairs) {
    if (!p0) p0 = p;
    else if (p.gt !== p0.gt) {
      p1 = p;
      break;
    }
  }
  if (!p0 || !p1) return null;
  const a = (p1.col - p0.col) / (p1.gt - p0.gt);
  const b = p0.col - a * p0.gt;
  if (a === 0) return null;
  for (const p of pairs) {
    const pred = a * p.gt + b;
    const tol = isFloat ? Math.max(Math.abs(p.col), Math.abs(pred), 1) * 1e-6 : 1e-3;
    if (Math.abs(p.col - pred) > tol) return null;
  }
  return { a, b };
}

const proven = [];
const leads = [];

for (const col of columns()) {
  // read column once, guard NaN for f32
  const vals = new Map(); // id -> value
  let bad = false;
  for (const r of records) {
    const v = col.read(r.buf);
    if (typeof v !== "number" || Number.isNaN(v)) {
      bad = true;
      break;
    }
    // f32 columns must hold plausible values everywhere, otherwise the offset is
    // not a float field and denormal garbage would defeat any tolerance check.
    if (col.enc === "f32be" && !(Number.isFinite(v) && (v === 0 || (Math.abs(v) >= 1e-4 && Math.abs(v) <= 1e6)))) {
      bad = true;
      break;
    }
    vals.set(r.id, v);
  }
  if (bad) continue;
  const allVals = [...vals.values()];
  if (distinctCount(allVals) < 2) continue; // constant column, useless

  // numeric tests
  for (const [name, get] of Object.entries(numericGT)) {
    const pairs = [];
    for (const r of records) {
      const gt = get(r);
      if (gt == null) continue;
      pairs.push({ id: r.id, gt, col: vals.get(r.id) });
    }
    if (pairs.length < 50) continue;
    const gtDistinct = distinctCount(pairs.map((p) => p.gt));
    if (gtDistinct < (name === "airJumpLevel" ? 3 : 4)) continue;
    const fit = affineFit(pairs, col.enc === "f32be");
    if (fit) {
      proven.push({
        kind: "numeric",
        field: name,
        enc: col.enc,
        offset: hex(col.off),
        a: fit.a,
        b: fit.b,
        n: pairs.length,
        gtDistinct,
      });
    } else {
      // lead: monotone rank correlation? keep it cheap: exact-match fraction
      const eq = pairs.filter((p) => p.col === p.gt).length;
      if (eq / pairs.length >= 0.9) {
        leads.push({
          kind: "numeric-near",
          field: name,
          enc: col.enc,
          offset: hex(col.off),
          equalFrac: +(eq / pairs.length).toFixed(3),
          n: pairs.length,
          mismatchIds: pairs.filter((p) => p.col !== p.gt).slice(0, 6).map((p) => `${p.id}(gt=${p.gt},col=${p.col})`),
        });
      }
    }
  }

  // categorical tests (u8/u16/u32 only; float enums unlikely but harmless to skip)
  if (col.enc === "f32be") continue;
  for (const [name, get] of Object.entries(categoricalGT)) {
    const byCat = new Map();
    let n = 0;
    for (const r of records) {
      const cat = get(r);
      if (cat == null) continue;
      n += 1;
      const v = vals.get(r.id);
      if (!byCat.has(cat)) byCat.set(cat, new Set());
      byCat.get(cat).add(v);
    }
    if (n < 50 || byCat.size < 3) continue;
    const constantWithin = [...byCat.values()].every((s) => s.size === 1);
    if (!constantWithin) continue;
    const catVals = [...byCat.values()].map((s) => [...s][0]);
    const distinctAcross = distinctCount(catVals) === catVals.length;
    const entry = {
      kind: "categorical",
      field: name,
      enc: col.enc,
      offset: hex(col.off),
      categories: byCat.size,
      bijective: distinctAcross,
      map: Object.fromEntries([...byCat.entries()].map(([k, s]) => [k, [...s][0]])),
      n,
    };
    if (distinctAcross) proven.push(entry);
    // a lead is only interesting if categories actually separate into >1 value
    else if (distinctCount(catVals) > 1) leads.push(entry);
  }
}

// dedupe: a u8 hit inside a u16/u32 hit shows up multiple times; keep all, report sorted
proven.sort((x, y) => parseInt(x.offset, 16) - parseInt(y.offset, 16));
leads.sort((x, y) => parseInt(x.offset, 16) - parseInt(y.offset, 16));

console.log("\n=== PROVEN (exact across all matched borgs) ===");
console.log(JSON.stringify(proven, null, 2));
console.log("\n=== LEADS (NOT derived; do not wire) ===");
console.log(JSON.stringify(leads, null, 2));

// ---------------------------------------------------------------- structure survey

let constant = 0;
const constBytes = [];
for (let off = 0; off < RECORD_SIZE; off += 1) {
  const s = new Set(records.map((r) => r.buf.readUInt8(off)));
  if (s.size === 1) {
    constant += 1;
    constBytes.push(off);
  }
}
console.log(`\nconstant u8 columns: ${constant}/${RECORD_SIZE}`);

// plausible f32be columns (all finite, |v| in [1e-4, 1e5] or 0) — candidates for physics params
const floatCols = [];
for (let off = 0; off + 4 <= RECORD_SIZE; off += 4) {
  let ok = true;
  const vs = [];
  for (const r of records) {
    const v = r.buf.readFloatBE(off);
    if (!Number.isFinite(v) || (v !== 0 && (Math.abs(v) < 1e-4 || Math.abs(v) > 1e5))) {
      ok = false;
      break;
    }
    vs.push(v);
  }
  if (ok && new Set(vs).size > 1) {
    const min = Math.min(...vs);
    const max = Math.max(...vs);
    floatCols.push({ offset: hex(off), min: +min.toFixed(4), max: +max.toFixed(4), distinct: new Set(vs).size });
  }
}
console.log(`\nplausible varying f32be columns (${floatCols.length}):`);
console.log(JSON.stringify(floatCols, null, 2));
