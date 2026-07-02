#!/usr/bin/env node
// Inspect candidate jump-related bytes (0x09f, 0x1a1..0x1a3, 0x180..0x183) grouped by
// borgs.json jump category, to characterize behavior outside the air-jump subdomain.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const roots = [
  path.join(repoRoot, "user-data", "GG4E", "afs_data", "root"),
  "D:\\GotYaForce\\user-data\\GG4E\\afs_data\\root",
];
const assetRoot = roots.find((p) => fs.existsSync(p));
const borgs = JSON.parse(
  fs.readFileSync(path.join(repoRoot, "packages", "assets", "data", "borgs.json"), "utf8"),
).borgs;
const byId = new Map(borgs.map((b) => [b.id.toLowerCase(), b]));

const files = fs
  .readdirSync(assetRoot)
  .filter((n) => /^pl[0-9a-f]{4}data\.bin$/i.test(n))
  .sort();

const groups = new Map();
for (const name of files) {
  const buf = fs.readFileSync(path.join(assetRoot, name));
  if (buf.length !== 432) continue;
  const id = name.slice(0, 6).toLowerCase();
  const m = byId.get(id);
  const jump = m ? String(m.jump).trim().toLowerCase() : "(no metadata)";
  const key = jump;
  if (!groups.has(key)) groups.set(key, []);
  groups.get(key).push({
    id,
    b09f: buf.readUInt8(0x9f),
    b09e: buf.readUInt8(0x9e),
    b1a1: buf.readUInt8(0x1a1),
    b1a2: buf.readUInt8(0x1a2),
    b1a3: buf.readUInt8(0x1a3),
    u180: buf.readUInt32BE(0x180).toString(16),
    b183: buf.readUInt8(0x183),
  });
}

for (const [jump, rows] of groups) {
  console.log(`\n== jump="${jump}" (${rows.length}) ==`);
  const summar = (k) => {
    const c = new Map();
    for (const r of rows) c.set(r[k], (c.get(r[k]) ?? 0) + 1);
    return [...c.entries()].map(([v, n]) => `${v}x${n}`).join(" ");
  };
  for (const k of ["b09e", "b09f", "b1a1", "b1a2", "b1a3", "b183"]) {
    console.log(`  ${k}: ${summar(k)}`);
  }
}
