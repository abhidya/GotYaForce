#!/usr/bin/env node
import assert from "node:assert/strict";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const scratch = path.join(root, ".tmp", "selfcheck-challenge-restart");
const combatStub = "export const DEFAULT_BOUNDS = { x: 500, z: 400 }; export const createBattle = (config) => ({ config });";
function emit(name, entry, stubs = {}) {
  return emitInlineModuleGraph({ label: `challenge-restart-${name}`, entry: path.join(root, entry),
    outDir: path.join(scratch, name), stubs });
}

// Real mission progression, scoring and reference tables, not the two-battle fake
// used by the navigation selfcheck. The app's VM and generated tables are real too.
// Only combat construction and asset loading are replaced: this tests navigation
// and progression, not rendering, combat outcomes or retail navigation parity.
const challengeGraph = emit("missions", "packages/missions/src/challenge.ts");
const referenceGraph = emit("reference", "packages/missions/src/challenge-reference.ts");
const configGraph = emit("config", "packages/missions/src/combat-config.ts", { "@gf/combat": combatStub });
const sessionGraph = emit("session", "apps/game/src/gameSession.ts", {
  "@gf/assets": "export {};",
  "@gf/combat": combatStub,
  "@gf/missions": [challengeGraph, referenceGraph, configGraph]
    .map((graph) => `export * from ${JSON.stringify(graph.url)};`).join("\n"),
});
const { createGameSession } = await import(sessionGraph.url);
const { createChallengeRun } = await import(challengeGraph.url);
const { CHALLENGE_GROUP_ROSTERS, challengeBattleCount } = await import(referenceGraph.url);
// Synthetic positive costs for real roster IDs keep CPU assembly meaningful without
// requiring extracted game assets. Neither battle totals nor progress are synthetic.
const borgs = [...new Set(Object.values(CHALLENGE_GROUP_ROSTERS).flat())]
  .map((id) => ({ id, name: id, energy: 200, tribe: "fixture" }));
const slots = [0, 1].map((i) => ({ no: i + 1, name: `FORCE ${i + 1}`, borgIds: [borgs[i].id] }));
const winResult = { outcome: "WIN", attack: 1, hitRatio: 0.5, dodgeRatio: 0.25,
  enemyBorgsDefeated: 1, costWon: 200, playerBorgsDefeated: 0, costLost: 0,
  allyBorgsDefeated: 0, grandTotal: 100 };
const stats = { attack: 1, hitRatio: 50, dodgeRatio: 25, enemyBorgsDefeated: 1,
  enemyTotalCost: 200, playerBorgsDefeated: 0, playerTotalCost: 0, allyBorgsDefeated: 0, grandTotal: 100 };
const budgets = [1500, 2000, 2500];

