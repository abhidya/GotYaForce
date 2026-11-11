#!/usr/bin/env node
import assert from "node:assert/strict";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Minimal DOM surface. Rendering assets/WebGL are isolated, while real builder
// state, button listeners, navigation, budget checks and callback delivery run.
class Element {
  children = []; style = {}; attrs = {}; listeners = {}; className = "";
  classList = { toggle: () => {} };
  append(...nodes) { for (const n of nodes) { n.parent = this; this.children.push(n); } }
  appendChild(n) { this.append(n); return n; }
  get firstChild() { return this.children[0]; }
  removeChild(n) { this.children.splice(this.children.indexOf(n), 1); }
  remove() { this.parent?.removeChild(this); }
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
  click() { if (!this.disabled) this.listeners.click?.({}); }
}
globalThis.document = { createElement: () => new Element() };
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const graph = emitInlineModuleGraph({
  label: "force-builder",
  entry: path.join(root, "apps/game/src/ui/screens/ForceBuilder.ts"),
  outDir: path.join(root, ".tmp/force-builder"),
  stubs: {
    "../bitmapText.js": "export const bitmapText = () => document.createElement('span'); export const setBitmapText = () => {};",
    "../captureCrop.js": "export const captureCropImg = () => document.createElement('img');",
    "../assets.js": "export const borgMiniPath = id => id;",
    "../sceneModel.js": "export const createUiSceneHost = () => document.createElement('div'); export const mountUiSceneModels = () => () => {};",
    "../layout.generated.js": "export const UI_SCENE_LAYOUTS = {unitall: {modelCount: 0}};",
  },
});
const { createForceBuilder } = await import(graph.url);
function mount(options = {}) {
  const container = new Element(), saved = [];
  let quits = 0;
  const handle = createForceBuilder(container, {
    catalog: [{id:"pl0004", name:"Acceleration Ninja", energy:380},
      {id:"other", name:"Other", energy:500}],
    limit: 600, onConfirm: force => saved.push(force), onQuit: () => quits++,
    ...options,
  });
  const action = a => handle.handleMenuInput({action:a, source:"keyboard"});
  return { container, saved, handle, action, quits: () => quits };
}
const edit = mount();
edit.action("start");
assert.deepEqual(edit.saved, [], "empty force cannot save");
edit.action("confirm");
assert.deepEqual(edit.handle.getForce(), ["pl0004"]);
assert.deepEqual(edit.saved, [], "A holds a borg, does not prematurely save");
edit.action("right");
edit.action("confirm");
assert.deepEqual(edit.handle.getForce(), ["pl0004"], "over-budget add blocked");
edit.action("start");
assert.deepEqual(edit.saved, [["pl0004"]], "START commits edited selection");
edit.saved[0].push("external");
assert.deepEqual(edit.handle.getForce(), ["pl0004"], "callback receives snapshot");
edit.action("switch");
edit.action("back");
assert.equal(edit.quits(), 1, "B cancels from ring");
assert.equal(edit.saved.length, 1);
const clicked = mount({ initialForce: ["pl0004"] });
clicked.container.querySelector(".gf-force-save").click();
assert.deepEqual(clicked.saved, [["pl0004"]], "visible button commits");
// Model the actual DOM propagation boundary: target listener runs before the
// window menu bus, which converts Enter/Space into confirm unless stopped.
for (const code of ["Enter", "Space"]) {
  const focused = mount({ initialForce: ["pl0004"] });
  const button = focused.container.querySelector(".gf-force-save");
  let prevented = false, stopped = false;
  button.listeners.keydown?.({ code, repeat: false,
    preventDefault() { prevented = true; },
    stopPropagation() { stopped = true; },
  });
  if (!stopped) focused.action("confirm");
  assert.equal(prevented, true, "suppress native duplicate click");
  assert.equal(stopped, true, "focused save does not reach menu bus");
  assert.deepEqual(focused.saved, [["pl0004"]], code + " commits focused save");
  assert.deepEqual(focused.handle.getForce(), ["pl0004"], "no roster toggle");
  button.listeners.keydown({ code, repeat: true,
    preventDefault() {}, stopPropagation() {},
  });
  assert.equal(focused.saved.length, 1, "held key does not repeat commit");
  focused.handle.destroy();
}
const over = mount({initialForce:["pl0004", "other"]});
over.action("start");
assert.equal(over.container.querySelector(".gf-force-save").disabled, true);
assert.deepEqual(over.saved, [], "over-budget initial force cannot save");
over.action("confirm"); // remove lead, now within budget
over.action("switch");
over.action("start");
assert.deepEqual(over.saved, [["other"]], "ring START saves after correction");
const empty = mount({catalog:[]});
empty.action("back");
assert.equal(empty.quits(), 1, "empty catalog remains cancellable");
const capped = mount({maxSlots:1, limit:1000});
capped.action("confirm"); capped.action("right"); capped.action("confirm");
assert.deepEqual(capped.handle.getForce(), ["pl0004"], "slot cap preserved");
for (const test of [edit, clicked, over, empty, capped]) test.handle.destroy();
console.log("force-builder selfcheck PASS: commit button/START, cancellation, snapshot, budget, capacity");
