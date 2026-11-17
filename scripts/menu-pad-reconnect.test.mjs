import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
let poll;
let pads = [];
let touch = null;
Object.defineProperty(globalThis, "navigator", { configurable: true, value: { getGamepads: () => pads } });
globalThis.window = { addEventListener() {} };
globalThis.setInterval = fn => { poll = fn; return 1; };
globalThis.testTouchPad = () => touch;
const { subscribeMenuInput } = await import(emitInlineModuleGraph({
  label: "menu-pad-reconnect", entry: path.join(root, "apps/game/src/ui/menuInput.ts"),
  outDir: path.join(root, ".tmp/menu-pad-reconnect"),
  stubs: { "./touch/index.js": "export const touchGamepad = () => globalThis.testTouchPad();" },
}).url);
const pad = (index = 0) => ({ index, connected: true, buttons: [{ pressed: true }], axes: [0, 0] });
for (const disconnected of [[], [null], [{ connected: false }]]) {
  test(`reconnect after ${JSON.stringify(disconnected)} permits a fresh confirm`, t => {
    const actions = [];
    t.after(subscribeMenuInput(e => actions.push(e.action)));
    pads = [null, null]; touch = null; poll();
    pads = [pad()]; poll(); poll();
    assert.deepEqual(actions, ["confirm"], "held button fires once");
    pads = disconnected; poll();
    pads = [pad()]; poll(); poll();
    assert.deepEqual(actions, ["confirm", "confirm"], "reconnected controller gets a fresh edge");
  });
}
test("shrinking physical slots resets removed pad without retriggering touch", t => {
  const actions = [];
  t.after(subscribeMenuInput(e => actions.push(e.action)));
  pads = [null, null]; touch = null; poll();
  touch = pad(-1); pads = [null, pad(1)]; poll();
  assert.equal(actions.length, 2);
  pads = []; poll();
  assert.equal(actions.length, 2, "held touch state survives physical disconnection");
  pads = [null, pad(1)]; poll(); poll();
  assert.equal(actions.length, 3, "only reconnected physical pad fires");
});
