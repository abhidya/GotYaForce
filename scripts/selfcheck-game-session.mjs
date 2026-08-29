#!/usr/bin/env node
import assert from "node:assert/strict";
import { existsSync, readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const modulePath = path.join(root, "apps/game/src/gameSession.ts");
const mainPath = path.join(root, "apps/game/src/main.ts");

// gameSession.ts runs here as REAL source, together with its real app-local dependencies
// (the ported Challenge-flow VM, the global-menu dispatcher and the generated DOL tables) —
// emitted as a real module graph, so the session exercises the actual ported state machines.
// Only the cross-package @gf/* runtime values are faked, and only the handful it calls.
//
// The old version rewrote imports with one hand-written regex per import statement, pinned
// to the exact named-binding list each import happened to have. The @gf/missions import grew
// past that list, the regex stopped matching, the import survived into a `data:` module, and
// the script died on module resolution — a selfcheck that could not run while still looking
// like coverage in package.json. emitInlineModuleGraph rewrites specifiers by AST position
// and HARD-ERRORS on any dependency that is neither mapped nor stubbed, so the next added
// import fails here with a readable message instead of silently disabling this check.
const graph = emitInlineModuleGraph({
  label: "selfcheck-game-session",
  entry: modulePath,
  outDir: path.join(root, ".tmp", "selfcheck-game-session"),
  stubs: {
    // Types only at runtime.
    "@gf/assets": "export {};",
    // Focused fakes for the cross-package runtime VALUES gameSession calls. Kept
    // deliberately small: a fake that grows into a second implementation stops testing
    // the real one.
    "@gf/combat": [
      "export const DEFAULT_BOUNDS = { x: 500, z: 400 };",
      "export const createBattle = (config, borgStats) => ({ config, borgStats });",
    ].join("\n"),
    "@gf/missions": [
      "export const playerIdFor = (player) => `p${player}`;",
      "export const stageIdForBattleConfig = (config) => config.arena;",
      "export const toCombatBattleConfig = (config, stage) => ({ ...config, stage });",
      "export const CHALLENGE_GROUP_ROSTERS = {};",
      "export const challengeBattleCount = () => 2;",
      "export const challengeStageId = () => 'st00';",
      "export const selectChallengeStage = () => 'st00';",
    ].join("\n"),
  },
});
const { createGameSession, InvalidSessionEventError } = await import(graph.url);
assert.equal(typeof createGameSession, "function", "createGameSession must be the real implementation");

// The global-menu dispatcher logs its per-screen ROM render-state on every front-end
// transition — a browser diagnostic, and ~1500 lines across the routes below. Silence
// console.info ONLY (warnings and errors still surface) so a failure here is readable.
console.info = () => {};

const battle = (index) => ({
  arena: `st0${index}`,
  forces: [
    { team: "player", ownerPlayer: 0, borgIds: ["a"] },
    { team: "enemy", ownerPlayer: null, borgIds: ["enemy"] },
  ],
  label: `BATTLE ${index + 1}`,
  meta: { mode: "challenge", index, enemyGroupChoices: [1, 2] },
});
const result = (outcome) => ({ outcome, attack: 1, hitRatio: 0.5, dodgeRatio: 0.25,
  enemyBorgsDefeated: 1, costWon: 100, playerBorgsDefeated: 0, costLost: 0,
  allyBorgsDefeated: 0, grandTotal: outcome === "WIN" ? 100 : -100 });
const stats = { attack: 1, hitRatio: 50, dodgeRatio: 25, enemyBorgsDefeated: 1,
  enemyTotalCost: 100, playerBorgsDefeated: 0, playerTotalCost: 0, allyBorgsDefeated: 0, grandTotal: 100 };

function fakeRun(options, count = 2, onNext = () => {}) {
  const battles = Array.from({ length: count }, (_, index) => battle(index));
  return { budget: options.budget, mode: 0, playerCount: options.playerCount, battles, total: count,
    current: 0, score: 0, ended: false,
    getCurrentBattle() { return this.ended ? null : this.battles[this.current] ?? null; },
    next(last) {
      onNext(last);
      this.score += last.grandTotal;
      if (last.outcome === "LOSE") { this.ended = true; return { action: "title", nextBattle: null }; }
      this.current += 1;
      if (this.current >= this.total) { this.ended = true; return { action: "complete", nextBattle: null }; }
      return { action: "advance", nextBattle: this.battles[this.current] };
    },
  };
}

function makeSession({
  battles = 2,
  load = async () => ({ renderState: {}, modelUrls: [] }),
  onNext,
  initialForceSlots = [
    { no: 1, name: "ONE", borgIds: ["a"] },
    { no: 2, name: "TWO", borgIds: ["b"] },
  ],
} = {}) {
  // No `configs` option any more: the Challenge VM builds the pending battle config, so a
  // caller-supplied battle list never reached the session and the option only made the
  // harness look like it controlled something it did not.
  return createGameSession({
    initialForceSlots,
    forceFromSlot: (slot) => [...slot.borgIds],
    validForce: (ids) => ids.filter((id) => id !== "bad"),
    createRun: (options) => fakeRun(options, battles, onNext),
    borgs: { borgs: [] }, stageCatalog: {}, borgStats: [], loadStageAssets: load,
  });
}

function toSelectForce(session) {
  session.dispatch({ type: "boot-ready" });
  session.dispatch({ type: "title-enter" });
  session.dispatch({ type: "menu-select", mode: "challenge" });
  session.dispatch({ type: "difficulty-select", budget: 2500 });
  session.dispatch({ type: "players-select", playerCount: 2 });
  session.dispatch({ type: "box-continue" });
  assert.equal(session.snapshot().screen, "select-force");
}

// Every forward and back route.
const navigation = makeSession();
navigation.dispatch({ type: "boot-ready" });
navigation.dispatch({ type: "title-enter" });
navigation.dispatch({ type: "menu-select", mode: "challenge" });
navigation.dispatch({ type: "back" });
assert.equal(navigation.snapshot().screen, "menu");
navigation.dispatch({ type: "menu-select", mode: "challenge" });
navigation.dispatch({ type: "difficulty-select", budget: 1500 });
navigation.dispatch({ type: "back" });
assert.equal(navigation.snapshot().screen, "difficulty");
navigation.dispatch({ type: "difficulty-select", budget: 2500 });
navigation.dispatch({ type: "players-select", playerCount: 2 });
navigation.dispatch({ type: "back" });
assert.equal(navigation.snapshot().screen, "players");
navigation.dispatch({ type: "players-select", playerCount: 2 });
navigation.dispatch({ type: "box-continue" });
navigation.dispatch({ type: "back" });
assert.equal(navigation.snapshot().screen, "load-box");

// Menu force edit return, slot sync/select/edit/update, and briefing back.
let edit = makeSession();
edit.dispatch({ type: "boot-ready" }); edit.dispatch({ type: "title-enter" });
edit.dispatch({ type: "menu-select", mode: "edit-force" });
edit.dispatch({ type: "force-editor-confirm", borgIds: ["saved", "bad"] });
assert.equal(edit.snapshot().screen, "menu");
assert.equal(edit.snapshot().menuMode, "edit-force");
assert.deepEqual(edit.snapshot().forceSlots[0].borgIds, ["saved"]);
edit.dispatch({ type: "menu-select", mode: "challenge" });
edit.dispatch({ type: "back" });
assert.equal(edit.snapshot().screen, "menu");
assert.equal(edit.snapshot().menuMode, "challenge", "back from Difficulty focuses Challenge after Edit Force");
toSelectForce(edit = makeSession());
edit.dispatch({ type: "force-slots-synced", slots: [{ no: 1, name: "ONE", borgIds: ["persisted"] }, { no: 2, name: "TWO", borgIds: ["b"] }] });
edit.dispatch({ type: "force-slot-selected", slotIndex: 1 });
edit.dispatch({ type: "force-slot-edit", slot: edit.snapshot().forceSlots[1] });
edit.dispatch({ type: "force-editor-quit" });
assert.equal(edit.snapshot().screen, "select-force");
edit.dispatch({ type: "force-slot-confirm", slot: edit.snapshot().forceSlots[1] });
assert.equal(edit.snapshot().screen, "briefing");
assert.equal(edit.snapshot().pendingBattleConfig.arena, "st00");
edit.dispatch({ type: "back" });
assert.equal(edit.snapshot().screen, "select-force");

const selectEdit = makeSession(); toSelectForce(selectEdit);
selectEdit.dispatch({ type: "force-slot-edit", slot: selectEdit.snapshot().forceSlots[0] });
selectEdit.dispatch({ type: "force-editor-confirm", borgIds: ["confirmed"] });
assert.equal(selectEdit.snapshot().screen, "select-force", "Force Editor confirm returns to Select Force");
assert.deepEqual(selectEdit.snapshot().forceSlots[0].borgIds, ["confirmed"]);

// Preparation success, default bounds, local ids, failure recovery, retry.
const prepared = makeSession(); toSelectForce(prepared);
prepared.dispatch({ type: "force-slot-confirm", slot: prepared.snapshot().forceSlots[0] });
prepared.dispatch({ type: "briefing-confirm" });
const boot = await prepared.prepareBattle();
assert.deepEqual(boot.stageBounds, { minX: -500, maxX: 500, minZ: -400, maxZ: 400 });
assert.deepEqual(boot.localPlayerIds, ["p0", "p1"]);
prepared.dispatch({ type: "battle-started" });
assert.equal(prepared.snapshot().screen, "battle");

let fail = true;
const retry = makeSession({ load: async () => { if (fail) throw new Error("offline"); return { renderState: {}, modelUrls: [], bounds: { minX: -1, maxX: 1, minZ: -2, maxZ: 2 } }; } });
toSelectForce(retry); retry.dispatch({ type: "force-slot-confirm", slot: retry.snapshot().forceSlots[0] }); retry.dispatch({ type: "briefing-confirm" });
await assert.rejects(retry.prepareBattle(), /offline/);
assert.equal(retry.snapshot().screen, "select-force");
fail = false;
retry.dispatch({ type: "force-slot-confirm", slot: retry.snapshot().forceSlots[0] }); retry.dispatch({ type: "briefing-confirm" });
assert.deepEqual((await retry.prepareBattle()).stageBounds, { minX: -1, maxX: 1, minZ: -2, maxZ: 2 });

async function enterBattle(session) {
  toSelectForce(session); session.dispatch({ type: "force-slot-confirm", slot: session.snapshot().forceSlots[0] });
  session.dispatch({ type: "briefing-confirm" }); await session.prepareBattle(); session.dispatch({ type: "battle-started" });
}

// Run routing, as the ported Challenge VM actually drives it (gameSession settleWin /
// rebuildAfterWin). These expectations were rewritten on 2026-08-29: while this script
// could not execute, gameSession moved to the VM's mode-4 post-battle gate and an
// INTERMEDIATE win stopped showing a per-battle Results screen — the ROM shows none — so
// it now tears the battle down and returns straight to the briefing. The old assertions
// still described the pre-VM routing and had never once run against the code.
//
// Intermediate win: no Results, straight back to the briefing, battle torn down.
const wins = makeSession(); await enterBattle(wins);
const intermediateWin = wins.dispatch({ type: "battle-resolved", battleResults: result("WIN"), stats, drops: [] });
assert.deepEqual(
  intermediateWin.map((effect) => effect.type),
  ["teardown-battle", "render"],
  "an intermediate win tears the battle down before rendering the next briefing",
);
assert.equal(wins.snapshot().screen, "briefing", "an intermediate win returns to the briefing, not Results");
assert.throws(() => wins.dispatch({ type: "advance" }), InvalidSessionEventError, "no advance to consume at the briefing");
// Final win of the run (the VM reaches CLEAR): Results, then Gets for the drops, then menu.
wins.dispatch({ type: "briefing-confirm" }); await wins.prepareBattle(); wins.dispatch({ type: "battle-started" });
wins.dispatch({ type: "battle-resolved", battleResults: result("WIN"), stats, drops: [{ borgId: "x", kind: "unit", partIndex: 0 }] });
assert.equal(wins.snapshot().screen, "results", "the run-clearing win shows Results");
wins.dispatch({ type: "advance" }); assert.equal(wins.snapshot().screen, "gets");
wins.dispatch({ type: "advance" }); assert.equal(wins.snapshot().screen, "menu");

// A loss always ends the run: Results (VM mode 6 FAIL), then out to the menu.
const loss = makeSession(); await enterBattle(loss);
loss.dispatch({ type: "battle-resolved", battleResults: result("LOSE"), stats, drops: [] });
assert.equal(loss.snapshot().screen, "results", "a loss shows Results");
loss.dispatch({ type: "advance" }); assert.equal(loss.snapshot().screen, "menu");

const abandoned = makeSession(); await enterBattle(abandoned);
const abandonEffects = abandoned.dispatch({ type: "battle-abandoned" });
assert.deepEqual(abandonEffects.map((effect) => effect.type), ["teardown-battle", "render"]);
assert.equal(abandoned.snapshot().screen, "menu");

// Snapshot/event ingress values are isolated deeply from callers and later mutations.
const initialSlots = [{ no: 1, name: "CALLER", borgIds: ["a"] }];
const slotIsolation = makeSession({ initialForceSlots: initialSlots });
initialSlots[0].name = "MUTATED";
initialSlots[0].borgIds[0] = "mutated";
let isolatedSnapshot = slotIsolation.snapshot();
isolatedSnapshot.forceSlots[0].name = "snapshot-mutated";
isolatedSnapshot.forceSlots[0].borgIds[0] = "snapshot-mutated";
assert.equal(slotIsolation.snapshot().forceSlots[0].name, "CALLER");
assert.deepEqual(slotIsolation.snapshot().forceSlots[0].borgIds, ["a"]);

// Battle-config isolation. NOTE (2026-08-29): the first battle's config is now built by the
// ported Challenge VM (gameSession applyVmBattleBuild), NOT taken from the run's battle
// list, so the old half of this check — "mutate the config object the caller handed to
// createRun" — no longer has a path into the session at all. What still matters, and what
// this now checks, is that neither a returned SNAPSHOT nor a returned PREPARED boot is a
// live handle on session state.
let loadedStage = null;
const configIsolation = makeSession({
  load: async (stageId) => { loadedStage = stageId; return { renderState: {}, modelUrls: [] }; },
});
toSelectForce(configIsolation);
configIsolation.dispatch({ type: "force-slot-confirm", slot: configIsolation.snapshot().forceSlots[0] });
const builtConfig = configIsolation.snapshot().pendingBattleConfig;
assert.equal(builtConfig.arena, "st00", "the VM built the pending battle config");
assert.deepEqual(builtConfig.forces[0].borgIds, ["a"], "the player force comes from the selected slot");
isolatedSnapshot = configIsolation.snapshot();
isolatedSnapshot.pendingBattleConfig.arena = "snapshot-mutated";
isolatedSnapshot.pendingBattleConfig.forces[0].borgIds[0] = "snapshot-mutated";
isolatedSnapshot.pendingBattleConfig.label = "snapshot-mutated";
assert.equal(configIsolation.snapshot().pendingBattleConfig.arena, "st00");
assert.deepEqual(configIsolation.snapshot().pendingBattleConfig.forces[0].borgIds, ["a"]);
assert.equal(configIsolation.snapshot().pendingBattleConfig.label, builtConfig.label);
configIsolation.dispatch({ type: "briefing-confirm" });
const isolatedBoot = await configIsolation.prepareBattle();
assert.equal(loadedStage, "st00", "snapshot mutation cannot redirect preparation");
assert.equal(isolatedBoot.config.arena, "st00");
isolatedBoot.config.arena = "prepared-mutated";
assert.equal(configIsolation.snapshot().pendingBattleConfig.arena, "st00");

// Result/drop ingress isolation. The intermediate win scores through run.next() and clears
// postBattle (no per-battle Results), so the ingress copy is checked on THAT hop; the
// surviving postBattle snapshot is checked on the run-clearing win that follows.
let nextInput = null;
const resultIsolation = makeSession({ onNext: (last) => { nextInput = { ...last }; } });
await enterBattle(resultIsolation);
const callerResult = result("WIN");
resultIsolation.dispatch({ type: "battle-resolved", battleResults: callerResult, stats, drops: [] });
callerResult.outcome = "LOSE";
callerResult.grandTotal = -999;
assert.equal(nextInput.outcome, "WIN", "a caller mutating its result object after dispatch cannot rescore the run");
assert.equal(nextInput.grandTotal, 100);
assert.equal(resultIsolation.snapshot().screen, "briefing", "mutated caller result cannot turn win into loss");

resultIsolation.dispatch({ type: "briefing-confirm" });
await resultIsolation.prepareBattle();
resultIsolation.dispatch({ type: "battle-started" });
const finalResult = result("WIN");
const callerDrops = [{ borgId: "drop", kind: "unit", partIndex: 0 }];
resultIsolation.dispatch({ type: "battle-resolved", battleResults: finalResult, stats, drops: callerDrops });
finalResult.outcome = "LOSE";
finalResult.grandTotal = -999;
callerDrops[0].borgId = "caller-mutated";
isolatedSnapshot = resultIsolation.snapshot();
isolatedSnapshot.postBattle.battleResults.outcome = "LOSE";
isolatedSnapshot.postBattle.battleResults.grandTotal = -888;
isolatedSnapshot.postBattle.stats.grandTotal = -777;
isolatedSnapshot.postBattle.drops[0].borgId = "snapshot-mutated";
assert.equal(resultIsolation.snapshot().postBattle.battleResults.outcome, "WIN");
assert.equal(resultIsolation.snapshot().postBattle.battleResults.grandTotal, 100);
assert.equal(resultIsolation.snapshot().postBattle.stats.grandTotal, 100);
assert.equal(resultIsolation.snapshot().postBattle.drops[0].borgId, "drop");
resultIsolation.dispatch({ type: "advance" });
assert.equal(resultIsolation.snapshot().screen, "gets");
resultIsolation.dispatch({ type: "advance" });
assert.equal(resultIsolation.snapshot().screen, "menu");

assert.throws(() => loss.dispatch({ type: "back" }), InvalidSessionEventError);
assert.throws(() => makeSession().dispatch({ type: "force-slot-selected", slotIndex: 9 }), InvalidSessionEventError);

// Static architecture guard.
const main = readFileSync(mainPath, "utf8");
assert.doesNotMatch(main, /\b(?:const|let)\s+flow\b/, "main has no global flow object");
assert.doesNotMatch(main, /function\s+show(?:TitleIntro|Menu|Difficulty|Players|LoadBoxData|SelectForce|ForceBuilder|BattleIntro|Results|Gets)\b/, "main has no showX transition cluster");
assert.doesNotMatch(main, /from\s+["']\.\/sim\/battleBootstrap\.js["']/, "main does not import battleBootstrap");
assert.equal(existsSync(path.join(root, "apps/game/src/sim/battleBootstrap.ts")), false, "battleBootstrap deleted");

console.log("game-session selfcheck PASS: transitions/abandon, edits/menu focus, isolated snapshots/ingress, run routing, preparation/retry, invalid events, static guard");
