// Self-test for the winner-mask battle judge (behavior-notes (ae), zz_00297c8_ @0x800297c8).
// Verifies BattleState.winnerMask + the derived result across the four ROM outcomes: side wins
// (mask 1<<side), mutual simultaneous destruction (mask 3 -> player LOSE), and timeout no-winner
// (mask 4 -> "draw"). Exercises the real createBattle/step path (energy recompute + death
// accounting), not a hand-set mask.
//
// Deliberately separate from selfcheck.ts — own entry point, own runner
// (scripts/run-judge-tests.mjs), per the commandSchema/burst/mashCounter precedent. Does not
// import or modify selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   tools/node/node.exe node_modules/typescript/bin/tsc -b tsconfig.json apps/game/tsconfig.json
//   tools/node/node.exe scripts/run-judge-tests.mjs

import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, resolve } from "node:path";

import { createBattle } from "./battle.js";
import { applyHit } from "./combat.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import { emptyInput, type BorgRuntime, type PlayerInput, type Battle, type BattleConfig } from "./types.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex } from "./gauges.js";

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

function loadBorgs(): BorgStats[] {
  const here = dirname(fileURLToPath(import.meta.url));
  const candidates = [
    resolve(here, "../../assets/data/borgs.json"),
    resolve(here, "../../../assets/data/borgs.json"),
    resolve(here, "../../../packages/assets/data/borgs.json"),
  ];
  for (const p of candidates) {
    try {
      const raw = readFileSync(p, "utf8");
      const json = JSON.parse(raw) as { borgs: BorgStats[] };
      return json.borgs;
    } catch {
      // try next candidate
    }
  }
  throw new Error("battleJudge.selftest: could not locate borgs.json");
}

const BORGS = loadBorgs();
const P1 = "pl0615"; // G RED (player)
const E1 = "pl0008"; // enemy

function profileFor(id: string): BorgProfile {
  const s = BORGS.find((b) => b.id === id);
  if (!s) throw new Error(`battleJudge.selftest: missing borg ${id}`);
  return buildProfile(s);
}

/** Two single-borg forces, spawned far apart so nobody dies except when we kill them.
 *  Omit `timeLimitFrames` for an untimed battle. */
function makeBattle(opts: { team0Human: boolean; team1Human: boolean; timeLimitFrames?: number }): Battle {
  const cfg: BattleConfig = {
    stageId: "st00",
    forces: [
      { team: 0, ownerPlayer: opts.team0Human ? "p1" : null, borgIds: [P1] },
      { team: 1, ownerPlayer: opts.team1Human ? "p2" : null, borgIds: [E1] },
    ],
    bounds: { x: 4000, z: 4000 },
    spawnPoints: [
      { pos: { x: -3500, y: 10, z: -3500 } },
      { pos: { x: 3500, y: 10, z: 3500 } },
    ],
    ...(opts.timeLimitFrames !== undefined ? { timeLimitFrames: opts.timeLimitFrames } : {}),
  };
  return createBattle(cfg, BORGS);
}

/** Drive a borg to a lethal death state in place (mirrors selfcheck's kill-event harness). */
function kill(borg: BorgRuntime, profile: BorgProfile): void {
  borg.hp = 1;
  borg.invincTimer = 0;
  borg.state = "idle";
  applyHit(
    borg,
    profile,
    9999,
    0,
    { x: 0, y: 0, z: 0 },
    { x: borg.pos.x, y: borg.pos.y, z: borg.pos.z - 10 },
    true,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
  );
}

const idle: Record<string, PlayerInput> = { p1: emptyInput(), p2: emptyInput() };

// --- Cases -------------------------------------------------------------------------------

function testEnemyWipeIsPlayerWin(): void {
  // Player = team 0 (human). Kill the only enemy borg -> team 1 destroyed -> mask 1 (side 0 won).
  const battle = makeBattle({ team0Human: true, team1Human: false });
  const enemy = battle.state.borgs.find((b) => b.team === 1);
  if (!enemy) throw new Error("no enemy borg");
  kill(enemy, profileFor(E1));
  battle.step(1 / 60, idle);
  assertEqual(battle.state.energy[1] ?? -1, 0, "team 1 energy drops to 0 after its only borg dies");
  assertEqual(battle.state.winnerMask, 1, "enemy wipe -> winnerMask === 1 (side 0 won)");
  assertEqual(battle.state.result, "win", "enemy wipe -> result 'win' for the player (team 0)");
}

