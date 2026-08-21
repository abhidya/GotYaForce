import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { applyHit } from "./combat.js";
import { STATE } from "./constants.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { emptyInput, type Battle, type BorgRuntime, type PlayerInput } from "./types.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`[lifecycle.selftest] ${message}`);
}

function loadStats(): BorgStats[] {
  return (borgsData as { borgs: BorgStats[] }).borgs;
}

const IDLE: PlayerInput = emptyInput();

function setupBattle(
  stats: readonly BorgStats[],
  replacement: boolean,
  timeLimitFrames?: number,
): {
  battle: Battle;
  victim: BorgRuntime;
  attacker: BorgRuntime;
  inputs: Record<string, PlayerInput>;
} {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        {
          team: 0,
          ownerPlayer: "p1",
          borgIds: replacement ? ["pl0615", "pl000c"] : ["pl0615"],
        },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: 40, z: 40 },
      ...(timeLimitFrames !== undefined ? { timeLimitFrames } : {}),
    },
    stats,
  );
  const inputs = { p1: IDLE, p2: IDLE };
  for (let frame = 0; frame <= STATE.SPAWN_DURATION; frame += 1) {
    battle.step(1 / 60, inputs);
  }
  const state = battleStateForSelfcheck(battle);
  const victim = state.borgs.find((actor) => actor.team === 0);
  const attacker = state.borgs.find((actor) => actor.team === 1);
  assert(victim, "missing ported-family victim");
  assert(attacker, "missing attacker");
  assert(victim.romDriver, "G RED did not receive a RomDriverBridge");
  assert(victim.state === "idle", `victim did not finish deployment: ${victim.state}`);
  return { battle, victim, attacker, inputs };
}

function killDuringRomSpecial(
  stats: readonly BorgStats[],
  victim: BorgRuntime,
  attacker: BorgRuntime,
): void {
  const stateActors = [victim, attacker];
  const started = victim.romDriver?.tryStartXSpecial(victim, stateActors);
  assert(started === true, "ported ROM special did not take action ownership");
  assert(victim.cooldowns["romSpecialActive"] === 1, "ROM ownership latch was not armed");

  const victimStats = stats.find((entry) => entry.id === victim.borgId);
  const attackerStats = stats.find((entry) => entry.id === attacker.borgId);
  assert(victimStats, `missing stats for ${victim.borgId}`);
  assert(attackerStats, `missing stats for ${attacker.borgId}`);
  victim.hp = 1;
  victim.invincTimer = 0;
  const damage = applyHit(
    victim,
    buildProfile(victimStats),
    1,
    0,
    { x: 1, y: 0, z: 0 },
    attacker.pos,
    true,
    undefined,
    {
      attacker,
      attackerProfile: buildProfile(attackerStats),
      aimedTargetUid: victim.uid,
    },
  );
  assert(damage > 0, "lethal hit dealt no damage");
  assert(victim.hp === 0 && victim.state === "death", "lethal hit did not enter death");
}

function assertReplacementAndExactlyOnceAccounting(stats: readonly BorgStats[]): void {
  const { battle, victim, attacker, inputs } = setupBattle(stats, true);
  killDuringRomSpecial(stats, victim, attacker);

  battle.step(1 / 60, inputs);
  let state = battleStateForSelfcheck(battle);
  assert(victim.state === "death" && victim.stateTime === 1, "ROM ownership consumed death frame 1");
  assert(victim.cooldowns["romSpecialActive"] === 0, "lethal lifecycle did not cancel ROM ownership");
  assert(victim.defeatAccounted, "kill event was not force-accounted");

  for (let frame = 1; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    battle.step(1 / 60, inputs);
  }
  state = battleStateForSelfcheck(battle);
  const replacement = state.borgs.find((actor) => actor.team === 0 && actor.uid !== victim.uid);
  const victimCost = buildProfile(stats.find((entry) => entry.id === victim.borgId)!).energy;
  const replacementCost = buildProfile(stats.find((entry) => entry.id === "pl000c")!).energy;

  assert(!victim.alive, "death lifecycle never reached alive=false");
  assert(replacement?.borgId === "pl000c", "next force member was not deployed");
  assert(state.result === "ongoing", `replacement battle settled early as ${state.result}`);
  assert(state.energy[0] === replacementCost, "force energy did not retain exactly the replacement cost");
  assert(state.defeated[0] === 1, "defeated count was not exactly one");
  assert(state.defeatedEnergy[0] === victimCost, "defeated energy was not exactly the victim cost");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "defeat list duplicated victim");
  assert(victim.deaths === 1, "ROM death accounting ran more or less than once");
  assert(attacker.kills === 1, "killer accounting ran more or less than once");
  assert(state.telemetry?.slots?.p2?.kills === 1, "persistent killer slot was not credited exactly once");
  assert(state.telemetry?.slots?.p1?.costLost === victimCost, "victim slot lost the wrong force cost");

  for (let frame = 0; frame < 10; frame += 1) battle.step(1 / 60, inputs);
  state = battleStateForSelfcheck(battle);
  assert(state.defeated[0] === 1, "defeated count changed after deployment");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "defeat list changed after deployment");
}

