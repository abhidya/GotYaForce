import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import vm from "node:vm";
import test from "node:test";
import { execFileSync } from "node:child_process";
import { fileURLToPath } from "node:url";
import ts from "typescript";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
// Optional negative control executes a prior revision without changing the checkout.
const read = name => process.env.BGM_TEST_BASE_REF
  ? execFileSync("git", ["show", `${process.env.BGM_TEST_BASE_REF}:${name}`], { cwd: root, encoding: "utf8" })
  : fs.readFileSync(path.join(root, name), "utf8");
const main = ts.createSourceFile("main.ts", read("apps/game/src/main.ts"), ts.ScriptTarget.Latest, true);
const functionNames = ["queueBgm", "playPendingBgm"];
const variableNames = ["activeBgmKey", "pendingBgmKey", "requestedBgmKey", "bgmGeneration", "bgmAttempt"];
const nodes = main.statements.filter(n =>
  (ts.isFunctionDeclaration(n) && functionNames.includes(n.name?.text)) ||
  (ts.isVariableStatement(n) && n.declarationList.declarations.some(d => variableNames.includes(d.name.getText(main)))));
for (const name of functionNames) assert.ok(nodes.some(n => ts.isFunctionDeclaration(n) && n.name?.text === name), name);
const compile = source => ts.transpileModule(source, {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.CommonJS },
}).outputText;
const hostCode = compile(nodes.map(n => n.getText(main)).join("\n") + `
async function initAudio() { return getManager(); }
globalThis.queue = queueBgm;
globalThis.retry = playPendingBgm;
globalThis.state = () => ({ active: activeBgmKey, pending: pendingBgmKey });`);
const audioSource = ts.createSourceFile("index.ts", read("packages/audio/src/index.ts"), ts.ScriptTarget.Latest, true);
// Only remove the unrelated cue resolver re-export. All manager logic is real.
const audioCode = compile(audioSource.statements.filter(n => !ts.isExportDeclaration(n)).map(n => n.getText(audioSource)).join("\n"));
const flush = async () => { for (let i = 0; i < 16; i++) await Promise.resolve(); };
function deferred() {
  let resolve, reject;
  const promise = new Promise((a, b) => { resolve = a; reject = b; });
  return { promise, resolve, reject };
}
async function harness({ abortOnLoad = true, delayedInit = false, noManager = false } = {}) {
  const elements = [];
  // No network/media assets: fake just the asynchronous HTMLAudioElement boundary.
  class Audio {
    constructor(src) { this.src = src; this.dataset = {}; this.paused = true; elements.push(this); }
    play() { this.playback = deferred(); return this.playback.promise; }
    succeed() { if (this.src) this.paused = false; this.playback.resolve(); }
    fail() { this.playback.reject(new Error("NotAllowedError or media load failure")); }
    pause() { this.paused = true; }
    load() { if (abortOnLoad) this.playback?.reject(new Error("AbortError")); }
  }
  const context = vm.createContext({ exports: {}, Audio, URL });
  vm.runInContext(audioCode, context);
  const manager = noManager ? null : await context.exports.createAudioManager({
    manifest: { files: ["menu", "battle"].map(key => ({ key, type: "bgm", path: `${key}.wav` })) },
    baseUrl: "http://audio-test.invalid/",
  });
  const init = deferred();
  let waitForInit = delayedInit;
  let managerCalls = 0;
  context.getManager = () => { managerCalls++; return waitForInit ? init.promise : Promise.resolve(manager); };
  vm.runInContext(hostCode, context);
  return {
    elements, queue: context.queue, retry: context.retry, init: () => init.resolve(manager),
    blockInit: () => { waitForInit = true; }, managerCalls: () => managerCalls,
    state: () => JSON.parse(JSON.stringify(context.state())),
    audible: () => elements.filter(e => !e.paused).map(e => e.dataset.gfAudioKey),
    last: () => elements.at(-1),
    async playing(key) { context.queue(key); await flush(); elements.at(-1).succeed(); await flush(); },
  };
}

test("menu returns while battle play is pending", async () => {
  const h = await harness(); await h.playing("menu");
  h.queue("battle"); await flush(); h.queue("menu"); await flush(); h.last().succeed(); await flush();
  assert.deepEqual(h.audible(), ["menu"]);
  assert.deepEqual(h.state(), { active: "menu", pending: null });
});

