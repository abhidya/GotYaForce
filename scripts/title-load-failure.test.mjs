import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Exercise the real screen and source VM. Only DOM/drawing are isolated; these
// tests do not claim a successful WebGL render or gameplay pass.
class Element {
  children = []; style = {}; dataset = {}; attrs = {}; listeners = new Map();
  className = ""; hidden = false; textContent = "";
  append(...nodes) { for (const node of nodes) { node.parent = this; this.children.push(node); } }
  appendChild(node) { this.append(node); return node; }
  remove() { if (this.parent) this.parent.children = this.parent.children.filter(node => node !== this); }
  setAttribute(name, value) { this.attrs[name] = value; }
  addEventListener(name, fn) { this.listeners.set(name, fn); }
  removeEventListener(name, fn) { if (this.listeners.get(name) === fn) this.listeners.delete(name); }
  querySelector(selector) {
    for (const child of this.children) {
      if (child.className.split(" ").includes(selector.slice(1))) return child;
      const found = child.querySelector(selector);
      if (found) return found;
    }
    return null;
  }
}
const listeners = new Map();
const frames = new Map();
let frameId = 0;
globalThis.document = { documentElement: { dataset: {} }, createElement: () => new Element() };
globalThis.window = {
  addEventListener: (name, fn) => listeners.set(name, fn),
  removeEventListener: (name, fn) => { if (listeners.get(name) === fn) listeners.delete(name); },
};
globalThis.requestAnimationFrame = fn => { frames.set(++frameId, fn); return frameId; };
globalThis.cancelAnimationFrame = id => frames.delete(id);

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const graph = emitInlineModuleGraph({
  label: "title-load-failure",
  entry: path.join(root, "apps/game/src/ui/screens/TitleIntro.ts"),
  outDir: path.join(root, ".tmp/title-load-failure"),
  stubs: {
    "three": `export class WebGLRenderer {
      constructor() { if (globalThis.titleFailureMode !== "asset") throw new Error("WebGL context unavailable"); }
      setClearColor() {} dispose() { globalThis.titleDisposals++; } forceContextLoss() { globalThis.titleContextLosses++; }
    }
    export class Scene { add() {} } export class Group {} export class PerspectiveCamera {} export class Vector3 {}`,
    "@gf/render": `export const createSourceCamera = () => ({}); export const applySourceCameraToThree = () => {}; export const createThreeAssetLoader = () => ({}); export const prepareImportedModel = () => {};`,
    "../intro/tdcSceneEnvironment.js": `export const applyTdcFog = () => {}; export const applyTdcLights = () => {};`,
    "../sceneModel.js": `export function createUiSceneHost(className) { const host = document.createElement("div"); host.className = className; const canvas = document.createElement("canvas"); canvas.className = "gf-ui-scene-canvas"; host.appendChild(canvas); return host; }`,
    "../bitmapText.js": `export function bitmapText(className) { const node = document.createElement("span"); node.className = className; return node; } export function setBitmapText(node, text) { node.textContent = text; }`,
    "../../publicUrl.js": `export const publicUrl = path => path;`,
  },
});
const { createTitleIntro } = await import(graph.url);

for (const input of ["keyboard", "click", "gamepad"]) {
  test(`failed title scene remains visibly dismissible with ${input}`, t => {
    const container = new Element();
    let entered = 0;
    const warn = console.warn;
    console.warn = () => {};
    t.after(() => { console.warn = warn; });
    const screen = createTitleIntro(container, { onEnter: () => entered++, onSound() {} });
    t.after(() => screen.destroy());
    const title = container.children[0];
    assert.equal(title.querySelector(".gf-title-intro-scene").dataset.gfModelStatus, "failed");
    assert.equal(title.querySelector(".gf-title-intro-prompt").hidden, false);
    assert.equal(title.querySelector(".gf-title-intro-prompt").style.opacity, "1");
    assert.match(title.querySelector(".gf-title-intro-error").textContent, /unavailable.*continue/i);
    if (input === "keyboard") listeners.get("keydown")({ preventDefault() {}, stopImmediatePropagation() {} });
    if (input === "click") title.listeners.get("click")();
    if (input === "gamepad") screen.handleMenuInput({ source: "gamepad", action: "confirm" });
    assert.equal(entered, 1, "failed decoration must not trap the player at the archive-wait opcode");
    assert.notEqual(title.dataset.gfIntroDone, "true", "recovery is not claimed as completed source playback");
    screen.destroy();
    screen.handleMenuInput({ source: "gamepad", action: "confirm" });
    assert.equal(entered, 1, "destroyed screen cannot navigate");
    assert.equal(frames.size, 0, "failed scene must not keep a stalled fallback animation loop alive");
  });
}