function testPlayerWipeIsLose(): void {
  // Player = team 0. Kill the player's only borg -> team 0 destroyed -> mask 2 (side 1 won).
  const battle = makeBattle({ team0Human: true, team1Human: false });
  const me = battle.state.borgs.find((b) => b.team === 0);
  if (!me) throw new Error("no player borg");
  kill(me, profileFor(P1));
  battle.step(1 / 60, idle);
  assertEqual(battle.state.energy[0] ?? -1, 0, "team 0 energy drops to 0 after its only borg dies");
  assertEqual(battle.state.winnerMask, 2, "player wipe -> winnerMask === 2 (side 1 won)");
  assertEqual(battle.state.result, "lose", "player wipe -> result 'lose' (equality test fails)");
}

function testMutualDestructionIsLose(): void {
  // Both sides' only borgs die the same frame -> mask 3 (mutual). Per the ROM (FUN_801969a0),
  // mask 3 exits to the same failure screen as a loss, so the player result is 'lose', NOT 'draw'.
  const battle = makeBattle({ team0Human: true, team1Human: false });
  const me = battle.state.borgs.find((b) => b.team === 0);
  const enemy = battle.state.borgs.find((b) => b.team === 1);
  if (!me || !enemy) throw new Error("missing borg");
  kill(me, profileFor(P1));
  kill(enemy, profileFor(E1));
  battle.step(1 / 60, idle);
  assertEqual(battle.state.energy[0] ?? -1, 0, "team 0 energy 0 (mutual)");
  assertEqual(battle.state.energy[1] ?? -1, 0, "team 1 energy 0 (mutual)");
  assertEqual(battle.state.winnerMask, 3, "mutual destruction -> winnerMask === 3");
  assertEqual(battle.state.result, "lose", "mutual destruction -> result 'lose' for the player (mask 3 = fail)");
}

function testTimeoutIsDrawMask4(): void {
  // Two live borgs far apart, a short running timer -> nobody dies -> timeout no-winner -> mask 4.
  const battle = makeBattle({ team0Human: true, team1Human: false, timeLimitFrames: 20 });
  for (let f = 0; f < 40 && battle.state.result === "ongoing"; f++) {
    battle.step(1 / 60, idle);
  }
  assertEqual(battle.state.result, "draw", "running-timer timeout -> result 'draw'");
  assertEqual(battle.state.winnerMask, 4, "running-timer timeout -> winnerMask === 4 (no-winner)");
}

function testOngoingHasNoMask(): void {
  // Fresh battle, both sides alive: no winner yet, no result flip.
  const battle = makeBattle({ team0Human: true, team1Human: false });
  battle.step(1 / 60, idle);
  assertEqual(battle.state.result, "ongoing", "both sides alive -> result stays 'ongoing'");
  assertEqual(battle.state.winnerMask ?? 0, 0, "both sides alive -> winnerMask absent/0");
}

function testAllCpuEnemyWipeIsWin(): void {
  // No human owner: a lone survivor "wins" (surviving side), mutual destruction is a draw.
  const battle = makeBattle({ team0Human: false, team1Human: false });
  const enemy = battle.state.borgs.find((b) => b.team === 1);
  if (!enemy) throw new Error("no enemy borg");
  kill(enemy, profileFor(E1));
  battle.step(1 / 60, idle);
  assertEqual(battle.state.winnerMask, 1, "all-CPU enemy wipe -> winnerMask === 1");
  assertEqual(battle.state.result, "win", "all-CPU: lone survivor -> 'win'");
}

// --- Runner ------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testEnemyWipeIsPlayerWin();
  testPlayerWipeIsLose();
  testMutualDestructionIsLose();
  testTimeoutIsDrawMask4();
  testOngoingHasNoMask();
  testAllCpuEnemyWipeIsWin();

  if (failures > 0) {
    console.error(`battleJudge.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`battleJudge.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
