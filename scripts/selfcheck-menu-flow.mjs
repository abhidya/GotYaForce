#!/usr/bin/env node
/**
 * selfcheck-menu-flow — STATIC wiring check for the shared menu-input bus + the
 * boot-to-battle screen flow. This is honestly NOT a browser test: it never boots a
 * DOM, never runs three.js, and never executes any of apps/game/src at all. It parses
 * the TypeScript SOURCE TEXT of apps/game/src/main.ts and apps/game/src/ui/screens/*.ts
 * with plain string/regex checks and asserts a few structural invariants that the
 * boot-to-battle UX work (menuInput.ts + the 10-screen refactor) depends on:
 *
 *   (a) every screen module in apps/game/src/ui/screens/*.ts subscribes to the shared
 *       menu-input bus (imports subscribeMenuInput from ../menuInput.js and calls it),
 *       and does NOT register its own `window.addEventListener("keydown", ...)` for the
 *       common actions — except a small documented allowlist of screens that
 *       legitimately need a raw listener for behavior broader than the bus's mapped key
 *       set (currently: TitleIntro's "press ANY key to continue").
 *
 *   (b) every showX() screen-transition function in main.ts has at least one visible
 *       "way out" — a callback wired to a flow-advancing function (another showX call,
 *       or an inline advance like enterBattle/startRun) OR an onBack/onQuit callback
 *       wired back into the flow. This is a grep-level structural check (it looks for
 *       `showXxx(` / `startRun(` / `enterBattle(` call-expressions inside each showX
 *       function's body, keyed by brace-depth-scanning from the `function showX(`
 *       declaration to its matching closing brace) — it does NOT prove the callback is
 *       reachable at runtime, only that the source text wires *something* forward.
 *
 * What this script deliberately does NOT check (again: a static wiring check, not a
 * behavioral test): whether the bus actually delivers gamepad/keyboard events at
 * runtime, whether LIFO subscriber ordering behaves correctly under real mount/unmount
 * sequences, whether the stall-guard timeout in challengeMenuMotion.ts actually unblocks
 * a real stalled animation, or whether a fresh-profile Select Force screen renders a
 * sane default force in a real browser. Those are covered by manual/preview
 * verification, not by this script.
 */
