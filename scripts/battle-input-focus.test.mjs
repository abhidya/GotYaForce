import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import vm from "node:vm";
import { fileURLToPath } from "node:url";
import ts from "typescript";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const mainPath = path.join(root, "apps/game/src/main.ts");
const source = fs.readFileSync(mainPath, "utf8");
const ast = ts.createSourceFile(mainPath, source, ts.ScriptTarget.Latest, true);
// Execute the app's actual registrations rather than duplicating the handlers in the test.
// Keep unrelated rendering/audio boot out of Node, with browser events as the test seam.
const start = source.indexOf("const keys = new Set<string>();");
const end = source.indexOf("function isTextInputTarget", start);
assert.ok(start >= 0 && end > start, "main keyboard registration block must be found");
const textTarget = ast.statements.find((node) => ts.isFunctionDeclaration(node) && node.name?.text === "isTextInputTarget");
assert.ok(textTarget, "actual text-input guard must be found");
const keyboardSource = source.slice(start, end) + textTarget.getText(ast) + "\nglobalThis.heldKeys = keys;";
const compiled = ts.transpileModule(keyboardSource, {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.ES2022 },
  reportDiagnostics: true,
});
assert.deepEqual(compiled.diagnostics, []);
const adapterGraph = emitInlineModuleGraph({
  // These imports supply types only; input conversion and its runtime dependencies are real.
  stubs: { "@gf/missions": "export {};", "@gf/combat": "export {};" },
  label: "battle-input-focus", entry: path.join(root, "apps/game/src/sim/adapter.ts"),
  outDir: path.join(root, ".tmp/battle-input-focus-test/adapter"),
});
const { inputFromKeys } = await import(adapterGraph.url);
const edgeGraph = emitInlineModuleGraph({
  label: "battle-input-focus-edge", entry: path.join(root, "apps/game/src/inputEdge.ts"),
  outDir: path.join(root, ".tmp/battle-input-focus-test/edge"),
});
const { createInputEdgeLatch } = await import(edgeGraph.url);

function setup() {
  const window = new EventTarget();
  const document = Object.assign(new EventTarget(), { hidden: false });
  class Input {}
  const context = vm.createContext({
    window, document, HTMLInputElement: Input, HTMLSelectElement: class {}, HTMLTextAreaElement: class {},
    playPendingBgm() {}, challengeSession: { snapshot: () => ({ screen: "battle" }) },
    debugOverlay: { visible: false, setVisible() {} },
  });
  vm.runInContext(compiled.outputText, context, { filename: mainPath });
  return {
    keys: context.heldKeys,
    input: () => inputFromKeys(context.heldKeys),
    key(type, code, target) {
      const event = new Event(type, { cancelable: true });
      Object.defineProperty(event, "code", { value: code });
      if (target) Object.defineProperty(event, "target", { value: target });
      window.dispatchEvent(event);
      return event;
    },
    blur: () => window.dispatchEvent(new Event("blur")),
    focus: () => window.dispatchEvent(new Event("focus")),
    visibility(hidden) {
      document.hidden = hidden;
      document.dispatchEvent(new Event("visibilitychange"));
    },
    textInput: new Input(),
  };
}
const neutral = inputFromKeys(new Set());

for (const lifecycle of ["blur", "hidden"]) {
  test(`${lifecycle} clears movement and all held actions without receiving keyup`, () => {
    const app = setup();
    for (const code of ["KeyW", "KeyK", "Space", "KeyL", "ShiftLeft", "KeyU", "Tab", "KeyQ", "KeyZ", "KeyY", "Enter"]) {
      app.key("keydown", code);
    }
    assert.equal(app.input().moveZ, 1);
    assert.equal(app.input().attack, true);
    if (lifecycle === "blur") app.blur(); else app.visibility(true);
    assert.equal(app.keys.size, 0, "all keys, including shell pause keys, must be released");
    assert.deepEqual(app.input(), neutral);
    // The physical keys are released outside the page: no keyup arrives here.
    app.visibility(false);
    app.focus();
    assert.deepEqual(app.input(), neutral, "returning must not revive old input");
    app.blur();
    app.visibility(true);
    assert.deepEqual(app.input(), neutral, "repeated loss events are harmless");
    app.visibility(false);
    app.focus();
    app.key("keydown", "KeyW");
    app.key("keydown", "KeyK");
    assert.equal(app.input().moveZ, 1);
    assert.equal(app.input().attack, true);
    app.key("keyup", "KeyW");
    assert.equal(app.input().moveZ, 0);
    assert.equal(app.input().attack, true, "keyup releases only its own key");
    app.key("keyup", "KeyK");
    assert.deepEqual(app.input(), neutral);
  });
}

test("visible notifications and normal focused controls preserve existing behavior", () => {
  const app = setup();
  app.key("keydown", "KeyW");
  app.key("keydown", "KeyK");
  app.visibility(false);
  app.focus();
  assert.equal(app.input().moveZ, 1);
  assert.equal(app.input().attack, true);
  assert.equal(app.key("keydown", "Tab").defaultPrevented, true);
  app.key("keyup", "Tab");
  app.key("keydown", "Space", app.textInput);
  assert.equal(app.input().jump, false, "text fields must still ignore game input");
});

test("focus loss releases a consumed pause key without synthesizing a pause press", () => {
  const app = setup();
  const edge = createInputEdgeLatch();
  const poll = () => edge.poll(app.keys.has("Enter") || app.keys.has("Escape"));
  app.key("keydown", "Enter");
  edge.consume(true); // Briefing confirmation is consumed by battle entry.
  assert.equal(poll(), false);
  app.blur();
  assert.equal(poll(), false);
  app.focus();
  assert.equal(poll(), false);
  app.key("keydown", "Enter");
  assert.equal(poll(), true);
  assert.equal(poll(), false);
  app.key("keyup", "Enter");
  assert.equal(poll(), false);
  app.key("keydown", "Escape");
  assert.equal(poll(), true);
});
