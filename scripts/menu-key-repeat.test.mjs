import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Keep real screen state, input translation and host routing. Only browser DOM,
// drawing and the absent touch controller are isolated; no WebGL pass is implied.
class Element {
  children = []; style = {}; attrs = {}; listeners = {}; className = "";
  classList = { toggle: () => {} };
  append(...nodes) { for (const n of nodes) { n.parent = this; this.children.push(n); } }
  appendChild(n) { this.append(n); return n; }
  get firstChild() { return this.children[0]; }
  removeChild(n) { this.children.splice(this.children.indexOf(n), 1); }
  remove() { this.parent?.removeChild(this); }
  replaceChildren() { this.children = []; }
  setAttribute(k, v) { this.attrs[k] = v; }
  addEventListener(k, f) { this.listeners[k] = f; }
  querySelectorAll(selector) {
    return this.children.flatMap(n => [
      ...(n.className.split(" ").includes(selector.slice(1)) ? [n] : []),
      ...n.querySelectorAll(selector),
    ]);
  }
  querySelector(s) { return this.querySelectorAll(s)[0]; }
  scrollIntoView() {}
}
globalThis.document = { createElement: () => new Element() };
globalThis.HTMLInputElement = class {};
globalThis.HTMLSelectElement = class {};
globalThis.HTMLTextAreaElement = class {};
const listeners = new Map();
globalThis.window = { addEventListener: (type, listener) => listeners.set(type, listener) };
// The keyboard tests never poll gamepads. Avoid leaving the bus's interval alive.
globalThis.setInterval = () => 1;
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const hostGraph = emitInlineModuleGraph({
  label: "menu-key-repeat-host",
  entry: path.join(root, "apps/game/src/ui/menuScreenHost.ts"),
  outDir: path.join(root, ".tmp/menu-key-repeat-host"),
  packages: { "@gf/core": path.join(root, "packages/core/src/index.ts") },
  stubs: { "./touch/index.js": "export const touchGamepad = () => null;" },
});
const builderGraph = emitInlineModuleGraph({
  label: "menu-key-repeat-builder",
  entry: path.join(root, "apps/game/src/ui/screens/ForceBuilder.ts"),
  outDir: path.join(root, ".tmp/menu-key-repeat-builder"),
  stubs: {
    "../bitmapText.js": "export const bitmapText = () => document.createElement('span'); export const setBitmapText = () => {};",
    "../captureCrop.js": "export const captureCropImg = () => document.createElement('img');",
    "../assets.js": "export const borgMiniPath = id => id;",
    "../sceneModel.js": "export const createUiSceneHost = () => document.createElement('div'); export const mountUiSceneModels = () => () => {};",
    "../layout.generated.js": "export const UI_SCENE_LAYOUTS = {unitall: {modelCount: 0}};",
    "./touch/index.js": "export const touchGamepad = () => null;",
  },
});
const { createMenuScreenHost } = await import(hostGraph.url);
const { createForceBuilder } = await import(builderGraph.url);
function key(code, repeat = false, target = null) {
  let prevented = false;
  listeners.get("keydown")({ code, repeat, target, preventDefault() { prevented = true; } });
  return prevented;
}
function mount(t, options = {}) {
  const host = createMenuScreenHost(new Element());
  t.after(() => host.destroy());
  const builder = host.mount(container => createForceBuilder(container, {
    catalog: ["first", "second", "third"].map(id => ({ id, name: id, energy: 100 })),
    limit: 1000, onConfirm() {}, ...options,
  }));
  return { host, builder };
}
for (const code of ["Enter", "Space", "KeyA"]) {
  test(`${code}: held confirm does not toggle the selected borg`, t => {
    const { builder } = mount(t);
    assert.equal(key(code), true);
    assert.deepEqual(builder.getForce(), ["first"]);
    assert.equal(key(code, true), true, "suppressed repeats still prevent native activation/scroll");
    assert.deepEqual(builder.getForce(), ["first"], "held confirm must not remove the borg");
    key(code);
    assert.deepEqual(builder.getForce(), [], "a new press still toggles normally");
  });
}
for (const code of ["ArrowRight", "ArrowDown", "ArrowLeft", "ArrowUp"]) {
  test(`${code}: directional repeat still navigates`, t => {
    const { builder } = mount(t);
    key(code);
    assert.equal(key(code, true), true);
    key("Enter");
    assert.deepEqual(builder.getForce(), [code === "ArrowRight" || code === "ArrowDown" ? "third" : "second"]);
  });
}
for (const code of ["KeyQ", "KeyE", "BracketLeft", "BracketRight"]) {
  test(`${code}: held switch does not toggle back to the grid`, t => {
    const { builder } = mount(t);
    key(code); // grid -> empty ring
    assert.equal(key(code, true), true);
    key("Enter");
    assert.deepEqual(builder.getForce(), [], "ring confirm cannot add a borg");
    key(code); // new press -> grid
    key("Enter");
    assert.deepEqual(builder.getForce(), ["first"]);
  });
}
for (const [code, callback, action] of [["KeyP", "onConfirm", "start"], ["Escape", "onQuit", "back"], ["KeyB", "onQuit", "back"]]) {
  test(`${code}: a held exit does not reach the next host target`, t => {
    const received = [];
    let host;
    ({ host } = mount(t, {
      initialForce: ["first"],
      [callback]: () => host.set({ handleMenuInput: e => received.push(e.action), destroy() {} }),
    }));
    key(code); // the real builder saves/quits and its callback replaces the host target
    assert.equal(key(code, true), true);
    assert.deepEqual(received, [], "repeat must not cascade into the replacement screen");
    key(code);
    assert.deepEqual(received, [action], "a fresh press reaches the replacement");
  });
}
test("edit repeat is suppressed; unmapped keys and text controls remain untouched", t => {
  const { host } = mount(t);
  const received = [];
  host.set({ handleMenuInput: e => received.push(e.action), destroy() {} });
  key("KeyX");
  assert.equal(key("KeyX", true), true);
  assert.deepEqual(received, ["edit"]);
  assert.equal(key("KeyZ"), false);
  for (const Control of [HTMLInputElement, HTMLSelectElement, HTMLTextAreaElement]) {
    for (const repeat of [false, true]) {
      assert.equal(key("Enter", repeat, new Control()), false);
      assert.equal(key("ArrowDown", repeat, new Control()), false);
    }
  }
  assert.deepEqual(received, ["edit"]);
});
