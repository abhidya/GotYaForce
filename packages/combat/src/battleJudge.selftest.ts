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

import { battleStateForSelfcheck, createBattle } from "./battle.js";
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
  const before = battle.observe();
  const active = battle.activeActor("p1");
  assertEqual(active?.uid, before.activeUidByPlayer["p1"], "activeActor resolves the player active uid");
  assertEqual(battle.actor(active?.uid ?? ""), active, "actor lookup reuses the boundary actor snapshot");
  assertEqual(before.result, "ongoing", "fresh observation reports an ongoing result");
  assertEqual(before.defeats.length, 0, "fresh observation has no recorded defeats");
  const beforeEnemy = before.actors.find((actor) => actor.team === 1);
  const beforeEnemyEnergy = before.energy[1] ?? -1;
  const beforeEnemyMax = before.energyMax[1] ?? -1;
  const beforeEnemyHp = beforeEnemy?.hp ?? -1;
  assertEqual(
    beforeEnemyMax,
    Math.floor(beforeEnemyEnergy / 10) * 10,
    "fresh observation reports the rounded team energy maximum",
  );
  if (false) {
    // @ts-expect-error Battle observations do not permit actor mutation.
    before.actors[0]!.hp = 0;
    // @ts-expect-error Battle observation arrays do not expose mutators.
    before.projectiles.push({});
  }
  const enemy = battleStateForSelfcheck(battle).borgs.find((b) => b.team === 1);
  if (!enemy) throw new Error("no enemy borg");
  kill(enemy, profileFor(E1));
  const after = battle.step(1 / 60, idle);
  assertEqual(after.energy[1] ?? -1, 0, "fixed-step result reports team 1 energy dropping to 0");
  assertEqual(after.winnerMask, 1, "enemy wipe -> winnerMask === 1 (side 0 won)");
  assertEqual(after.result, "win", "fixed-step result reports a player win");
  assertEqual(after.defeats.length, 1, "fixed-step result records one defeat fact");
  assertEqual(after.energyMax[1], beforeEnemyMax, "team energy maximum remains stable after defeat");
  assertEqual(before.energy[1], beforeEnemyEnergy, "captured observation keeps its pre-step energy");
  assertEqual(before.energyMax[1], beforeEnemyMax, "captured observation keeps its energy maximum");
  assertEqual(before.defeats.length, 0, "captured observation keeps its pre-step defeat list");
  assertEqual(before.defeated[1] ?? 0, 0, "captured observation keeps its pre-step defeated count");
  assertEqual(beforeEnemy?.hp, beforeEnemyHp, "captured actor keeps its pre-step hp");
  assertEqual(beforeEnemy?.alive, true, "captured actor keeps its pre-step alive fact");
}

function testProjectileObservationAndDespawnFacts(): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0102"] },
        { team: 1, ownerPlayer: "p2", borgIds: [E1] },
      ],
      bounds: { minX: -300, maxX: 300, minZ: -300, maxZ: 300 },
      spawnPoints: [
        { pos: { x: -250, y: 10, z: 0 }, rotY: Math.PI / 2 },
        { pos: { x: 250, y: 10, z: 250 }, rotY: -Math.PI / 2 },
      ],
    },
    BORGS,
  );
  for (let frame = 0; frame < 40; frame++) battle.step(1 / 60, idle);
  battle.step(1 / 60, { p1: { ...emptyInput(), attack: true }, p2: emptyInput() });
  const projectile = battle.observe().projectiles[0];
  if (!projectile) throw new Error("read-interface test did not spawn a projectile");
  const originalPos = { ...projectile.pos };
  const originalLife = projectile.life;
  if (false) {
    // @ts-expect-error Current projectile snapshots cannot mutate sim-owned position.
    projectile.pos.x = 123456;
  }
  let despawn = battle.observe().projectileDespawns.find((fact) => fact.uid === projectile.uid);
  for (let frame = 0; frame < 300 && !despawn; frame++) {
    const after = battle.step(1 / 60, idle);
    despawn = after.projectileDespawns.find((fact) => fact.uid === projectile.uid);
  }
  if (!despawn) throw new Error("read-interface test projectile did not produce despawn facts");
  assertEqual(
    projectile.pos.x,
    originalPos.x,
    "old observation keeps the projectile's original x position",
  );
  assertEqual(projectile.pos.y, originalPos.y, "old observation keeps the projectile's original y position");
  assertEqual(projectile.pos.z, originalPos.z, "old observation keeps the projectile's original z position");
  assertEqual(projectile.life, originalLife, "old observation keeps the projectile's original life");
  assertEqual(despawn.reason, "hit-target", "despawn facts report the correct hit reason");
  assertEqual(despawn.team, projectile.team, "despawn facts retain projectile team");
  assertEqual(
    typeof despawn.impactEffectId,
    "number",
    "target-hit despawn facts retain the applied impact effect id",
  );
  assertEqual(
    Number.isFinite(despawn.pos.x) && Number.isFinite(despawn.pos.y) && Number.isFinite(despawn.pos.z),
    true,
    "despawn facts retain a finite final position",
  );
  assertEqual(
    Number.isFinite(despawn.vel.x) && Number.isFinite(despawn.vel.y) && Number.isFinite(despawn.vel.z),
    true,
    "despawn facts retain finite final velocity",
  );
}

