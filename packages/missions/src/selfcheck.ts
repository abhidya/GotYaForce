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

import { createChallengeRun, CHALLENGE_DIFFICULTIES } from "./challenge.js";
import { createAdventureCampaign } from "./adventure.js";
import { computeResults, type BattleOutcome } from "./scoring.js";
import type { BorgData } from "./borg-data.js";
import type { StagesData } from "./adventure.js";

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
  const wins: BattleOutcome = {
    win: true,
    attack: 4200,
    hits: 80,
    attempts: 100,
    dodges: 30,
    incoming: 40,
    enemyBorgsDefeated: 8,
    playerBorgsDefeated: 0,
    allyBorgsDefeated: 1,
    costWon: 1800,
    costLost: 0,
  };
  const loss: BattleOutcome = {
    ...wins,
    win: false,
    enemyBorgsDefeated: 3,
    playerBorgsDefeated: 3,
    costWon: 600,
    costLost: 900,
  };
  for (const outcome of [wins, wins, loss]) {
    const results = computeResults(outcome);
    const prog = run.next(results);
    console.log(
      `    -> ${prog.outcome} grand=${results.grandTotal} ` +
        `action=${prog.action} runScore=${prog.score} current=${prog.current}`,
    );
  }

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
