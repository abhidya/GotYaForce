#!/usr/bin/env node
// Quick probe: dump a given f32be/u8/u16be column vs borgs.json ground truth.
// Usage: node scripts/probe-pl-offset.mjs <hexOffset> <enc>
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

const off = parseInt(process.argv[2], 16);
const enc = process.argv[3] ?? "f32be";

const files = fs
  .readdirSync(assetRoot)
  .filter((n) => /^pl[0-9a-f]{4}data\.bin$/i.test(n))
  .sort();

for (const name of files) {
  const buf = fs.readFileSync(path.join(assetRoot, name));
  if (buf.length !== 432) continue;
  const id = name.slice(0, 6).toLowerCase();
  const m = byId.get(id);
  let v;
  if (enc === "f32be") v = buf.readFloatBE(off);
  else if (enc === "u16be") v = buf.readUInt16BE(off);
  else if (enc === "u32be") v = buf.readUInt32BE(off);
  else v = buf.readUInt8(off);
  const hp = m?.hp ?? "?";
  console.log(
    `${id} v=${v} hp=${hp} energy=${m?.energy ?? "?"} def=${m?.defense ?? "?"} spd=${m?.speed ?? "?"} name=${m?.name ?? "?"}`,
  );
}
