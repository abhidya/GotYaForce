// Self-test for the ATK-018 fusion pair-table RUNTIME wiring (fusionPairs.ts).
//
// fusionPairs.selftest.ts validates the research extraction itself; this test validates
// the runtime lookup layer against an INDEPENDENT transcription of the ROM table
// (DAT_802d352c, behavior-notes.md (aj)) and against the roster, so a generator or
// reshaping bug cannot silently drop/shuffle a pair on its way into the sim.
//
// Deliberately separate from selfcheck.ts — own entry point, own runner
// (scripts/run-fusion-runtime-tests.mjs), per the fusionPairs.selftest.ts precedent.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-fusion-runtime-tests.mjs

import { readFileSync } from "node:fs";
import { dirname, resolve as resolvePath } from "node:path";
import { fileURLToPath } from "node:url";

import {
  FUSION_PAIRS,
  fusionPairCoverage,
  fusionPairsForBorgId,
  fusionPartnerIdsForBorgId,
  fusionResultForPair,
  isFusionResultBorgId,
} from "./fusionPairs.js";

// --- Test scaffolding --------------------------------------------------------------------

let failures = 0;
let checks = 0;

function assertEqual<T>(actual: T, expected: T, label: string): void {
  checks++;
  if (actual !== expected) {
    failures++;
    console.error(`FAIL: ${label} — expected ${String(expected)}, got ${String(actual)}`);
  }
}

function assertTrue(cond: boolean, label: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
  }
}

// --- Independent transcription of the ROM table -------------------------------------------
// Every directed entry of DAT_802d352c's two non-null family sub-lists (families 5, 6),
// transcribed from research/decomp/data/fusion-pairs-802d352c.json — NOT read from the
// generated runtime JSON, so the generator is checked against the source, not itself.

const EXPECTED_PAIRS: ReadonlyArray<readonly [string, string, string]> = [
  ["pl0505", "pl0506", "pl0507"], // DEATH HEAD + CYBER DRAGON -> CYBER DEATH DRAGON
  ["pl0506", "pl0505", "pl0507"],
  ["pl0511", "pl0512", "pl0513"], // MACHINE HEAD + MECHANICAL DRAGON -> MACHINE DRAGON
  ["pl0512", "pl0511", "pl0513"],
  ["pl0600", "pl0601", "pl0602"], // MACHINE RED + MACHINE BLUE -> CYBER MACHINE SEIRYU
  ["pl0600", "pl0609", "pl060c"], // MACHINE RED + CYBER ATLAS -> CYBER MACHINE BYAKKO
  ["pl0601", "pl0600", "pl0602"],
  ["pl0601", "pl0608", "pl060e"], // MACHINE BLUE + CYBER MARS -> CYBER MACHINE GENBU
  ["pl0608", "pl0601", "pl060e"],
  ["pl0608", "pl0609", "pl060a"], // CYBER MARS + CYBER ATLAS -> CYBER MACHINE SUZAKU
  ["pl0609", "pl0600", "pl060c"],
  ["pl0609", "pl0608", "pl060a"],
];

// --- Tests ---------------------------------------------------------------------------------

function testEveryTableEntryResolves(): void {
  assertEqual(FUSION_PAIRS.length, EXPECTED_PAIRS.length, "runtime table holds every directed pair");
  for (const [self, partner, result] of EXPECTED_PAIRS) {
    assertEqual(fusionResultForPair(self, partner), result, `${self} + ${partner} -> ${result}`);
    assertEqual(
      fusionResultForPair(self.toUpperCase(), partner.toUpperCase()),
      result,
      `${self} + ${partner} resolves case-insensitively`,
    );
    assertTrue(
      fusionPairsForBorgId(self).some((p) => p.partner === partner && p.result === result),
      `${self}'s own sub-list carries the ${partner} entry`,
    );
    assertTrue(fusionPartnerIdsForBorgId(self).includes(partner), `${self} lists ${partner} as a partner`);
    assertTrue(isFusionResultBorgId(result), `${result} is marked as a fusion result`);
  }
}

function testNonPairsResolveNull(): void {
  // Roster borgs from families whose table slots are empty (0-4, 7-16) can never fuse.
  assertEqual(fusionResultForPair("pl0000", "pl0001"), null, "family 0 borgs have no fusion entries");
  assertEqual(fusionResultForPair("pl0200", "pl0201"), null, "family 2 borgs have no fusion entries");
  // Fusable borgs with the WRONG partner do not fuse.
  assertEqual(fusionResultForPair("pl0505", "pl0600"), null, "DEATH HEAD does not fuse with MACHINE RED");
  assertEqual(fusionResultForPair("pl0600", "pl0608"), null, "MACHINE RED does not fuse with CYBER MARS");
  // A fusion RESULT borg carries no entries of its own.
  assertEqual(fusionPairsForBorgId("pl0507").length, 0, "CYBER DEATH DRAGON carries no fusion entries");
  assertEqual(fusionPairsForBorgId("pl0602").length, 0, "CYBER MACHINE SEIRYU carries no fusion entries");
  assertEqual(fusionResultForPair("pl0507", "pl0505"), null, "fusion results cannot re-fuse");
  assertTrue(!isFusionResultBorgId("pl0505"), "DEATH HEAD is not itself a fusion result");
}

function testCoverage(): void {
  const coverage = fusionPairCoverage();
  assertEqual(coverage.pairCount, 12, "coverage: 12 directed pairs");
  assertEqual(coverage.selfBorgCount, 8, "coverage: 8 borgs carry entries");
  assertEqual(coverage.resultBorgCount, 6, "coverage: 6 distinct fusion results");
}

function testAllIdsResolveToRoster(rosterIds: Set<string>): void {
  for (const pair of FUSION_PAIRS) {
    assertTrue(rosterIds.has(pair.self), `self id ${pair.self} resolves to a roster entry`);
    assertTrue(rosterIds.has(pair.partner), `partner id ${pair.partner} resolves to a roster entry`);
    assertTrue(rosterIds.has(pair.result), `result id ${pair.result} resolves to a roster entry`);
  }
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  // The compiled file lives in packages/combat/dist — 3 levels up is the repo root
  // (same convention as fusionPairs.selftest.ts).
  const repoRoot = resolvePath(dirname(fileURLToPath(import.meta.url)), "..", "..", "..");
  const borgsDoc = JSON.parse(
    readFileSync(resolvePath(repoRoot, "packages/assets/data/borgs.json"), "utf8"),
  ) as { borgs: { id: string }[] };
  const rosterIds = new Set(borgsDoc.borgs.map((b) => b.id));

  testEveryTableEntryResolves();
  testNonPairsResolveNull();
  testCoverage();
  testAllIdsResolveToRoster(rosterIds);

  if (failures > 0) {
    console.error(`fusionRuntime.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`fusionRuntime.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