function assertFinalDeathSettlesResult(stats: readonly BorgStats[]): void {
  const { battle, victim, attacker, inputs } = setupBattle(stats, false);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5; frame += 1) {
    battle.step(1 / 60, inputs);
    if (battle.observe().result !== "ongoing") break;
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "final death settled the result before alive=false");
  assert(state.energy[0] === 0, "destroyed force retained energy");
  assert(state.result === "lose", `final death did not settle player loss: ${state.result}`);
  assert(state.defeated[0] === 1, "final defeat was not counted exactly once");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "final defeat list duplicated victim");
}

function assertFinalKillNearTimeoutFinishesDeathFirst(stats: readonly BorgStats[]): void {
  const timeoutFrame = STATE.SPAWN_DURATION + 2;
  const { battle, victim, attacker, inputs } = setupBattle(stats, false, timeoutFrame);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    const observation = battle.step(1 / 60, inputs);
    if (victim.alive) {
      assert(observation.result === "ongoing", `timeout preempted pending final death as ${observation.result}`);
    }
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "final kill near timeout never completed death lifecycle");
  assert(state.result === "lose", `final kill near timeout settled as ${state.result}`);
  assert(state.winnerMask === 2, `final kill near timeout produced winner mask ${String(state.winnerMask)}`);
  assert(state.defeated[0] === 1, "final kill near timeout was not counted exactly once");
}

function assertReplacementNearTimeoutDeploysBeforeDraw(stats: readonly BorgStats[]): void {
  const timeoutFrame = STATE.SPAWN_DURATION + 2;
  const { battle, victim, attacker, inputs } = setupBattle(stats, true, timeoutFrame);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    const observation = battle.step(1 / 60, inputs);
    if (victim.alive) {
      assert(observation.result === "ongoing", `timeout preempted replacement death as ${observation.result}`);
    }
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "replacement kill near timeout never completed death lifecycle");
  const replacement = state.borgs.find((actor) => actor.team === 0 && actor.uid !== victim.uid);
  const replacementCost = buildProfile(stats.find((entry) => entry.id === "pl000c")!).energy;
  assert(replacement?.borgId === "pl000c", "timeout settled before replacement deployment");
  assert(state.energy[0] === replacementCost, "replacement energy was not recomputed before timeout");
  assert(state.result === "draw", `replacement near timeout did not settle draw: ${state.result}`);
  assert(state.winnerMask === 4, `replacement timeout produced winner mask ${String(state.winnerMask)}`);
  assert(state.defeated[0] === 1, "replacement timeout defeat was not counted exactly once");
}

function assertNonRomAirborneDeathKeepsGravity(stats: readonly BorgStats[]): void {
  const { battle, victim, inputs } = setupBattle(stats, false);
  victim.romDriver = null;
  victim.hp = 0;
  victim.state = "death";
  victim.stateTime = 0;
  victim.pos.y = 100;
  victim.vel.y = -2;
  victim.grounded = false;
  const beforeY = victim.pos.y;
  const beforeVelocityY = victim.vel.y;

  battle.step(1 / 60, inputs);
  assert(victim.stateTime === 1, "non-ROM death lifecycle did not advance exactly one frame");
  assert(victim.vel.y < beforeVelocityY, "non-ROM airborne death did not apply gravity");
  assert(victim.pos.y < beforeY, "non-ROM airborne death did not integrate vertical position");
}

export function runSelfTest(): void {
  const stats = loadStats();
  assertReplacementAndExactlyOnceAccounting(stats);
  assertFinalDeathSettlesResult(stats);
  assertFinalKillNearTimeoutFinishesDeathFirst(stats);
  assertReplacementNearTimeoutDeploysBeforeDraw(stats);
  assertNonRomAirborneDeathKeepsGravity(stats);
  console.log("[lifecycle.selftest] PASS: lethal ROM ownership interruption, deployment, accounting, and result settlement");
}

if (import.meta.url === `file://${process.argv[1]}` || process.argv[1]?.endsWith("lifecycle.selftest.js")) {
  runSelfTest();
}
