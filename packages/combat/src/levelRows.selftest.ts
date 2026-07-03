// Self-test for ATK-020 (borg level plumbing -- level byte + row table selection; damage-
// formula floats stay defaulted, NOT wired to level).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) --
// this is its own entry point with its own runner (scripts/run-level-tests.mjs), following the
// same pattern as commandSchema.selftest.ts (ATK-001/ATK-004) and ammo.selftest.ts (ATK-009).
// Does not import or modify selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   tools/node/node.exe node_modules/typescript/bin/tsc -b tsconfig.json apps/game/tsconfig.json
//   tools/node/node.exe scripts/run-level-tests.mjs
// main()/runSelfTest() return an exit code (0 = pass).

import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import { LEVEL_ROW_OFFSETS_804339E8, sourceStatsForBorgId } from "./sourceBorgStats.js";
import { computeSourceDamage } from "./damageFormula.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex } from "./gauges.js";
import type { BorgRuntime } from "./types.js";

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

const G_RED: BorgStats = {
  id: "pl0615",
  name: "G RED",
  energy: 300,
  hp: "200/290",
  defense: 3,
  shot: 4,
  attack: 4,
  speed: 6,
};

function makeProfile(overrides: Partial<BorgProfile> = {}): BorgProfile {
  return {
    id: "test",
    name: "Test",
    energy: 1,
    maxHp: 100,
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 5,
    airJumpLevel: 1,
    flyer: false,
    hasShot: true,
    hasMelee: true,
    rangePref: "mixed",
    ...overrides,
  };
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test",
    team: 0,
    ownerPlayer: "p1",
    hp: 100,
    maxHp: 100,
    pos: { x: 0, y: 0, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 1,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 0,
    cooldowns: {},
    invincTimer: 0,
    balanceGauge: 100,
    balanceGaugeMax: 100,
    downGauge: 100,
    downGaugeBase: 100,
    balanceRefillDelay: 0,
    downResetDelay: 0,
    comboWindow: 0,
    comboAccum: 0,
    comboRank: 0,
    paramTier: { tier: 0x10, deltaAccum: 0, timerFrames: 0 },
    statusId: 0,
    statusTimer: 0,
    statusImmunityMask: 0,
    lockTarget: null,
    allyLockTarget: null,
    burstArmFrames: 0,
    burstActive: false,
    burstPaired: false,
    fusionPartnerUid: null,
    fusionState: 0,
    defeatAccounted: false,
    alive: true,
    ...overrides,
  };
}

// --- G RED anchor at default level (ticket's mandated anchor) ------------------------------

function testGRedAnchorDefaultLevel(): void {
  // No level passed -> default row (DAT_804339e8[0]=2) -> HP 200 / ammo 5, EXACTLY reproducing
  // today's (pre-ATK-020) extracted values (behavior-notes.md ag live-verified anchor).
  const profile = buildProfile(G_RED);
  assertEqual(profile.maxHp, 200, "G RED (pl0615) default-level maxHp === 200 (live-verified anchor)");
  assertEqual(profile.level, undefined, "buildProfile(borg) with no level arg leaves BorgProfile.level undefined");

  const sourceStats = sourceStatsForBorgId("pl0615");
  assertEqual(sourceStats?.maxHp, 200, "sourceStatsForBorgId('pl0615') with no level === 200 (unchanged)");
  assertEqual(sourceStats?.weaponSlots[0].ammoCount, 5, "sourceStatsForBorgId('pl0615') weapon-0 ammoCount === 5 (unchanged)");

  // Explicitly passing level 0 must reproduce the exact same row (DAT_804339e8[0] === 2).
  const explicitLevel0 = buildProfile(G_RED, 0);
  assertEqual(explicitLevel0.maxHp, 200, "buildProfile(G_RED, 0) maxHp === 200 (level 0 === default row)");
  assertEqual(explicitLevel0.level, 0, "buildProfile(G_RED, 0) sets BorgProfile.level === 0");
}

// --- Table-driven row-selection vs the verified JSON ---------------------------------------

function testLevelTableDrivenRowSelection(): void {
  // Cross-check every table entry against the verified level-row-offsets JSON baked into
  // borgSourceStats.json (scripts/gen-level-row-offsets.mjs, citing behavior-notes.md ak).
  assertEqual(LEVEL_ROW_OFFSETS_804339E8.length, 32, "DAT_804339e8 table has 32 entries");
  assertEqual(LEVEL_ROW_OFFSETS_804339E8[0], 2, "DAT_804339e8[0] === 2 (ag/ak anchor)");

  // For every level in the table, sourceStatsForBorgId(id, level) must return the SAME row as
  // directly indexing the borg's row table with that level's resolved offset.
  for (let level = 0; level < LEVEL_ROW_OFFSETS_804339E8.length; level++) {
    const expectedOffset = LEVEL_ROW_OFFSETS_804339E8[level] ?? 0;
    const viaLevel = sourceStatsForBorgId("pl0615", level);
    assertTrue(viaLevel !== null, `pl0615 resolves stats at level ${level}`);
    // Cross-check against the level-0 default row scaled by known deltas: G RED's rows step by
    // +10 HP per row offset starting at row[0]=180 (row[N] = 180 + N*10; see
    // research/decomp/data/borg-hp-stat-rows-802f2988.json tables.06.variants.15).
    const expectedHp = 180 + expectedOffset * 10;
    assertEqual(viaLevel?.maxHp, expectedHp, `pl0615 level ${level} (offset ${expectedOffset}) maxHp === ${expectedHp}`);
  }
}

