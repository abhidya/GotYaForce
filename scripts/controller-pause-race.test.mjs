import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import vm from "node:vm";
import ts from "typescript";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Execute production input, routing, pause screen and main's pause functions. Only
// DOM/drawing and raw device snapshots are fake; this is not a WebGL/browser smoke test.
class Element {
  children = []; style = {}; className = ""; classList = { toggle() {} };
  append(...nodes) { for (const n of nodes) { n.parent = this; this.children.push(n); } }
  appendChild(n) { this.append(n); return n; }
  get firstChild() { return this.children[0]; }
  removeChild(n) { this.children.splice(this.children.indexOf(n), 1); }
  remove() { this.parent?.removeChild(this); }
  replaceChildren() { this.children = []; }
  setAttribute() {} addEventListener() {}
  querySelector() { return null; }
}
globalThis.document = { createElement: () => new Element() };
globalThis.HTMLInputElement = class {};
globalThis.HTMLSelectElement = class {};
globalThis.HTMLTextAreaElement = class {};
const listeners = new Map();
globalThis.window = { addEventListener: (type, f) => listeners.set(type, f) };
let menuTick;
globalThis.setInterval = f => { menuTick = f; return 1; };
let physical = [], touch = null;
Object.defineProperty(globalThis, "navigator", { configurable: true, value: { getGamepads: () => physical } });
globalThis.pauseRaceTouch = () => touch;
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const app = path.join(root, "apps/game/src");
function graph(name, entry, stubs = {}, packages = {}) {
  return emitInlineModuleGraph({ label: name, entry: path.join(app, entry),
    outDir: path.join(root, ".tmp", name), stubs, packages });
}
const bus = await import(graph("pause-race-bus", "ui/menuInput.ts", {
  "./touch/index.js": "export const touchGamepad = () => globalThis.pauseRaceTouch();",
}).url);
globalThis.pauseRaceBus = bus;
const { createMenuScreenHost } = await import(graph("pause-race-host", "ui/menuScreenHost.ts", {
  "./menuInput.js": "export const subscribeMenuInput = globalThis.pauseRaceBus.subscribeMenuInput;",
}, { "@gf/core": path.join(root, "packages/core/src/index.ts") }).url);
const { createPauseMenu } = await import(graph("pause-race-screen", "ui/screens/PauseMenu.ts", {
  "../bitmapText.js": "export const bitmapText = () => document.createElement('span'); export const setBitmapText = () => {};",
  "../assets.js": "export const ASSETS = {menuRoundelPlate: ''};",
}).url);
const { createInputEdgeLatch } = await import(graph("pause-race-latch", "inputEdge.ts").url);