import { readFileSync, readdirSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const screensDir = path.join(repoRoot, "apps/game/src/ui/screens");
const mainTsPath = path.join(repoRoot, "apps/game/src/main.ts");

// Screens allowed to keep a raw `window.addEventListener("keydown", ...)` alongside (or
// instead of, if the bus doesn't cover their need) the shared bus subscription, with the
// documented reason. Everything else in screensDir/*.ts must have ZERO raw keydown
// listeners — the common actions must route through subscribeMenuInput exclusively.
const RAW_KEYDOWN_ALLOWLIST = {
  "TitleIntro.ts": "press-ANY-key-to-continue is broader than the bus's mapped key set",
};

const failures = [];
const notes = [];

function fail(message) {
  failures.push(message);
}

function note(message) {
  notes.push(message);
}

// ---------------------------------------------------------------------------
// Check (a): every screen subscribes to the bus; no stray raw keydown listeners.
// ---------------------------------------------------------------------------

const screenFiles = readdirSync(screensDir).filter((f) => f.endsWith(".ts"));
if (screenFiles.length === 0) {
  fail(`No screen files found under ${screensDir}`);
}

for (const file of screenFiles) {
  const fullPath = path.join(screensDir, file);
  const src = readFileSync(fullPath, "utf8");

  const importsBus = /from\s+["']\.\.\/menuInput\.js["']/.test(src) && /subscribeMenuInput/.test(src);
  const callsSubscribe = /subscribeMenuInput\s*\(/.test(src);
  const hasRawKeydown = /window\.addEventListener\(\s*["']keydown["']/.test(src);
  const hasUnsubscribeCall = /unsubscribeMenuInput\s*\(\s*\)/.test(src) || /unsubscribe\w*\s*\(\s*\)/.test(src);

  if (!importsBus || !callsSubscribe) {
    fail(`${file}: does not subscribe to the shared menu-input bus (expected an import of subscribeMenuInput from ../menuInput.js and a call to it)`);
  }

  if (hasRawKeydown && !RAW_KEYDOWN_ALLOWLIST[file]) {
    fail(`${file}: registers a raw window keydown listener but is not on the documented allowlist (RAW_KEYDOWN_ALLOWLIST in this script) — common actions must route through subscribeMenuInput`);
  } else if (hasRawKeydown && RAW_KEYDOWN_ALLOWLIST[file]) {
    note(`${file}: raw keydown listener allowed — ${RAW_KEYDOWN_ALLOWLIST[file]}`);
  }

  // destroy() must unsubscribe: look for a destroy() method whose body (naively, the
  // text between "destroy:" and the next top-level "}," at the same indent) calls the
  // unsubscribe function returned by subscribeMenuInput. This is a soft check (string
  // search within a window around "destroy:"), not a full parser, by design.
  const destroyIdx = src.indexOf("destroy:");
  if (destroyIdx === -1 && !/destroy\s*\(/.test(src)) {
    fail(`${file}: no destroy() handle found`);
  } else {
    const windowText = src.slice(Math.max(0, destroyIdx - 200), destroyIdx + 400);
    if (!/unsubscribe/i.test(windowText) && !hasUnsubscribeCall) {
      fail(`${file}: destroy() does not appear to call the menu-input unsubscribe function`);
    }
  }
}

// ---------------------------------------------------------------------------
// Check (b): every showX() in main.ts has a back/advance path.
// ---------------------------------------------------------------------------

const mainSrc = readFileSync(mainTsPath, "utf8");

// Extract each top-level `function showXxx(...) { ... }` body by brace-depth scanning
// from the declaration to its matching close brace (grep-level: does not parse the AST,
// just counts braces starting at the function's own opening brace).
function extractFunctionBodies(src, namePattern) {
  const results = [];
  const re = new RegExp(`function\\s+(${namePattern})\\s*\\(`, "g");
  let match;
  while ((match = re.exec(src))) {
    const name = match[1];
    const openBraceIdx = src.indexOf("{", match.index);
    if (openBraceIdx === -1) continue;
    let depth = 0;
    let i = openBraceIdx;
    for (; i < src.length; i += 1) {
      if (src[i] === "{") depth += 1;
      else if (src[i] === "}") {
        depth -= 1;
        if (depth === 0) break;
      }
    }
    results.push({ name, body: src.slice(openBraceIdx, i + 1) });
  }
  return results;
}

const showFunctions = extractFunctionBodies(mainSrc, "show\\w+");
if (showFunctions.length === 0) {
  fail("No showX() functions found in main.ts — flow-state-machine shape has changed; update this selfcheck");
}

// A showX body "has a way out" if its text calls another showX(...)/startRun()/
// enterBattle(...)/advanceRun(...) (an advance — advanceRun is showResults's one level
// of indirection: its onAdvance callback calls advanceRun(), which itself calls
// showBattleIntro/showMenu) OR references onBack/onQuit/onAdvance (a documented
// forward/backward callback some caller wires up). showLoadingMessage is exempt (see
// below) since it's a boot/error utility screen, not a flow node with callbacks.
const ADVANCE_CALL_RE = /\b(show\w+|startRun|enterBattle|advanceRun)\s*\(/g;
const BACK_CALLBACK_RE = /\bon(Back|Quit|Advance)\b/;

for (const { name, body } of showFunctions) {
  const advanceCalls = [...body.matchAll(ADVANCE_CALL_RE)]
    .map((m) => m[1])
    .filter((called) => called !== name); // exclude self-recursion from counting as "a way out"
  const hasAdvance = advanceCalls.length > 0;
  const hasBack = BACK_CALLBACK_RE.test(body);

  if (name === "showLoadingMessage") {
    // Terminal/utility screen (boot error message), not a flow node with callbacks.
    continue;
  }

  if (!hasAdvance && !hasBack) {
    fail(`main.ts: ${name}() has neither an advance call (show*/startRun/enterBattle) nor a back/quit callback (onBack/onQuit) in its body — looks like a dead-end screen`);
  } else {
    note(`main.ts: ${name}() — advance=[${[...new Set(advanceCalls)].join(", ") || "none"}] hasBackCallback=${hasBack}`);
  }
}

// ---------------------------------------------------------------------------
// Report
// ---------------------------------------------------------------------------

console.log(`selfcheck-menu-flow: checked ${screenFiles.length} screen modules + ${showFunctions.length} showX() flow functions`);
for (const n of notes) console.log(`  note: ${n}`);

if (failures.length > 0) {
  console.error(`\nselfcheck-menu-flow FAILED (${failures.length}):`);
  for (const f of failures) console.error(`  - ${f}`);
  process.exit(1);
}

console.log("\nselfcheck-menu-flow PASS (static wiring check only — see file header for what this does not prove)");