test("failed battle start does not leave a falsely active menu", async () => {
  const h = await harness(); await h.playing("menu");
  h.queue("battle"); await flush(); h.last().fail(); await flush();
  h.queue("menu"); await flush(); h.last().succeed(); await flush();
  assert.deepEqual(h.audible(), ["menu"]);
});

test("repeated gestures and same-key queues coalesce while playback is pending", async () => {
  const h = await harness(); h.queue("battle"); await flush();
  for (let i = 0; i < 20; i++) { h.retry(); h.queue("battle"); await flush(); }
  assert.equal(h.elements.length, 1);
  h.last().succeed(); await flush(); assert.deepEqual(h.audible(), ["battle"]);
});

test("already playing track is not restarted by same-key queues", async () => {
  const h = await harness(); await h.playing("menu");
  h.queue("menu"); await h.retry(); await flush();
  assert.equal(h.elements.length, 1); assert.deepEqual(h.audible(), ["menu"]);
});

test("autoplay rejection remains pending and retries on the next gesture", async () => {
  const h = await harness(); h.queue("menu"); await flush(); h.last().fail(); await flush();
  assert.deepEqual(h.state(), { active: null, pending: "menu" });
  h.retry(); await flush(); assert.equal(h.elements.length, 2);
  h.last().succeed(); await flush(); assert.deepEqual(h.state(), { active: "menu", pending: null });
});

for (const outcome of ["succeed", "fail"]) {
  test(`stale ${outcome} cannot change newer completed playback`, async () => {
    const h = await harness({ abortOnLoad: false });
    h.queue("menu"); await flush(); const old = h.last();
    h.queue("battle"); await flush(); h.last().succeed(); await flush();
    old[outcome](); await flush();
    assert.deepEqual(h.state(), { active: "battle", pending: null });
    assert.deepEqual(h.audible(), ["battle"]);
  });
}

test("rapid A to B to A ignores both stale completion generations", async () => {
  const h = await harness({ abortOnLoad: false });
  h.queue("menu"); await flush(); const a = h.last();
  h.queue("battle"); await flush(); const b = h.last();
  h.queue("menu"); await flush(); const final = h.last();
  a.succeed(); b.fail(); await flush();
  assert.deepEqual(h.state(), { active: null, pending: "menu" });
  h.retry(); await flush(); assert.equal(h.elements.length, 3);
  final.succeed(); await flush(); assert.deepEqual(h.audible(), ["menu"]);
});

test("new requests are not blocked behind pending obsolete playback", async () => {
  const h = await harness({ abortOnLoad: false });
  h.queue("menu"); await flush(); h.queue("battle"); await flush();
  assert.equal(h.elements.length, 2); assert.equal(h.last().dataset.gfAudioKey, "battle");
  h.last().succeed(); await flush(); assert.deepEqual(h.state(), { active: "battle", pending: null });
});

test("manifest initialization only starts the latest requested track", async () => {
  const h = await harness({ delayedInit: true });
  h.queue("menu"); h.retry(); h.queue("battle"); h.retry(); h.init(); await flush();
  assert.equal(h.elements.length, 1); assert.equal(h.last().dataset.gfAudioKey, "battle");
  h.last().succeed(); await flush(); assert.deepEqual(h.state(), { active: "battle", pending: null });
});

test("null manager stays silent and releases the in-flight attempt", async () => {
  const h = await harness({ noManager: true });
  h.queue("menu"); await flush(); await h.retry();
  assert.deepEqual(h.state(), { active: null, pending: "menu" });
  h.queue("battle"); await flush(); await h.retry();
  assert.deepEqual(h.state(), { active: null, pending: "battle" }); assert.equal(h.elements.length, 0);
  assert.equal(h.managerCalls(), 4);
});


test("return to active menu supersedes battle still waiting for initialization", async () => {
  const h = await harness(); await h.playing("menu"); h.blockInit();
  h.queue("battle"); await flush(); h.queue("menu"); h.init(); await flush();
  assert.equal(h.elements.length, 1);
  assert.deepEqual(h.audible(), ["menu"]);
  assert.deepEqual(h.state(), { active: "menu", pending: null });
});
