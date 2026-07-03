#!/usr/bin/env node
// Cross-check: the hand-transcribed Challenge constants in packages/missions must equal the
// DOL-extracted tables in research/decomp/data/challenge-battle-tables-8036f360.json. The UI
// survey (2026-07-03) flagged that the extract existed but was never checked against the
// transcription — a silent transcription error would go undetected. This closes that gap.
//
// Requires packages/missions built (tsc -b). Reads the extract JSON directly.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const extract = JSON.parse(
  fs.readFileSync(path.join(repoRoot, "research/decomp/data/challenge-battle-tables-8036f360.json"), "utf8"),
);
const ref = await import("../packages/missions/dist/challenge-reference.js");
const challenge = await import("../packages/missions/dist/challenge.js");

let checks = 0;
let failures = 0;
const eq = (a, b, msg) => {
  checks++;
  const av = JSON.stringify(a);
  const bv = JSON.stringify(b);
  if (av !== bv) {
    failures++;
    console.error(`  FAIL: ${msg}\n    transcribed=${av}\n    extracted  =${bv}`);
  }
};

// Battle counts 5/10/15
eq([...ref.CHALLENGE_BATTLE_COUNTS], [extract.battleCountsPerDifficulty.normal, extract.battleCountsPerDifficulty.tuff, extract.battleCountsPerDifficulty.insane], "CHALLENGE_BATTLE_COUNTS");

// Energy limits 1500/2000/2500
eq([challenge.CHALLENGE_DIFFICULTIES.NORMAL, challenge.CHALLENGE_DIFFICULTIES.TUFF, challenge.CHALLENGE_DIFFICULTIES.INSANE],
  [extract.energyLimitsPerDifficulty.normal, extract.energyLimitsPerDifficulty.tuff, extract.energyLimitsPerDifficulty.insane], "energy limits");

// Stage pool (reference stores hex bytes; extract stores decimal)
eq([...ref.CHALLENGE_STAGE_BYTES], extract.stagePool, "CHALLENGE_STAGE_BYTES vs stagePool");

// Side-rank pairs (damage-side bytes per difficulty) — DAT_804356e4_pairs = NORMAL/TUFF/INSANE
if (extract.perDifficultyExtras?.DAT_804356e4_pairs) {
  // challengeSideRanksForMode lives in @gf/combat; the reference exposes the same via
  // challengeModeForPlayerBudget mapping — assert the difficulty ordering at least maps 3 modes.
  const pairs = extract.perDifficultyExtras.DAT_804356e4_pairs;
  checks++;
  if (!(Array.isArray(pairs) && pairs.length === 3)) {
    failures++;
    console.error(`  FAIL: expected 3 side-rank pairs, got ${JSON.stringify(pairs)}`);
  }
}

console.log(`challengeTables.crosscheck: ${checks - failures}/${checks} checks passed`);
process.exit(failures);
