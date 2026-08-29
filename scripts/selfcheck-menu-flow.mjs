#!/usr/bin/env node
/** Executable lifecycle/routing check for the app-owned menu-screen host. */
import assert from "node:assert/strict";
import { readFileSync, readdirSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const hostPath = path.join(repoRoot, "apps/game/src/ui/menuScreenHost.ts");
const screensDir = path.join(repoRoot, "apps/game/src/ui/screens");
const mainPath = path.join(repoRoot, "apps/game/src/main.ts");

// Execute the real TypeScript implementations without relying on a previous build: the host
// is emitted as a module graph with the REAL @gf/core linked in, so it exercises the actual
// createScreenHost rather than a stand-in.
//
// This is what used to break the script. It transpiled core+host into ONE data: module and
// deleted their imports with hand-written regexes; when `packages/core/src/index.ts` gained
// `export * from "./gcRuntime.js"` the regexes knew nothing about it, the specifier survived
// into a data: URL that cannot resolve relative paths, and the run died on "Invalid relative
// URL" — a selfcheck that could not execute while still looking like coverage.
// emitInlineModuleGraph follows the real graph (gcRuntime included) and hard-errors by name
// on any dependency that is neither mapped nor stubbed.
const graph = emitInlineModuleGraph({
  label: "selfcheck-menu-flow",
  entry: hostPath,
  outDir: path.join(repoRoot, ".tmp", "selfcheck-menu-flow"),
  packages: {
    // The real implementation, not a fake: linking it is the point of this check.
    "@gf/core": path.join(repoRoot, "packages/core/src/index.ts"),
  },
  stubs: {
    // menuInput is the browser DOM seam. Tests pass their own input source, which is the
    // injection point createMenuScreenHost exposes; this placeholder only has to exist so
    // the default parameter can be evaluated, and throws if it is ever actually reached.
    "./menuInput.js":
      "export const subscribeMenuInput = () => { throw new Error('browser input was not injected'); };",
  },
});
const { createMenuScreenHost } = await import(graph.url);
assert.equal(typeof createMenuScreenHost, "function", "createMenuScreenHost must be the real implementation");

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
// Results and Gets build their handle first (they need `.render(...)` before display) and
// therefore ADOPT it with screenHost.set() rather than mounting a builder. Assert that
// against the mount functions themselves. The previous version sliced main.ts between
// `case "results"` and `case "gets"`, which only worked while the wiring was inline in the
// switch; once each arm became a one-line call to a mountX() helper the slice contained no
// screenHost call at all and the guard could not pass.
function mountFunctionBody(source, name) {
  const start = source.indexOf(`function ${name}(`);
  assert.notEqual(start, -1, `main.ts must define ${name}()`);
  const end = source.indexOf("\nfunction ", start + 1);
  return source.slice(start, end === -1 ? undefined : end);
}
assert.match(
  mountFunctionBody(mainSource, "mountResults"),
  /screenHost\.set\(handle\)/,
  "Results handle must be adopted by the host",
);
assert.match(
  mountFunctionBody(mainSource, "mountGets"),
  /screenHost\.set\(handle\)/,
  "Gets handle must be adopted by the host",
);

console.log(
  `selfcheck-menu-flow PASS: ${screenFiles.length} targets; delivery/current/top routing, replacement, clear, overlay fall-through, exact-once teardown`,
);
