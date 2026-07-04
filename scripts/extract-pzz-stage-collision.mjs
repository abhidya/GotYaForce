#!/usr/bin/env node
// Extract stage STIH collision from st##.pzz members for stages without loose hit files.
//
// Discovery (2026-07-04): the 22 stages listed as "no collision source" (st20+, st4x)
// were never missing — every stage .pzz carries its STIH hit layers as members 1..3
// (verified st20/st29/st4e: member payloads begin with the "STIH" magic). The stage
// exporter (scripts/export-all-stages.mjs copyRawStageAssets) only copied LOOSE
// afs root hit###.bin files, which exist for just 18 stages. This closes the gap to 40/40.

import fs from "node:fs";
import path from "node:path";
import { unpack as unpackPzz } from "../packages/formats/dist/pzz.js";

const repoRoot = path.resolve(".");
const rootDir = path.join(repoRoot, "user-data", "GG4E", "afs_data", "root");
const publicStages = path.join(repoRoot, "apps", "game", "public", "stages");

const STIH = Buffer.from("STIH", "latin1");
let stagesFixed = 0;
let filesWritten = 0;
const skipped = [];

for (const stageId of fs.readdirSync(publicStages).sort()) {
  const stageDir = path.join(publicStages, stageId);
  if (!fs.statSync(stageDir).isDirectory()) continue;
  const collisionDir = path.join(stageDir, "collision");
  const hasBins =
    fs.existsSync(collisionDir) && fs.readdirSync(collisionDir).some((f) => /^hit.*\.bin$/i.test(f));
  if (hasBins) continue;

  const pzzPath = path.join(rootDir, `${stageId}.pzz`);
  if (!fs.existsSync(pzzPath)) {
    skipped.push(`${stageId}: no ${stageId}.pzz`);
    continue;
  }
  const archive = unpackPzz(fs.readFileSync(pzzPath));
  const hits = archive.members.filter(
    (m) => m.payload.byteLength >= 4 && Buffer.from(m.payload.slice(0, 4)).equals(STIH),
  );
  if (hits.length === 0) {
    skipped.push(`${stageId}: pzz has no STIH members`);
    continue;
  }
  fs.mkdirSync(collisionDir, { recursive: true });
  hits.forEach((m, i) => {
    // Same naming convention as the loose exports (hit000/hit001/hit002 per stage code).
    const name = `hit${stageId.replace(/^st/, "")}${i}.bin`;
    fs.writeFileSync(path.join(collisionDir, name), Buffer.from(m.payload));
    filesWritten += 1;
  });
  stagesFixed += 1;
  console.log(`${stageId}: extracted ${hits.length} STIH layers from ${stageId}.pzz`);
}

console.log(`done: ${stagesFixed} stages fixed, ${filesWritten} hit bins written; skipped: ${skipped.join("; ") || "none"}`);
