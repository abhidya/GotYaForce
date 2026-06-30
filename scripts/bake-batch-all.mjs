#!/usr/bin/env node
// Batch driver: bake EVERY pl****mot.bin borg via bake-all-borg-anims.mjs.
// Skips the 5 already-fully-baked borgs. Logs parse failures and borgs missing
// a mot.bin. Writes a summary JSON to scratchpad.
import fs from "node:fs";
import path from "node:path";
import { spawnSync } from "node:child_process";

const region = "GG4E";
const repoRoot = path.resolve(".");
const nodeExe = path.join(repoRoot, "tools", "node", "node.exe");
const driver = path.join(repoRoot, "scripts", "bake-all-borg-anims.mjs");
const rootDir = path.join(repoRoot, "user-data", region, "afs_data", "root");
const modelsDir = path.join(repoRoot, "apps", "game", "public", "models");

const alreadyDone = new Set(["pl0615", "pl0102", "pl0802", "pl0500", "pl0109"]);

// all pl****mot.bin (exclude dm/dp etc.)
const motBorgs = fs.readdirSync(rootDir)
  .filter((f) => /^pl[0-9a-f]+mot\.bin$/i.test(f))
  .map((f) => f.replace(/mot\.bin$/i, "").toLowerCase())
  .sort();

// borgs that have a model but NO mot.bin -> need shared fallback
const modelBorgs = new Set(
  fs.readdirSync(rootDir)
    .filter((f) => /^pl[0-9a-f]+_mdl\.arc$/i.test(f))
    .map((f) => f.replace(/_mdl\.arc$/i, "").toLowerCase()),
);
const noMot = [...modelBorgs].filter((b) => !motBorgs.includes(b)).sort();

const results = [];
const failures = [];
const coreSlots = [
  ["idle", 0, 0], ["move", 0, 1], ["dash", 0, 2],
  ["attack", 1, null], ["hit", 3, 1], ["down", 4, 0],
  ["death", 5, 1], ["victory", 5, 2],
];

let i = 0;
for (const borg of motBorgs) {
  i++;
  if (alreadyDone.has(borg)) {
    const idxPath = path.join(modelsDir, borg, "anim_index.json");
    let n = 0;
    try { n = JSON.parse(fs.readFileSync(idxPath, "utf8")).bankCount; } catch {}
    results.push({ borg, clips: n, status: "already-done" });
    console.log(`[${i}/${motBorgs.length}] ${borg}: SKIP (already done, ${n} clips)`);
    continue;
  }
  const r = spawnSync(nodeExe, [driver, borg, region], {
    cwd: repoRoot, encoding: "utf8", maxBuffer: 64 * 1024 * 1024,
  });
  const idxPath = path.join(modelsDir, borg, "anim_index.json");
  if ((r.status ?? 1) !== 0 || !fs.existsSync(idxPath)) {
    failures.push({ borg, code: r.status, err: (r.stderr || r.stdout || "").slice(-400) });
    console.error(`[${i}/${motBorgs.length}] ${borg}: FAILED (${r.status})`);
    continue;
  }
  const idx = JSON.parse(fs.readFileSync(idxPath, "utf8"));
  // verify which core slots are present
  const present = {};
  for (const [name, g, s] of coreSlots) {
    if (s === null) present[name] = idx.banks.some((b) => b.group === g);
    else present[name] = idx.banks.some((b) => b.group === g && b.slot === s);
  }
  const missingCore = Object.entries(present).filter(([, v]) => !v).map(([k]) => k);
  results.push({ borg, clips: idx.bankCount, status: "baked", present, missingCore });
  console.log(`[${i}/${motBorgs.length}] ${borg}: baked ${idx.bankCount} clips` +
    (missingCore.length ? ` (missing core: ${missingCore.join(",")})` : ""));
}

const summary = {
  region,
  totalMotBorgs: motBorgs.length,
  alreadyDone: [...alreadyDone],
  bakedThisRun: results.filter((r) => r.status === "baked").length,
  totalClipsThisRun: results.filter((r) => r.status === "baked").reduce((a, r) => a + r.clips, 0),
  totalClipsAll: results.reduce((a, r) => a + (r.clips || 0), 0),
  failures,
  noMot,
  results,
};
const outFile = path.join(
  "C:", "Users", "manny", "AppData", "Local", "Temp", "claude",
  "D--GotYaForce", "822776cd-587a-4427-904d-05ebb3888f96", "scratchpad",
  "bake-summary.json",
);
fs.mkdirSync(path.dirname(outFile), { recursive: true });
fs.writeFileSync(outFile, JSON.stringify(summary, null, 2));

console.log("\n========== SUMMARY ==========");
console.log(`mot borgs: ${motBorgs.length}; already-done: ${alreadyDone.size}; baked this run: ${summary.bakedThisRun}`);
console.log(`clips this run: ${summary.totalClipsThisRun}; clips all baked: ${summary.totalClipsAll}`);
console.log(`failures: ${failures.length} -> ${failures.map((f) => f.borg).join(", ")}`);
console.log(`borgs with NO mot.bin (need shared fallback): ${noMot.length}`);
console.log(`summary written: ${outFile}`);