// Extract exact AST nodes, not a copied implementation. Fail loudly if main changes
// its names or shape. This avoids booting its unrelated renderer/asset pipeline.
const mainText = fs.readFileSync(path.join(app, "main.ts"), "utf8");
const main = ts.createSourceFile("main.ts", mainText, ts.ScriptTarget.Latest, true);
const functions = ["activeGamepad", "pauseControlPressed", "pollPauseToggle", "pauseBattle", "resumeBattle", "closePauseMenu"];
const constants = ["pauseInputEdge", "PAD_START_BUTTON"];
const nodes = [...functions.map(name => {
  const node = main.statements.find(n => ts.isFunctionDeclaration(n) && n.name?.text === name);
  assert.ok(node, `main must define ${name}`); return node;
}), ...constants.map(name => {
  const node = main.statements.find(n => ts.isVariableStatement(n) && n.declarationList.declarations.some(d => d.name.getText(main) === name));
  assert.ok(node, `main must define ${name}`); return node;
})];
const pauseCode = ts.transpileModule(nodes.map(n => n.getText(main)).join("\n"), {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.ES2022 },
}).outputText;
function pad(index) {
  return { index, connected: true, buttons: Array.from({length: 16}, () => ({pressed: false})), axes: [0, 0] };
}
function setup(t, source, oldBehavior = false) {
  physical = []; touch = null;
  // Drop stale bus state from the previous scenario, including physical slots.
  const reset = bus.subscribeMenuInput(() => {});
  physical = [null, null, null]; menuTick(); physical = []; reset();
  const device = pad(source === "touch" ? -1 : source === "fallback" ? 2 : 0);
  if (source === "touch") touch = device;
  else physical = Array.from({length: device.index + 1}, (_, i) => i === device.index ? device : null);
  const host = createMenuScreenHost(new Element());
  t.after(() => host.destroy());
  const normalActions = [];
  host.set({ handleMenuInput: e => normalActions.push(e.action), destroy() {} });
  let opens = 0, resumes = 0;
  const context = vm.createContext({ navigator, touchGamepad: () => touch,
    keys: new Set(), session: {paused: false, resolved: false, pauseHandle: null},
    createInputEdgeLatch, consumeMenuGamepadStart: oldBehavior ? () => {} : bus.consumeMenuGamepadStart,
    screenHost: host, createPauseMenu: (...args) => { opens++; return createPauseMenu(...args); },
    playConfirmSfx: () => { resumes++; }, playBackSfx() {}, endBattleToMenu() {},
  });
  vm.runInContext(pauseCode, context);
  return { device, host, context, normalActions, counts: () => ({opens, resumes}),
    tick(order) { for (const which of order) which === "sim" ? context.pollPauseToggle() : menuTick(); },
    press(value) { device.buttons[9].pressed = value; },
  };
}
function opening(h, order) {
  h.press(true); h.tick(order);
  assert.equal(h.context.session.paused, true, "opening Start must leave battle paused");
  assert.deepEqual(h.counts(), {opens: 1, resumes: 0});
}
for (const source of ["physical", "fallback", "touch"]) {
  for (const order of [["sim", "menu"], ["menu", "sim"]]) {
    test(`${source}, ${order.join(" first: ")}: one Start press per transition`, t => {
      const h = setup(t, source); opening(h, order);
      for (let i = 0; i < 4; i++) h.tick(order);
      assert.equal(h.context.session.paused, true, "held Start must not resume");
      h.press(false); h.tick(order); h.press(true); h.tick(order);
      assert.equal(h.context.session.paused, false, "fresh Start resumes");
      for (let i = 0; i < 4; i++) h.tick(order);
      assert.deepEqual(h.counts(), {opens: 1, resumes: 1}, "resume cannot immediately repause");
      h.press(false); h.tick(order); h.press(true); h.tick(order);
      assert.equal(h.context.session.paused, true, "next fresh Start pauses");
      assert.deepEqual(h.counts(), {opens: 2, resumes: 1});
    });
  }
}
test("negative control: the old unclaimed opening edge fails the same assertion", t => {
  const h = setup(t, "physical", true);
  assert.throws(() => opening(h, ["sim", "menu"]), /opening Start must leave battle paused/);
  assert.deepEqual(h.counts(), {opens: 1, resumes: 1});
});
test("only the opening pad's Start is consumed; another controller can resume", t => {
  const h = setup(t, "touch"); opening(h, ["sim", "menu"]);
  const other = pad(0); physical = [other]; other.buttons[9].pressed = true;
  menuTick();
  assert.equal(h.context.session.paused, false);
  assert.deepEqual(h.counts(), {opens: 1, resumes: 1});
});
test("other buttons, sticks, normal-menu Start and keyboard remain active", t => {
  const h = setup(t, "physical");
  h.context.session = null;
  h.press(true); menuTick();
  assert.deepEqual(h.normalActions, ["start"], "Start still works outside battle");
  h.press(false); menuTick();
  h.context.session = {paused: false, resolved: false, pauseHandle: null};
  h.press(true); h.context.pollPauseToggle();
  h.device.buttons[13].pressed = true; menuTick();
  assert.equal(h.context.session.pauseHandle.getSelected(), "quit", "D-pad is not consumed");
  h.device.buttons[13].pressed = false; h.device.axes[1] = -1; menuTick();
  assert.equal(h.context.session.pauseHandle.getSelected(), "resume", "stick still navigates");
  h.device.buttons[0].pressed = true; menuTick();
  assert.equal(h.context.session.paused, false, "A still resumes");
  h.press(false); h.device.buttons[0].pressed = false; h.device.axes[1] = 0; h.tick(["sim", "menu"]);
  // Match real keyboard ordering: keydown/menu event happens before the sim tick.
  const key = (code, repeat = false) => listeners.get("keydown")({code, repeat, target: null, preventDefault() {}});
  h.context.keys.add("Escape"); key("Escape"); h.context.pollPauseToggle();
  assert.equal(h.context.session.paused, true);
  key("Escape", true); h.context.pollPauseToggle();
  assert.equal(h.context.session.paused, true);
  h.context.keys.clear(); h.context.pollPauseToggle();
  h.context.keys.add("Escape"); key("Escape"); h.context.pollPauseToggle();
  assert.equal(h.context.session.paused, false);
});
