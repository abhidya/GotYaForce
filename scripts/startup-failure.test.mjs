import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const graph = emitInlineModuleGraph({
  label: "startup-failure",
  entry: path.join(root, "apps/game/src/startupFailure.ts"),
  outDir: path.join(root, ".tmp/startup-failure"),
});
const { showStartupFailure } = await import(graph.url);
class Element {
  children = []; style = {}; attrs = {}; listeners = {}; textContent = "";
  append(...children) { this.children.push(...children); }
  appendChild(child) { this.append(child); }
  replaceChildren() { this.children = []; }
  setAttribute(name, value) { this.attrs[name] = value; }
  addEventListener(name, fn) { this.listeners[name] = fn; }
}

for (const [detail, expected] of [
  ["Error creating WebGL context.", /WebGL 2.*hardware acceleration/],
  ["Failed to fetch dynamically imported module", /Check your connection/],
  ["<script>not executable</script>", /Check your connection/],
]) {
  test(`startup failure is visible and retryable: ${detail}`, t => {
    const host = new Element();
    host.append(new Element());
    let reloads = 0;
    globalThis.document = { documentElement: { dataset: {} }, getElementById: () => host, createElement: () => new Element() };
    globalThis.window = { location: { reload: () => reloads++ } };
    const error = console.error;
    console.error = () => {};
    t.after(() => { console.error = error; });
    showStartupFailure(new Error(detail));
    assert.equal(document.documentElement.dataset.gfRuntime, "boot-failed");
    assert.equal(host.children.length, 1);
    const panel = host.children[0];
    assert.equal(panel.attrs.role, "alert");
    assert.match(panel.children[0].textContent, expected);
    assert.equal(panel.children[1].textContent, detail, "error text is not interpreted as HTML");
    panel.children[2].listeners.click();
    assert.equal(reloads, 1);
  });
}

test("HTML shows loading before the guarded game module evaluates", () => {
  const html = fs.readFileSync(path.join(root, "apps/game/index.html"), "utf8");
  const bootstrap = fs.readFileSync(path.join(root, "apps/game/src/bootstrap.ts"), "utf8");
  assert.match(html, /Loading Gotcha Force/);
  assert.match(html, /src="\/src\/bootstrap.ts"/);
  assert.doesNotMatch(html, /src="\/src\/main.ts"/);
  assert.match(bootstrap, /import\("\.\/main"\)\.catch\(showStartupFailure\)/);
});

test("title startup does not load a battle stage before it is selected", () => {
  const main = fs.readFileSync(path.join(root, "apps/game/src/main.ts"), "utf8");
  const session = fs.readFileSync(path.join(root, "apps/game/src/gameSession.ts"), "utf8");
  const boot = main.match(/async function loadInitialAssets\(\): Promise<void> \{([\s\S]*?)\n\}/)?.[1];
  assert.ok(boot);
  assert.match(boot, /loadModelManifest\(\)/);
  assert.doesNotMatch(boot, /loadStage\(/);
  assert.match(main, /loadStageAssets: loadStage/);
  assert.match(session, /await dependencies\.loadStageAssets\(stageId\)/);
});