function makeSession() {
  return createGameSession({ initialForceSlots: slots, forceFromSlot: (slot) => [...slot.borgIds],
    validForce: (ids) => [...ids], createRun: createChallengeRun, borgs, borgStats: borgs,
    stageCatalog: { defaultStageId: "st00", hasStageCollision: () => true },
    loadStageAssets: async () => ({ renderState: {}, modelUrls: [] }) });
}
function confirmForce(session) {
  session.dispatch({ type: "force-slot-confirm", slot: session.snapshot().forceSlots[0] });
}
function enter(session, mode, players) {
  for (const event of [{ type: "boot-ready" }, { type: "title-enter" },
    { type: "menu-select", mode: "challenge" }, { type: "difficulty-select", budget: budgets[mode] },
    { type: "players-select", playerCount: players }, { type: "box-continue" }]) session.dispatch(event);
  confirmForce(session);
}
function assertBriefing(session, index, mode, players, score) {
  const state = session.snapshot();
  assert.equal(state.screen, "briefing");
  assert.equal(state.pendingBattleConfig.meta.index, index, "VM and mission index must agree");
  assert.equal(state.pendingBattleConfig.label, `BATTLE ${index + 1} VS`);
  assert.equal(state.run.current, index);
  assert.equal(state.run.total, challengeBattleCount(mode));
  assert.equal(state.run.score, score);
  assert.equal(state.run.ended, false);
  assert.equal(state.pendingBattleConfig.meta.challengeMode, mode);
  assert.deepEqual(state.pendingBattleConfig.forces.filter((f) => f.ownerPlayer !== null)
    .map((f) => f.ownerPlayer), Array.from({ length: players }, (_, i) => i));
}
async function startBattle(session, players) {
  session.dispatch({ type: "briefing-confirm" });
  const prepared = await session.prepareBattle();
  assert.deepEqual(prepared.localPlayerIds, Array.from({ length: players }, (_, i) => `p${i}`));
  session.dispatch({ type: "battle-started" });
}
async function win(session, players, drops = []) {
  await startBattle(session, players);
  session.dispatch({ type: "battle-resolved", battleResults: winResult, stats, drops });
}
async function completeRun(session, mode, players, withDrop = false) {
  const total = challengeBattleCount(mode);
  for (let i = 0; i < total; i += 1) {
    assertBriefing(session, i, mode, players, i * 100);
    await win(session, players, withDrop && i === total - 1
      ? [{ borgId: borgs[0].id, kind: "unit", partIndex: 0 }] : []);
  }
  assert.equal(session.snapshot().screen, "results", "CLEAR after exactly the selected number of battles");
  session.dispatch({ type: "advance" });
  if (withDrop) {
    assert.equal(session.snapshot().screen, "gets");
    session.dispatch({ type: "advance" });
  }
  const state = session.snapshot();
  assert.equal(state.screen, "menu", "CLEAR must not launch a fallback extra battle");
  assert.equal(state.pendingBattleConfig, null);
  assert.equal(state.run.current, total);
  assert.equal(state.run.score, total * 100, "new run score excludes victories before restart");
  assert.equal(state.run.ended, true);
}

const originalInfo = console.info;
console.info = () => {};
try {
  // The existing port restarts its host run on force confirmation. Repeated Back
  // after victories must restart the VM too, not preserve the old battle index.
  for (const mode of [0, 1, 2]) for (const players of [1, 2]) {
    const session = makeSession();
    enter(session, mode, players);
    for (let repeat = 0; repeat < 2; repeat += 1) {
      await win(session, players);
      assertBriefing(session, 1, mode, players, 100);
      session.dispatch({ type: "back" });
      confirmForce(session);
      assertBriefing(session, 0, mode, players, 0);
    }
    await completeRun(session, mode, players, players === 2);
  }
  // Back all the way to difficulty, then change both settings before confirming.
  for (const [from, to, players] of [[2, 0, 2], [0, 1, 1], [1, 2, 2]]) {
    const session = makeSession();
    enter(session, from, players === 1 ? 2 : 1);
    await win(session, players === 1 ? 2 : 1);
    for (let i = 0; i < 4; i += 1) session.dispatch({ type: "back" });
    assert.equal(session.snapshot().screen, "difficulty");
    session.dispatch({ type: "difficulty-select", budget: budgets[to] });
    session.dispatch({ type: "players-select", playerCount: players });
    session.dispatch({ type: "box-continue" });
    confirmForce(session);
    await completeRun(session, to, players);
  }
  // Uninterrupted victory and existing loss/abandon exits still behave normally.
  const normal = makeSession();
  enter(normal, 0, 1);
  await completeRun(normal, 0, 1);
  for (const exit of ["loss", "abandon"]) {
    const session = makeSession();
    enter(session, 0, 1);
    await win(session, 1);
    await startBattle(session, 1);
    if (exit === "loss") {
      session.dispatch({ type: "battle-resolved", battleResults: { ...winResult, outcome: "LOSE", grandTotal: -50 }, stats, drops: [] });
      assert.equal(session.snapshot().screen, "results");
      session.dispatch({ type: "advance" });
      assert.equal(session.snapshot().run.score, 50);
      assert.equal(session.snapshot().run.ended, true);
    } else session.dispatch({ type: "battle-abandoned" });
    assert.equal(session.snapshot().screen, "menu");
    assert.equal(session.snapshot().pendingBattleConfig, null);
  }
} finally {
  console.info = originalInfo;
}
console.log("challenge-restart integration PASS: 6 repeated restart campaigns, 3 settings-change campaigns, normal/loss/abandon exits (real mission run + VM)");