function testPlayerWipeIsLose(): void {
  // Player = team 0. Kill the player's only borg -> team 0 destroyed -> mask 2 (side 1 won).
  const battle = makeBattle({ team0Human: true, team1Human: false });
  const me = battleStateForSelfcheck(battle).borgs.find((b) => b.team === 0);
  if (!me) throw new Error("no player borg");
  kill(me, profileFor(P1));
  battle.step(1 / 60, idle);
  assertEqual(battle.observe().energy[0] ?? -1, 0, "team 0 energy drops to 0 after its only borg dies");
  assertEqual(battle.observe().winnerMask, 2, "player wipe -> winnerMask === 2 (side 1 won)");
  assertEqual(battle.observe().result, "lose", "player wipe -> result 'lose' (equality test fails)");
}

function testMutualDestructionIsLose(): void {
  // Both sides' only borgs die the same frame -> mask 3 (mutual). Per the ROM (FUN_801969a0),
  // mask 3 exits to the same failure screen as a loss, so the player result is 'lose', NOT 'draw'.
  const battle = makeBattle({ team0Human: true, team1Human: false });
  const mutable = battleStateForSelfcheck(battle);
  const me = mutable.borgs.find((b) => b.team === 0);
  const enemy = mutable.borgs.find((b) => b.team === 1);
  if (!me || !enemy) throw new Error("missing borg");
  kill(me, profileFor(P1));
  kill(enemy, profileFor(E1));
  battle.step(1 / 60, idle);
  assertEqual(battle.observe().energy[0] ?? -1, 0, "team 0 energy 0 (mutual)");
  assertEqual(battle.observe().energy[1] ?? -1, 0, "team 1 energy 0 (mutual)");
  assertEqual(battle.observe().winnerMask, 3, "mutual destruction -> winnerMask === 3");
  assertEqual(battle.observe().result, "lose", "mutual destruction -> result 'lose' for the player (mask 3 = fail)");
}

function testTimeoutIsDrawMask4(): void {
  // Two live borgs far apart, a short running timer -> nobody dies -> timeout no-winner -> mask 4.
  const battle = makeBattle({ team0Human: true, team1Human: false, timeLimitFrames: 20 });
  for (let f = 0; f < 40 && battle.observe().result === "ongoing"; f++) {
    battle.step(1 / 60, idle);
  }
  assertEqual(battle.observe().result, "draw", "running-timer timeout -> result 'draw'");
  assertEqual(battle.observe().winnerMask, 4, "running-timer timeout -> winnerMask === 4 (no-winner)");
}

function testOngoingHasNoMask(): void {
  // Fresh battle, both sides alive: no winner yet, no result flip.
  const battle = makeBattle({ team0Human: true, team1Human: false });
  battle.step(1 / 60, idle);
  assertEqual(battle.observe().result, "ongoing", "both sides alive -> result stays 'ongoing'");
  assertEqual(battle.observe().winnerMask ?? 0, 0, "both sides alive -> winnerMask absent/0");
}

function testAllCpuEnemyWipeIsWin(): void {
  // No human owner: a lone survivor "wins" (surviving side), mutual destruction is a draw.
  const battle = makeBattle({ team0Human: false, team1Human: false });
  const enemy = battleStateForSelfcheck(battle).borgs.find((b) => b.team === 1);
  if (!enemy) throw new Error("no enemy borg");
  kill(enemy, profileFor(E1));
  battle.step(1 / 60, idle);
  assertEqual(battle.observe().winnerMask, 1, "all-CPU enemy wipe -> winnerMask === 1");
  assertEqual(battle.observe().result, "win", "all-CPU: lone survivor -> 'win'");
}

// --- Runner ------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testEnemyWipeIsPlayerWin();
  testProjectileObservationAndDespawnFacts();
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
