// @gf/missions — selfcheck.ts
//
// Node-runnable sanity check. Builds a NORMAL challenge run, loads the full
// adventure campaign, and reports battle counts, enemy borg ids per battle, and
// any name→id resolution failures across all stages.
//
// Run:
//   node --experimental-strip-types packages/missions/src/selfcheck.ts
// (or transpile first). Data is read from packages/assets/data at runtime so
// the library itself stays free of filesystem access.

import { readFileSync, existsSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, resolve } from "node:path";

import { createChallengeRun, CHALLENGE_DIFFICULTIES, enemyTargetForBattle } from "./challenge.js";
import { stageIdForBattleConfig, type CombatStageCatalog } from "./combat-config.js";
import {
  CHALLENGE_ALLY_BUDGETS,
  CHALLENGE_ALLY_GROUP_CODES,
  CHALLENGE_ALLY_MAX_MEMBERS,
  CHALLENGE_BATTLE_COUNTS,
  CHALLENGE_ENEMY_BUDGETS,
  CHALLENGE_ENEMY_GROUP_CODES,
  CHALLENGE_ENEMY_MAX_MEMBERS,
  CHALLENGE_GROUP_ROSTERS,
  CHALLENGE_STAGE_BYTES,
  challengeStageId,
  challengeStageVariantCount,
  type ChallengeGroupCode,
  type ChallengeMode,
} from "./challenge-reference.js";
import { createAdventureCampaign } from "./adventure.js";
import type { MissionBattleConfig } from "./battle-config.js";
import { computeResults, type BattleOutcome } from "./scoring.js";
import { readBorgs, type BorgData } from "./borg-data.js";
import type { StagesData } from "./adventure.js";

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`selfcheck failed: ${message}`);
}

