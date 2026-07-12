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
import { createBattle } from "./battle.js";
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

const DEATH_BORG_ALPHA: BorgStats = {
  id: "pl0008",
  name: "Death Borg Alpha",
  energy: 100,
  hp: 100,
  defense: 0,
  shot: 0,
  attack: 2,
  speed: 3,
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
  // No level passed -> default row (byte 0 -> row 2) -> HP 200 / ammo 5, EXACTLY reproducing
  // today's (pre-ATK-020) extracted values (behavior-notes.md ag live-verified anchor).
  const profile = buildProfile(G_RED);
  assertEqual(profile.maxHp, 200, "G RED (pl0615) default-level maxHp === 200 (live-verified anchor)");
  assertEqual(profile.level, undefined, "buildProfile(borg) with no level arg leaves BorgProfile.level undefined");

  const sourceStats = sourceStatsForBorgId("pl0615");
  assertEqual(sourceStats?.maxHp, 200, "sourceStatsForBorgId('pl0615') with no level === 200 (unchanged)");
  assertEqual(sourceStats?.weaponSlots[0].ammoCount, 5, "sourceStatsForBorgId('pl0615') weapon-0 ammoCount === 5 (unchanged)");

  // Explicitly passing level BYTE 0 (= display level 1) must reproduce the exact same default
  // row (byte 0 + 2 === row 2), so the default and explicit-level-0 paths agree.
  const explicitLevel0 = buildProfile(G_RED, 0);
  assertEqual(explicitLevel0.maxHp, 200, "buildProfile(G_RED, 0) maxHp === 200 (byte 0 -> row 2 === default)");
  assertEqual(explicitLevel0.level, 0, "buildProfile(G_RED, 0) sets BorgProfile.level === 0");
}

// --- Corrected level->row rule (row = levelByte + 2) vs the wiki's lv1/lv10 anchors ---------

function testMonotonicLevelProgression(): void {
  // CORRECTED rule (behavior-notes (av)/(aw)): rowIndex = levelByte + 2 (display level + 1). The
  // wiki's per-borg lv1/lv10 HP map to row[2]/row[11]; the curve is monotonic +10 HP/level for
  // G RED (row[N] = 180 + N*10; research/decomp/data/borg-hp-stat-rows-802f2988.json
  // tables.06.variants.15). This REPLACES the old DAT_804339e8[level] indexing, whose
  // non-monotonic values ([2,2,8,6,0,...]) cannot be a level curve (HP would fall as you level).
  //
  // Sanity-check the retained table is still the non-monotonic raw dump (NOT used for rows now):
  assertEqual(LEVEL_ROW_OFFSETS_804339E8[0], 2, "DAT_804339e8[0] === 2 (raw dump retained for reference)");
  assertEqual(LEVEL_ROW_OFFSETS_804339E8[2], 8, "DAT_804339e8[2] === 8 (raw dump; NOT the row offset)");

  // Wiki anchors: byte 0 (display lv1) -> row 2 -> HP 200; byte 9 (display lv10) -> row 11 -> 290.
  assertEqual(sourceStatsForBorgId("pl0615", 0)?.maxHp, 200, "pl0615 byte 0 (lv1) -> row 2 -> HP 200 (wiki L1)");
  assertEqual(sourceStatsForBorgId("pl0615", 9)?.maxHp, 290, "pl0615 byte 9 (lv10) -> row 11 -> HP 290 (wiki L10)");

  // Full monotonic sweep across the 10 display levels (bytes 0..9): HP = 180 + (byte+2)*10.
  let prev = -Infinity;
  for (let levelByte = 0; levelByte <= 9; levelByte++) {
    const expectedHp = 180 + (levelByte + 2) * 10;
    const hp = sourceStatsForBorgId("pl0615", levelByte)?.maxHp ?? -1;
    assertEqual(hp, expectedHp, `pl0615 byte ${levelByte} (row ${levelByte + 2}) maxHp === ${expectedHp}`);
    assertTrue(hp > prev, `pl0615 byte ${levelByte} HP (${hp}) strictly greater than previous (${prev}) — monotonic`);
    prev = hp;
  }
}

function testLevelClampsToRowBounds(): void {
  // Clamp to the borg's available rows (G RED has 20: rows 0..19). A level byte far beyond the
  // rows must not throw and must clamp to the last row (index 19 -> HP 370) rather than reading
  // out of bounds. (an) s6: out-of-range levels read neighbouring rows; clamping is the safe
  // port choice, not a ROM-read claim.
  const clampedHigh = sourceStatsForBorgId("pl0615", 255);
  assertTrue(clampedHigh !== null, "byte 255 (past the row table) does not throw / returns a value");
  assertEqual(clampedHigh?.maxHp, 370, "byte 255 clamps to the last row (index 19, HP 370)");

  // Negative bytes (nonsensical for an unsigned level) clamp to row 0 (the minimum stat row).
  const negativeLevel = sourceStatsForBorgId("pl0615", -5);
  assertEqual(negativeLevel?.maxHp, 180, "negative byte clamps to row 0 (HP 180)");
}

function testDifferentLevelSelectsDifferentRow(): void {
  // Different level bytes must select genuinely different rows under the corrected rule.
  // byte 0 -> row 2 -> HP 200; byte 5 (display lv6) -> row 7 -> HP 250.
  const level0 = sourceStatsForBorgId("pl0615", 0);
  const level5 = sourceStatsForBorgId("pl0615", 5);
  assertTrue(level0 !== null && level5 !== null, "both byte 0 and byte 5 resolve");
  assertTrue(level0?.maxHp !== level5?.maxHp, "byte 5 selects a different HP row than byte 0 (rows 2 vs 7)");
  assertEqual(level5?.maxHp, 180 + 7 * 10, "byte 5 maxHp === row 7's HP (250)");

  // buildProfile threads the same selection through BorgProfile.maxHp.
  const profileLevel5 = buildProfile(G_RED, 5);
  assertEqual(profileLevel5.maxHp, 250, "buildProfile(G_RED, 5).maxHp === 250 (row 7)");
  assertEqual(profileLevel5.level, 5, "buildProfile(G_RED, 5).level === 5");
}

function testBattleForceLevelsThreadIntoDeploy(): void {
  const battle = createBattle(
    {
      stageId: "level-test",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"], borgLevels: [9] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
      ],
    },
    [G_RED, DEATH_BORG_ALPHA],
  );
  const gRed = battle.observe().actors.find((b) => b.borgId === "pl0615");
  assertTrue(gRed !== undefined, "battle deploys G RED");
  assertEqual(gRed?.maxHp, 290, "battle deploy reads borgLevels[0]=9 as G RED lv10 maxHp 290");
  assertEqual(gRed?.hp, 290, "battle deploy starts G RED at lv10 HP");
  assertEqual(gRed?.ammo, 8, "battle deploy starts G RED with lv10 weapon-0 ammo 8");
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
  testMonotonicLevelProgression();
  testLevelClampsToRowBounds();
  testDifferentLevelSelectsDifferentRow();
  testBattleForceLevelsThreadIntoDeploy();
  testBorgsWithoutMultiLevelDataFallBackToDefaultRow();
  testDamageFormulaUnchangedByLevel();

  if (failures > 0) {
    console.error(`levelRows.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`levelRows.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
