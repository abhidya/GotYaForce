#!/usr/bin/env node
/** Executable lifecycle/routing check for the app-owned menu-screen host. */
import assert from "node:assert/strict";
import { readFileSync, readdirSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import ts from "typescript";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const corePath = path.join(repoRoot, "packages/core/src/index.ts");
const hostPath = path.join(repoRoot, "apps/game/src/ui/menuScreenHost.ts");
const screensDir = path.join(repoRoot, "apps/game/src/ui/screens");
const mainPath = path.join(repoRoot, "apps/game/src/main.ts");

// Execute the real TypeScript implementations without relying on a previous build.
// The host's two imports are replaced only to join the core implementation in the same
// in-memory module and inject a browser-free default input placeholder. Tests pass their
// own input source, which is the intended seam exposed by createMenuScreenHost.
const coreSource = readFileSync(corePath, "utf8");
const hostSource = readFileSync(hostPath, "utf8")
  .replace(/^import \{ createScreenHost \} from "@gf\/core";\s*$/m, "")
  .replace(
    /^import \{ subscribeMenuInput, type MenuInputHandler, type MenuInputTarget \} from "\.\/menuInput\.js";\s*$/m,
    "const subscribeMenuInput = () => { throw new Error('browser input was not injected'); };",
  );
const compiled = ts.transpileModule(`${coreSource}\n${hostSource}`, {
  compilerOptions: { module: ts.ModuleKind.ES2022, target: ts.ScriptTarget.ES2022 },
  reportDiagnostics: true,
});
assert.deepEqual(compiled.diagnostics ?? [], [], "host sources must transpile without diagnostics");
const moduleUrl = `data:text/javascript;base64,${Buffer.from(compiled.outputText).toString("base64")}`;
const { createMenuScreenHost } = await import(moduleUrl);

let subscribed = 0;
let unsubscribed = 0;
let deliver = () => {};
const input = {
  subscribe(handler) {
    subscribed += 1;
    deliver = handler;
    let active = true;
    return () => {
      if (!active) return;
      active = false;
      unsubscribed += 1;
    };
  },
};

let replacements = 0;
const root = {
  replaceChildren() {
    replacements += 1;
  },
};
const events = [];
const destroys = new Map();
function handle(name) {
  destroys.set(name, 0);
  return {
    handleMenuInput(event) {
      events.push(`${name}:${event.action}:${event.dir ?? 0}`);
    },
    destroy() {
      destroys.set(name, destroys.get(name) + 1);
    },
  };
}

const host = createMenuScreenHost(root, input);
assert.equal(subscribed, 1, "host subscribes to the input bus exactly once");
deliver({ action: "confirm", source: "keyboard" }); // no target: safe ignore
assert.deepEqual(events, []);

const first = host.mount(() => handle("first"));
deliver({ action: "switch", source: "gamepad", dir: -1 });
assert.deepEqual(events, ["first:switch:-1"], "bus event and direction reach current screen");
const second = host.mount(() => handle("second"));
assert.equal(destroys.get("first"), 1, "replacement releases prior screen once");
assert.equal(host.current, second);
deliver({ action: "confirm", source: "keyboard" });
assert.equal(events.at(-1), "second:confirm:0", "replacement becomes current route");

host.clear();
host.clear();
assert.equal(destroys.get("second"), 1, "repeated clear releases current screen once");
deliver({ action: "back", source: "keyboard" });
assert.equal(events.at(-1), "second:confirm:0", "clear leaves no input target");

const under = host.mount(() => handle("under"));
const replacementsBeforeOverlay = replacements;
const lower = host.mountOverlay(() => handle("lower"));
const top = host.mountOverlay(() => handle("top"));
assert.equal(replacements, replacementsBeforeOverlay, "overlay preserves underlying root content");
deliver({ action: "down", source: "keyboard" });
assert.equal(events.at(-1), "top:down:0", "top overlay has input priority");
host.closeOverlay(lower);
deliver({ action: "up", source: "keyboard" });
assert.equal(events.at(-1), "top:up:0", "closing a lower overlay keeps top priority");
host.closeOverlay(top);
host.closeOverlay(top);
deliver({ action: "confirm", source: "keyboard" });
assert.equal(events.at(-1), "under:confirm:0", "closing overlays falls through to current screen");
assert.equal(destroys.get("lower"), 1);
assert.equal(destroys.get("top"), 1, "overlay close is exact-once");

const overlayOnReplace = host.mountOverlay(() => handle("overlay-on-replace"));
const replacement = host.mount(() => handle("replacement"));
assert.equal(destroys.get("overlay-on-replace"), 1, "standard replacement releases active overlay once");
assert.equal(destroys.get("under"), 1, "standard replacement releases underlying screen once");
host.closeOverlay(overlayOnReplace);
assert.equal(destroys.get("overlay-on-replace"), 1, "closed replacement overlay stays exact-once");

const overlayOnClear = host.mountOverlay(() => handle("overlay-on-clear"));
host.clear();
host.clear();
assert.equal(destroys.get("overlay-on-clear"), 1, "clear releases active overlay once");
assert.equal(destroys.get("replacement"), 1, "clear releases replacement screen once");
host.closeOverlay(overlayOnClear);
assert.equal(destroys.get("overlay-on-clear"), 1, "cleared overlay stays exact-once");

const finalScreen = host.mount(() => handle("final"));
host.destroy();
host.destroy();
assert.equal(destroys.get("final"), 1, "host destroy releases current screen once");
assert.equal(unsubscribed, 1, "host destroy unsubscribes exactly once");
deliver({ action: "confirm", source: "keyboard" });
assert.equal(events.at(-1), "under:confirm:0", "destroyed host ignores later delivery");
assert.throws(() => host.mount(() => first), /destroyed menu-screen host/);

// Keep static checks only for the exceptional raw listener and simple wiring facts.
const screenFiles = readdirSync(screensDir).filter((file) => file.endsWith(".ts"));
assert.equal(screenFiles.length, 11, "expected screen inventory changed");
for (const file of screenFiles) {
  const source = readFileSync(path.join(screensDir, file), "utf8");
  assert.doesNotMatch(source, /subscribeMenuInput/, `${file} must not own bus subscription lifetime`);
  assert.match(source, /handleMenuInput/, `${file} must expose menu-action behavior`);
  const hasRawKeydown = /window\.addEventListener\(\s*["']keydown["']/.test(source);
  assert.equal(hasRawKeydown, file === "TitleIntro.ts", `${file} has unexpected raw keydown wiring`);
}
const mainSource = readFileSync(mainPath, "utf8");
assert.match(mainSource, /createMenuScreenHost\(ui\)/);
assert.match(mainSource, /screenHost\.mountOverlay/);
assert.doesNotMatch(mainSource, /createScreenHost\(ui\)/);
assert.doesNotMatch(mainSource, /pauseHandle\?\.destroy/);
const resultsWiring = mainSource.slice(mainSource.indexOf("function showResults"), mainSource.indexOf("function showGets"));
const getsWiring = mainSource.slice(mainSource.indexOf("function showGets"), mainSource.indexOf("function advanceRun"));
assert.match(resultsWiring, /screenHost\.set\(handle\)/, "Results handle must be adopted by the host");
assert.match(getsWiring, /screenHost\.set\(handle\)/, "Gets handle must be adopted by the host");

console.log(
  `selfcheck-menu-flow PASS: ${screenFiles.length} targets; delivery/current/top routing, replacement, clear, overlay fall-through, exact-once teardown`,
);