function assertChallengeReferenceInvariants(): void {
  assert(CHALLENGE_DIFFICULTIES.NORMAL === 1500, "Challenge NORMAL must be GF ENERGY 1500");
  assert(CHALLENGE_DIFFICULTIES.TUFF === 2000, "Challenge TUFF must be GF ENERGY 2000");
  assert(CHALLENGE_DIFFICULTIES.INSANE === 2500, "Challenge INSANE must be GF ENERGY 2500");
  assert(
    Object.keys(CHALLENGE_DIFFICULTIES).join(",") === "NORMAL,TUFF,INSANE",
    "Challenge difficulty labels must match captured UI order",
  );
  assert(
    enemyTargetForBattle(CHALLENGE_DIFFICULTIES.NORMAL, 0) === 1000,
    "NORMAL BATTLE 1 target should match recovered DOL table",
  );
  assert(
    enemyTargetForBattle(CHALLENGE_DIFFICULTIES.NORMAL, 1) === 1000,
    "NORMAL BATTLE 2 target should match recovered DOL table",
  );
  assert(
    CHALLENGE_STAGE_BYTES.map(challengeStageId).join(",") === "st00,st01,st02,st03,st04,st05,st08,st0a,st0b,st0c,st0e",
    "Challenge stage-byte table should map to the recovered exported base stage ids",
  );
  assert(
    CHALLENGE_STAGE_BYTES.every((stageByte) => challengeStageVariantCount(stageByte) === 4),
    "Challenge stage bytes should use the recovered DOL variant-count table, not a literal hardcoded count",
  );
  assert(
    challengeStageVariantCount(0x09) === 5,
    "DOL stage-variant count table should preserve the non-Challenge st09 five-variant entry",
  );

  // Per-mode table rows must exactly cover the DOL battle counts (5/10/15).
  for (const mode of [0, 1, 2] as const) {
    const count = CHALLENGE_BATTLE_COUNTS[mode];
    assert(CHALLENGE_ALLY_BUDGETS[mode].length === count, `ally budget rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_BUDGETS[mode].length === count, `enemy budget rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ALLY_MAX_MEMBERS[mode].length === count, `ally max-member rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_MAX_MEMBERS[mode].length === count, `enemy max-member rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ALLY_GROUP_CODES[mode].length === count, `ally group rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_GROUP_CODES[mode].length === count, `enemy group rows must cover mode ${mode}'s ${count} battles`);
    for (const row of CHALLENGE_ENEMY_GROUP_CODES[mode]) {
      assert(row.length === 4, "each enemy group row carries the DOL's four random choices");
      assert(
        row.every((code) => CHALLENGE_GROUP_ROSTERS[code].length > 0),
        `mode ${mode} enemy group row [${row.join(",")}] must only reference non-empty spawn pools`,
      );
    }
    for (const row of CHALLENGE_ALLY_GROUP_CODES[mode]) {
      assert(row.length === 4, "each ally group row carries the DOL's four random choices");
      assert(
        row.every((code) => CHALLENGE_GROUP_ROSTERS[code].length > 0),
        `mode ${mode} ally group row [${row.join(",")}] must only reference non-empty spawn pools`,
      );
    }
  }

  // RAM-trace cross-check (research/traces/GG4E/spawn-evidence.json):
  // battle1_start_checkpoint.sav captured a NORMAL BATTLE 1 with enemy borgs
  // 0a05/0705 and CPU ally 020a. Those must be reachable from the round's
  // DOL group rows (enemy row 48, ally row 50).
  assert(
    CHALLENGE_ENEMY_GROUP_CODES[0][0]!.every((code) => code === 48),
    "NORMAL BATTLE 1 enemy group row must be the traced group 48",
  );
  assert(
    CHALLENGE_ALLY_GROUP_CODES[0][0]!.every((code) => code === 50),
    "NORMAL BATTLE 1 ally group row must be the traced group 50",
  );
  assert(
    (CHALLENGE_GROUP_ROSTERS[48] as readonly string[]).includes("pl0a05") &&
      (CHALLENGE_GROUP_ROSTERS[48] as readonly string[]).includes("pl0705"),
    "group 48 must contain the enemy borgs (pl0a05, pl0705) observed in the battle-1 RAM trace",
  );
  assert(
    (CHALLENGE_GROUP_ROSTERS[50] as readonly string[]).includes("pl020a"),
    "group 50 must contain the CPU ally borg (pl020a) observed in the battle-1 RAM trace",
  );
}

function assertChallengeStageFamilyResolution(): void {
  const catalog = (ids: readonly string[]): CombatStageCatalog => {
    const available = new Set(ids);
    return {
      defaultStageId: "st00",
      hasStageCollision(stageId: string): boolean {
        return available.has(stageId);
      },
    };
  };
  const cfg = (stageByte: number, stageSubtable: number): MissionBattleConfig => ({
    arena: "challenge",
    forces: [],
    meta: {
      mode: "challenge",
      index: 0,
      stageByte,
      stageSubtable,
      stageVariant: 0,
    },
  });

  assert(
    stageIdForBattleConfig(cfg(0x0a, 1), catalog(["st0a", "st2a"])) === "st2a",
    "Challenge stage selector must prefer exported subtable-family stages when present",
  );
  assert(
    stageIdForBattleConfig(cfg(0x0b, 2), catalog(["st0b"])) === "st0b",
    "Challenge stage selector must fall back to the base stage when a family stage is unavailable",
  );
  assert(
    stageIdForBattleConfig({ arena: "challenge", forces: [] }, catalog(["st05"])) === "st00",
    "Challenge arena without raw selector bytes should use the catalog default",
  );
}

/**
 * Deep per-round audit: for each difficulty, generate a full run and verify
 * every battle's enemy/ally rosters, budgets, member caps, and stage selector
 * bytes against the recovered DOL tables in challenge-reference.ts.
 */
function auditChallengeRunAgainstReference(borgs: BorgData): void {
  const validBorgIds = new Set(readBorgs(borgs).map((b) => b.id));

  // Every spawn-pool borg id must resolve against borgs.json.
  for (const [group, roster] of Object.entries(CHALLENGE_GROUP_ROSTERS)) {
    for (const id of roster) {
      assert(validBorgIds.has(id), `group ${group} roster id ${id} must exist in borgs.json`);
    }
  }

  const budgets: Array<[number, ChallengeMode]> = [
    [CHALLENGE_DIFFICULTIES.NORMAL, 0],
    [CHALLENGE_DIFFICULTIES.TUFF, 1],
    [CHALLENGE_DIFFICULTIES.INSANE, 2],
  ];

  for (const [budget, mode] of budgets) {
    const run = createChallengeRun({
      budget,
      playerCount: 1,
      playerForces: [{ player: 0, borgIds: ["pl0615"] }],
      borgs,
    });
    assert(run.mode === mode, `budget ${budget} must map to Challenge mode ${mode}`);
    assert(run.battles.length === CHALLENGE_BATTLE_COUNTS[mode], `mode ${mode} run must have ${CHALLENGE_BATTLE_COUNTS[mode]} battles`);

    let previousStageByte: number | null = null;
    run.battles.forEach((battle, i) => {
      const meta = battle.meta;
      assert(meta !== undefined, `battle ${i + 1} must carry meta`);

      // --- stage selector bytes ---
      const stageByte = meta.stageByte;
      assert(
        typeof stageByte === "number" && (CHALLENGE_STAGE_BYTES as readonly number[]).includes(stageByte),
        `battle ${i + 1} stage byte ${String(stageByte)} must come from the DOL Challenge stage table`,
      );
      assert(battle.arena === challengeStageId(stageByte as number), `battle ${i + 1} arena must match its stage byte`);
      assert(stageByte !== previousStageByte, `battle ${i + 1} must not repeat the previous battle's stage byte`);
      previousStageByte = stageByte as number;
      assert(
        typeof meta.stageSubtable === "number" && meta.stageSubtable >= 0 && meta.stageSubtable <= 2,
        `battle ${i + 1} stage subtable must be 0..2`,
      );
      assert(
        typeof meta.stageVariant === "number" &&
          meta.stageVariant >= 0 &&
          meta.stageVariant < challengeStageVariantCount(stageByte as number),
        `battle ${i + 1} stage variant must respect the DOL variant-count table`,
      );

      // --- enemy rosters ---
      const enemyForces = battle.forces.filter((f) => f.team === "enemy");
      assert(enemyForces.length === 2, `battle ${i + 1} must carry the original two enemy CPU slots`);
      const allowedEnemy = new Set<string>();
      for (const code of CHALLENGE_ENEMY_GROUP_CODES[mode][i]!) {
        for (const id of CHALLENGE_GROUP_ROSTERS[code as ChallengeGroupCode]) allowedEnemy.add(id);
      }
      const maxEnemyMembers = CHALLENGE_ENEMY_MAX_MEMBERS[mode][i]!;
      for (const force of enemyForces) {
        assert(force.borgIds.length <= maxEnemyMembers, `battle ${i + 1} enemy slot must respect the DOL member cap ${maxEnemyMembers}`);
        for (const id of force.borgIds) {
          assert(allowedEnemy.has(id), `battle ${i + 1} enemy borg ${id} must come from the round's DOL group rosters`);
        }
      }
      const enemyCharges = meta.enemySlotBudgetCharge ?? [];
      const enemyTarget = CHALLENGE_ENEMY_BUDGETS[mode][i]!;
      assert(meta.enemyTargetEnergy === enemyTarget, `battle ${i + 1} enemy target must match the DOL budget table`);
      for (const charge of enemyCharges) {
        assert(charge <= enemyTarget, `battle ${i + 1} enemy slot charge ${charge} must fit the DOL budget ${enemyTarget}`);
      }

      // --- CPU ally roster (FIGHT ALONE) ---
      const allyForce = battle.forces.find((f) => f.team === "player" && f.cpuAlly);
      assert(allyForce !== undefined, `battle ${i + 1} FIGHT ALONE must include the CPU ally force`);
      const allowedAlly = new Set<string>();
      for (const code of CHALLENGE_ALLY_GROUP_CODES[mode][i]!) {
        for (const id of CHALLENGE_GROUP_ROSTERS[code as ChallengeGroupCode]) allowedAlly.add(id);
      }
      const maxAllyMembers = CHALLENGE_ALLY_MAX_MEMBERS[mode][i]!;
      assert(allyForce.borgIds.length <= maxAllyMembers, `battle ${i + 1} ally roster must respect the DOL member cap ${maxAllyMembers}`);
      for (const id of allyForce.borgIds) {
        assert(allowedAlly.has(id), `battle ${i + 1} ally borg ${id} must come from the round's DOL ally group rosters`);
      }
      const allyTarget = CHALLENGE_ALLY_BUDGETS[mode][i]!;
      assert(meta.allyTargetEnergy === allyTarget, `battle ${i + 1} ally target must match the DOL budget table`);
      assert((meta.allyBudgetCharge ?? 0) <= allyTarget, `battle ${i + 1} ally charge must fit the DOL budget ${allyTarget}`);
    });
  }
  console.log("challenge per-round audit vs challenge-reference tables: PASS (NORMAL/TUFF/INSANE, stages+rosters+budgets)");
}

/** Find packages/assets/data by walking up from a start directory. */
function findDataDir(): string {
  let dir = dirname(fileURLToPath(import.meta.url));
  for (let i = 0; i < 12; i++) {
    const candidate = resolve(dir, "packages/assets/data/borgs.json");
    if (existsSync(candidate)) return dirname(candidate);
    const sibling = resolve(dir, "../../assets/data/borgs.json");
    if (existsSync(sibling)) return dirname(sibling);
    dir = resolve(dir, "..");
  }
  throw new Error("Could not locate packages/assets/data (borgs.json/stages.json).");
}

function loadData(): { borgs: BorgData; stages: StagesData } {
  const dataDir = findDataDir();
  const borgs = JSON.parse(
    readFileSync(resolve(dataDir, "borgs.json"), "utf8"),
  ) as BorgData;
  const stages = JSON.parse(
    readFileSync(resolve(dataDir, "stages.json"), "utf8"),
  ) as StagesData;
  return { borgs, stages };
}

export function main(): void {
  const { borgs, stages } = loadData();
  assertChallengeReferenceInvariants();
  assertChallengeStageFamilyResolution();
  auditChallengeRunAgainstReference(borgs);

  console.log("=".repeat(70));
  console.log("CHALLENGE — NORMAL run (budget", CHALLENGE_DIFFICULTIES.NORMAL, ")");
  console.log("=".repeat(70));

  // A simple player force; ids exist in the roster (G RED + some ninjas).
  const playerForces = [{ player: 0, borgIds: ["pl0615", "pl0000", "pl000a"] }];

  const run = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1, // FIGHT ALONE → CPU ally added
    playerForces,
    borgs,
  });
  assert(run.battles.length === 5, "NORMAL Challenge run should default to DOL table count");
  assert(run.battles[0]?.label === "BATTLE 1 VS", "Challenge battle label should match captured VS flow");
  assert(run.battles[1]?.label === "BATTLE 2 VS", "WIN branch should advance to BATTLE 2 VS");
  assert(
    run.battles.every((battle) => /^st[0-9a-f]{2}$/.test(battle.arena)),
    "Challenge generated battles should carry literal exported stage ids, not arena-name fallbacks",
  );
  assert(
    run.battles.every((battle) => battle.meta?.stageByte !== undefined && battle.meta.stageSubtable !== undefined && battle.meta.stageVariant !== undefined),
    "Challenge generated battles should preserve all three raw stage selector bytes",
  );
  assert(
    run.battles[0]?.forces.filter((f) => f.team === "player" && f.ownerPlayer == null && f.cpuAlly).length === 1,
    "FIGHT ALONE should add one CPU ally on the player side",
  );
  const clampedTeamRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 4,
    playerForces,
    borgs,
    battleCount: 1,
  });
  assert(clampedTeamRun.playerCount === 2, "Challenge player count should clamp to original 1P/2P branches");
  assert(
    clampedTeamRun.battles[0]?.forces.every((f) => !f.cpuAlly),
    "TEAM UP branch should not add the FIGHT ALONE CPU ally",
  );

  console.log(`battles in run: ${run.total}`);
  for (const battle of run.battles) {
    const enemy = battle.forces.find((f) => f.team === "enemy");
    const allies = battle.forces.filter((f) => f.team === "player");
    const hasCpuAlly = allies.some((f) => f.cpuAlly);
    console.log(
      `  ${battle.label}  target=${battle.meta?.enemyTargetEnergy} ` +
        `actual=${battle.meta?.enemyForceEnergy} ` +
        `enemyCount=${enemy?.borgIds.length} cpuAlly=${hasCpuAlly}`,
    );
    console.log(`     enemy ids: ${enemy?.borgIds.join(", ")}`);
  }

  // Drive the progression: win the first 2, then lose.
  console.log("\n  progression demo (win, win, lose):");
  // DERIVED outcome shape (ROM slot counters +0x404..+0x437). Expected grand totals per
  // the decoded formula (scoring.ts): wins -> costWon 1800 in [1701,1800] -> 18000,
  // costLost 0 -> +1000 (flawless bonus), first strike +5000 = 24000.
  // loss -> costWon 600 in [501,600] -> 6000, costLost 900 in [801,1000] -> −1000, no
  // first strike = 5000 — POSITIVE even on a LOSS (the ROM formula has no win/lose flip).
  const wins: BattleOutcome = {
    win: true,
    attempts: 100,
    hits: 80,
    incomingAimed: 40,
    hitsTakenAimed: 10,
    hitsTakenOther: 5,
    enemyBorgsDefeated: 8,
    playerBorgsDefeated: 0,
    allyBorgsDefeated: 1,
    costWon: 1800,
    costLost: 0,
    firstStrike: true,
  };
  const loss: BattleOutcome = {
    ...wins,
    win: false,
    enemyBorgsDefeated: 3,
    playerBorgsDefeated: 3,
    costWon: 600,
    costLost: 900,
    firstStrike: false,
  };
  for (const outcome of [wins, wins, loss]) {
    const results = computeResults(outcome);
    const prog = run.next(results);
    console.log(
      `    -> ${prog.outcome} grand=${results.grandTotal} ` +
        `action=${prog.action} runScore=${prog.score} current=${prog.current}`,
    );
  }

  const branchRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1,
    playerForces,
    borgs,
  });
  const firstWin = branchRun.next(computeResults(wins));
  assert(firstWin.action === "advance", "WIN should advance Challenge to the next battle");
  assert(firstWin.nextBattle?.label === "BATTLE 2 VS", "WIN should load BATTLE 2 VS next");
  const losingRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1,
    playerForces,
    borgs,
  });
  const firstLoss = losingRun.next(computeResults(loss));
  assert(firstLoss.action === "title", "LOSE should return Challenge to title/menu");
  assert(firstLoss.nextBattle == null, "LOSE should not enqueue an auto-retry battle");

  console.log("\n" + "=".repeat(70));
  console.log("ADVENTURE — campaign load");
  console.log("=".repeat(70));

  const campaign = createAdventureCampaign(stages, borgs);
  console.log(`total stages: ${campaign.total}`);

  const stage1 = campaign.getStage(0);
  if (stage1) {
    console.log(`\nstage 1: "${stage1.name}" @ ${stage1.arena}`);
    console.log(`  confidence=${stage1.confidence} boss=${stage1.boss}`);
    for (const e of stage1.enemies) {
      console.log(
        `  ${e.count}x ${e.name} -> ${e.id ?? "UNRESOLVED"} (energy ${e.energy})`,
      );
    }
    const enemyForce = stage1.battle.forces.find((f) => f.team === "enemy");
    console.log(`  battle enemy borgIds: ${enemyForce?.borgIds.join(", ")}`);
    console.log(`  enemyForceEnergy: ${stage1.enemyForceEnergy}`);
  }

  // Resolution audit across ALL stages.
  console.log("\nname -> id resolution audit (all stages):");
  const unresolvedSet = new Set<string>();
  let resolvedCleanly = 0;
  for (const stage of campaign.stages) {
    if (stage.unresolved.length === 0) resolvedCleanly++;
    for (const name of stage.unresolved) unresolvedSet.add(name);
  }
  console.log(
    `  stages with ALL enemies resolved: ${resolvedCleanly}/${campaign.total}`,
  );
  console.log(`  distinct unresolved enemy names: ${unresolvedSet.size}`);
  for (const name of [...unresolvedSet].sort()) {
    console.log(`    - ${name}`);
  }
}

// Run when executed directly.
main();
