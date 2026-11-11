import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Run the real overlay's hit testing, ownership, lifecycle and pad publication,
// then the real combat adapter. DOM layout and image loading are the only seams.
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const { createGcTouchOverlay } = await import(emitInlineModuleGraph({
  label: "touch-input-focus", entry: path.join(root, "apps/game/src/ui/touch/gcTouchOverlay.ts"),
  outDir: path.join(root, ".tmp/touch-input-focus/overlay"),
  stubs: { "../../publicUrl.js": "export const publicUrl = path => path;" },
}).url);
const { inputFromKeys } = await import(emitInlineModuleGraph({
  label: "touch-input-adapter", entry: path.join(root, "apps/game/src/sim/adapter.ts"),
  outDir: path.join(root, ".tmp/touch-input-focus/adapter"),
  stubs: { "@gf/missions": "export {};", "@gf/combat": "export {};" },
}).url);
class Element {
  style = {}; dataset = {}; children = []; clientWidth = 1000; clientHeight = 600;
  append(...nodes) { this.children.push(...nodes); }
  appendChild(node) { this.append(node); return node; }
  setAttribute() {} remove() {}
  getBoundingClientRect() { return {left: 0, top: 0, width: 1000, height: 600}; }
}
function setup(t) {
  const window = Object.assign(new EventTarget(), {innerWidth: 1000, innerHeight: 600});
  const document = Object.assign(new EventTarget(), {hidden: false, body: new Element(), createElement: () => new Element()});
  Object.assign(globalThis, {window, document});
  const overlay = createGcTouchOverlay(); overlay.setVisible(true);
  t.after(() => overlay.destroy());
  const controls = document.body.children[0].children;
  const point = (art, x = 0.5, y = 0.5) => {
    const el = controls.find(el => el.children[0].src.endsWith(`/${art}.png`));
    assert.ok(el, `${art} must exist`);
    return {clientX: parseFloat(el.style.left) + parseFloat(el.style.width) * x,
      clientY: parseFloat(el.style.top) + parseFloat(el.style.height) * y};
  };
  const event = (type, props = {}) => {
    const ev = new Event(type, {cancelable: true}); Object.assign(ev, props); window.dispatchEvent(ev);
  };
  return {overlay, event, point, document,
    press(art, id, x, y) { event("pointerdown", {pointerId: id, ...point(art, x, y)}); },
    input: () => inputFromKeys(new Set(), overlay.getGamepad()),
    hidden(value) { document.hidden = value; document.dispatchEvent(new Event("visibilitychange")); },
  };
}
const neutral = inputFromKeys(new Set());
for (const lifecycle of ["blur", "hidden", "hide"]) {
  test(`${lifecycle} releases all held touch controls and permits fresh ownership`, t => {
    const h = setup(t);
    h.press("gcpad_b", 1);
    h.press("gcpad_a", 2);
    h.press("gcpad_start", 3);
    h.press("gcwii_dpad", 4, 0.5, 0.1);
    h.press("gcwii_joystick_range", 5);
    h.event("pointermove", {pointerId: 5, ...h.point("gcwii_joystick_range", 1, 0.5)});
    assert.equal(h.input().attack, true); assert.equal(h.input().jump, true);
    assert.notEqual(h.input().moveX, 0);
    assert.equal(h.overlay.getGamepad().buttons[9].pressed, true);
    assert.equal(h.overlay.getGamepad().buttons[12].pressed, true);
    if (lifecycle === "blur") h.event("blur");
    else if (lifecycle === "hidden") h.hidden(true);
    else h.overlay.setVisible(false);
    assert.deepEqual(h.input(), neutral, "lost focus must release combat input without pointerup");
    h.overlay.setVisible(true); h.hidden(false); h.event("focus");
    const pad = h.overlay.getGamepad();
    assert.ok(pad.buttons.every(b => !b.pressed)); assert.ok(pad.axes.every(a => a === 0));
    // Old pointer releases are harmless; fresh pointers can own every control again.
    h.event("pointerup", {pointerId: 1});
    h.press("gcpad_b", 11); assert.equal(h.input().attack, true);
    h.event("pointerup", {pointerId: 11}); assert.deepEqual(h.input(), neutral);
    h.press("gcwii_joystick_range", 15);
    h.event("pointermove", {pointerId: 15, ...h.point("gcwii_joystick_range", 0, 0.5)});
    assert.notEqual(h.input().moveX, 0);
    h.event("pointercancel", {pointerId: 15}); assert.deepEqual(h.input(), neutral);
  });
}
test("visible notification preserves controls; cancel releases only its own pointer", t => {
  const h = setup(t); h.press("gcpad_b", 1); h.press("gcpad_a", 2);
  h.hidden(false); assert.equal(h.input().attack, true); assert.equal(h.input().jump, true);
  h.event("pointercancel", {pointerId: 1});
  assert.equal(h.input().attack, false); assert.equal(h.input().jump, true);
  h.event("pointerup", {pointerId: 99}); assert.equal(h.input().jump, true);
  h.event("pointerup", {pointerId: 2}); assert.deepEqual(h.input(), neutral);
});
test("destroy removes listeners and leaves the old controller neutral", t => {
  const h = setup(t); h.press("gcpad_b", 1); h.overlay.destroy();
  h.press("gcpad_b", 2); h.event("blur"); h.hidden(true);
  assert.deepEqual(h.input(), neutral);
});