test("title leaves browser shortcuts and modifier keys alone while ordinary keys continue", t => {
  const warn=console.warn; console.warn=()=>{}; t.after(()=>{console.warn=warn;});
  const screen=createTitleIntro(new Element(),{onEnter:()=>entered++,onSound(){}}); let entered=0;
  const handler=listeners.get('keydown'); assert.ok(handler);
  for(const event of [
    {key:'Control',ctrlKey:true}, {key:'Shift'}, {key:'r',ctrlKey:true},
    {key:'r',metaKey:true}, {key:'ArrowLeft',altKey:true}, {key:'Process',isComposing:true},
    {key:'F5'}, {key:'F11'}, {key:'F12'}, {key:'Tab'},
  ]) {
    let prevented=false,stopped=false;
    handler({...event,preventDefault(){prevented=true;},stopImmediatePropagation(){stopped=true;}});
    assert.equal(entered,0); assert.equal(prevented,false); assert.equal(stopped,false);
  }
  let prevented=false,stopped=false;
  handler({key:'Enter',preventDefault(){prevented=true;},stopImmediatePropagation(){stopped=true;}});
  assert.equal(entered,1); assert.equal(prevented,true); assert.equal(stopped,true);
  screen.destroy();
});

test("failed camera asset releases its renderer and permits continuation", async t => {
  globalThis.titleFailureMode = "asset";
  globalThis.titleDisposals = 0;
  globalThis.titleContextLosses = 0;
  globalThis.fetch = async () => ({ ok: false, status: 404 });
  const warn = console.warn;
  console.warn = () => {};
  t.after(() => { console.warn = warn; delete globalThis.titleFailureMode; });
  const container = new Element();
  let entered = 0;
  const screen = createTitleIntro(container, { onEnter: () => entered++, onSound() {} });
  await Promise.resolve();
  const title = container.children[0];
  assert.equal(title.querySelector(".gf-title-intro-scene").dataset.gfModelStatus, "failed");
  assert.equal(globalThis.titleDisposals, 1);
  assert.equal(globalThis.titleContextLosses, 1);
  screen.handleMenuInput({ source: "gamepad", action: "confirm" });
  assert.equal(entered, 1);
  screen.destroy();
  assert.equal(globalThis.titleDisposals, 1, "destroy does not release a failed renderer twice");
});

test("failure arriving after destroy does not revive the title UI or animation loop", async t => {
  globalThis.titleFailureMode = "asset";
  globalThis.titleDisposals = 0;
  globalThis.titleContextLosses = 0;
  let finish;
  globalThis.fetch = () => new Promise(resolve => { finish = resolve; });
  const warn = console.warn;
  console.warn = () => {};
  t.after(() => { console.warn = warn; delete globalThis.titleFailureMode; });
  const container = new Element();
  let entered = 0;
  const screen = createTitleIntro(container, { onEnter: () => entered++, onSound() {} });
  const title = container.children[0];
  screen.destroy();
  finish({ ok: false, status: 404 });
  await Promise.resolve();
  assert.equal(container.children.length, 0);
  assert.equal(title.querySelector(".gf-title-intro-error"), null);
  assert.equal(globalThis.titleDisposals, 1);
  assert.equal(globalThis.titleContextLosses, 1);
  assert.equal(frames.size, 0);
  screen.handleMenuInput({ source: "gamepad", action: "confirm" });
  assert.equal(entered, 0);
});


test("successful camera load after destroy cannot resume the scene loader", async t => {
  globalThis.titleFailureMode = "asset";
  globalThis.titleDisposals = 0;
  globalThis.titleContextLosses = 0;
  let finish;
  let requests = 0;
  globalThis.fetch = () => { requests++; return new Promise(resolve => { finish = resolve; }); };
  const warn = console.warn;
  let warnings = 0;
  console.warn = () => { warnings++; };
  t.after(() => { console.warn = warn; delete globalThis.titleFailureMode; });
  const container = new Element();
  const screen = createTitleIntro(container, { onEnter() {}, onSound() {} });
  screen.destroy();
  finish({ ok: true, json: async () => [] });
  await Promise.resolve();
  await Promise.resolve();
  assert.equal(requests, 1, "cancelled scene cannot begin model requests");
  assert.equal(warnings, 0, "cancelled success is not handled as a new loader failure");
  assert.equal(container.children.length, 0);
  assert.equal(globalThis.titleDisposals, 1);
  assert.equal(frames.size, 0);
});
