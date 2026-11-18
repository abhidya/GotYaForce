import { battleStateForSelfcheck, createBattle, HUSK_BORG_ID } from "./battle.js";
import { STATE } from "./constants.js";
import { emptyInput } from "./types.js";
import type { BorgStats } from "./stats.js";
import data from "../../assets/data/borgs.json" with { type: "json" };

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[challengeHusk] ${message}`);
}
export function runChallengeHuskSelfTest(): void {
  const battle = createBattle({ stageId: "st00", bounds: { x: 5000, z: 5000 }, forces: [
    {team: 0, ownerPlayer: "p1", borgIds: ["pl0615"]},
    {team: 1, ownerPlayer: null, borgIds: ["pl0008"]},
    {team: 1, ownerPlayer: null, borgIds: ["pl0008"]},
  ], spawnPoints: [{pos:{x:-4000,y:10,z:-4000}}, {pos:{x:4000,y:10,z:4000}},
    {pos:{x:4000,y:10,z:0}}]}, (data as {borgs: BorgStats[]}).borgs);
  const input = {p1: emptyInput()};
  for (let i=0; i<=STATE.SPAWN_DURATION; i++) battle.step(1/60, input);
  const enemies = battleStateForSelfcheck(battle).borgs.filter(b => b.team === 1 && b.alive);
  assert(enemies.length === 2, "two enemy forces initially active");
  enemies[0]!.hp = 0;
  for (let i=0; i<STATE.DEATH_DURATION+30; i++) battle.step(1/60, input);
  const afterFirst = battleStateForSelfcheck(battle);
  assert(afterFirst.result === "ongoing", "one surviving enemy keeps the battle active");
  assert(!afterFirst.borgs.some(b => b.team === 1 && b.borgId === HUSK_BORG_ID),
    "an exhausted CPU enemy force never respawns a human husk");
  assert(afterFirst.borgs.filter(b => b.team === 1 && b.alive).length === 1,
    "only the remaining enemy force stays active");
  enemies[1]!.hp = 0;
  for (let i=0; i<STATE.DEATH_DURATION+30 && battle.observe().result === "ongoing"; i++) battle.step(1/60, input);
  assert(battle.observe().result === "win", "last enemy death settles a player win");
  // The rule is controller-scoped, not team-scoped: a CPU ally must not get a husk either.
  const allyBattle = createBattle({ stageId: "st00", bounds: {x:5000,z:5000}, forces: [
    {team:0, ownerPlayer:"p1", borgIds:["pl0615"]},
    {team:0, ownerPlayer:null, borgIds:["pl0008"]},
    {team:1, ownerPlayer:null, borgIds:["pl0008"]},
  ]}, (data as {borgs:BorgStats[]}).borgs);
  for (let i=0; i<=STATE.SPAWN_DURATION; i++) allyBattle.step(1/60, input);
  const ally = battleStateForSelfcheck(allyBattle).borgs.find(b => b.team === 0 && b.ownerPlayer === null)!;
  ally.hp = 0;
  for (let i=0; i<STATE.DEATH_DURATION+30; i++) allyBattle.step(1/60, input);
  assert(!battleStateForSelfcheck(allyBattle).borgs.some(b => b.team === 0 && b.borgId === HUSK_BORG_ID),
    "an exhausted CPU ally does not respawn a player husk");

  // Preserve the player-facing rule when another same-team force still fights.
  const humanBattle = createBattle({ stageId:"st00", bounds:{x:5000,z:5000}, forces:[
    {team:0,ownerPlayer:"p1",borgIds:["pl0615"]},
    {team:0,ownerPlayer:"p2",borgIds:["pl0008"]},
    {team:1,ownerPlayer:null,borgIds:["pl0008"]},
  ]}, (data as {borgs:BorgStats[]}).borgs);
  const twoInputs = {p1:emptyInput(),p2:emptyInput()};
  for (let i=0; i<=STATE.SPAWN_DURATION; i++) humanBattle.step(1/60, twoInputs);
  battleStateForSelfcheck(humanBattle).borgs.find(b => b.ownerPlayer === "p1")!.hp = 0;
  for (let i=0; i<STATE.DEATH_DURATION+30; i++) humanBattle.step(1/60, twoInputs);
  assert(battleStateForSelfcheck(humanBattle).borgs.some(b => b.ownerPlayer === "p1" && b.borgId === HUSK_BORG_ID),
    "an exhausted human player still receives a husk while a teammate fights");
  console.log("[challengeHusk] CPU exhaustion, human husk and final win PASS");
}
