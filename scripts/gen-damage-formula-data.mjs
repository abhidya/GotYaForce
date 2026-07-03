#!/usr/bin/env node
// Copy the decoded damage-formula tables into the combat runtime package.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const sourcePath = path.join(repoRoot, "research", "decomp", "data", "damage-formula-tables-804335e0.json");
const outPath = path.join(repoRoot, "packages", "combat", "src", "data", "damageFormula.json");

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

const parsed = JSON.parse(fs.readFileSync(sourcePath, "utf8"));
const required = [
  "scalars",
  "attackRankBySideRank_804335e0",
  "attackerHpCurves_804335e8",
  "attackerForceCurves_804335f0",
  "attackHandicap_804335f8",
  "defenseRankCurves_80433600",
  "defenderHpCurves_80433608",
  "defenderForceCurves_80433610",
  "defenseHandicap_80433618",
  "comboRankScale_802c7ca0",
  "challengeSideRankBytes_804356e4",
  "defenseCurveSelectors_pldata_9c9d9e",
];

const missing = required.filter((key) => !(key in parsed));
if (missing.length > 0) {
  throw new Error(`damage formula source is missing keys: ${missing.join(", ")}`);
}

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(parsed, null, 1)}\n`);
console.log(`wrote ${rel(outPath)} from ${rel(sourcePath)}`);