function testLevelClampsToTableBounds(): void {
  // "clamped to the table's 32 entries" (ticket's Required behavior). A level far beyond the
  // table must not throw and must clamp to the last entry (index 31 -> offset 1, per the
  // verified table) rather than reading out of bounds.
  const lastOffset = LEVEL_ROW_OFFSETS_804339E8[LEVEL_ROW_OFFSETS_804339E8.length - 1] ?? 0;
  const clampedHigh = sourceStatsForBorgId("pl0615", 255);
  const atLastIndex = sourceStatsForBorgId("pl0615", LEVEL_ROW_OFFSETS_804339E8.length - 1);
  assertTrue(clampedHigh !== null, "level 255 (out of table bounds) does not throw / returns a value");
  assertEqual(clampedHigh?.maxHp, atLastIndex?.maxHp, "level 255 clamps to the same row as the last table index");
  assertEqual(clampedHigh?.maxHp, 180 + lastOffset * 10, "level 255 clamps to offset " + lastOffset);

  // Negative levels clamp to index 0 (the default row) rather than wrapping/throwing.
  const negativeLevel = sourceStatsForBorgId("pl0615", -5);
  assertEqual(negativeLevel?.maxHp, 200, "negative level clamps to index 0 (offset 2, HP 200)");
}

function testDifferentLevelSelectsDifferentRow(): void {
  // A level whose table entry differs from level 0's must select a genuinely different row.
  // Level 2 -> DAT_804339e8[2] === 8 (verified table), a different offset than level 0's 2.
  assertEqual(LEVEL_ROW_OFFSETS_804339E8[2], 8, "DAT_804339e8[2] === 8 (precondition for this test)");
  const level0 = sourceStatsForBorgId("pl0615", 0);
  const level2 = sourceStatsForBorgId("pl0615", 2);
  assertTrue(level0 !== null && level2 !== null, "both level 0 and level 2 resolve");
  assertTrue(level0?.maxHp !== level2?.maxHp, "level 2 selects a different HP row than level 0 (offsets 2 vs 8 differ)");
  assertEqual(level2?.maxHp, 180 + 8 * 10, "level 2 maxHp === row offset 8's HP (260)");

  // buildProfile threads the same selection through BorgProfile.maxHp.
  const profileLevel2 = buildProfile(G_RED, 2);
  assertEqual(profileLevel2.maxHp, 260, "buildProfile(G_RED, 2).maxHp === 260 (offset 8 row)");
  assertEqual(profileLevel2.level, 2, "buildProfile(G_RED, 2).level === 2");
}

function testBorgsWithoutMultiLevelDataFallBackToDefaultRow(): void {
  // Fallback per ticket: "Borgs without multi-level row data: keep default row (labeled)."
  // An unknown id has no source stats at any level -> both calls return null (same as today).
  const unknown = sourceStatsForBorgId("plffff", 5);
  assertEqual(unknown, null, "unknown borg id returns null regardless of level (fallback preserved)");
  const profile = buildProfile({ id: "plffff", name: "Unknown", energy: 1, defense: 0, shot: 0, attack: 0, speed: 1 }, 5);
  assertEqual(profile.maxHp, 100, "unknown borg id falls back to parseHp's safe default (100) even with a level passed");
}

// --- damageFormula output is UNCHANGED by level (regression guard) ------------------------

function testDamageFormulaUnchangedByLevel(): void {
  // The formula's attackerPower/defenderPower params are NOT fed from BorgProfile.level (per
  // damageFormula.ts's ATK-020 comment near attackerPower/defenderPower, citing behavior-notes
  // (ak): level float init sites are still unfound). Build two otherwise-identical profiles
  // that differ ONLY in .level and confirm computeSourceDamage's output is bit-identical.
  const attackerLevel0 = makeProfile({ id: "pl0615", level: 0 });
  const attackerLevel10 = makeProfile({ id: "pl0615", level: 10 });
  const victimProfile = makeProfile({ id: "pl0008" });

  const attacker = makeBorg({ borgId: "pl0615", team: 0 });
  const victim = makeBorg({ borgId: "pl0008", team: 1, hp: 10_000_000, maxHp: 10_000_000 });
  const record = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);

  const dmgLevel0 = computeSourceDamage({
    attacker,
    attackerProfile: attackerLevel0,
    victim,
    victimProfile,
    record,
  });
  const dmgLevel10 = computeSourceDamage({
    attacker,
    attackerProfile: attackerLevel10,
    victim,
    victimProfile,
    record,
  });
  assertEqual(dmgLevel10, dmgLevel0, "computeSourceDamage output is unchanged when only attackerProfile.level differs (floats not wired)");

  // Same guard from the victim side.
  const victimLevel0 = makeProfile({ id: "pl0008", level: 0 });
  const victimLevel10 = makeProfile({ id: "pl0008", level: 10 });
  const dmgVictimLevel0 = computeSourceDamage({
    attacker,
    attackerProfile: makeProfile({ id: "pl0615" }),
    victim,
    victimProfile: victimLevel0,
    record,
  });
  const dmgVictimLevel10 = computeSourceDamage({
    attacker,
    attackerProfile: makeProfile({ id: "pl0615" }),
    victim,
    victimProfile: victimLevel10,
    record,
  });
  assertEqual(dmgVictimLevel10, dmgVictimLevel0, "computeSourceDamage output is unchanged when only victimProfile.level differs (floats not wired)");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testGRedAnchorDefaultLevel();
  testLevelTableDrivenRowSelection();
  testLevelClampsToTableBounds();
  testDifferentLevelSelectsDifferentRow();
  testBorgsWithoutMultiLevelDataFallBackToDefaultRow();
  testDamageFormulaUnchangedByLevel();

  if (failures > 0) {
    console.error(`levelRows.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`levelRows.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
