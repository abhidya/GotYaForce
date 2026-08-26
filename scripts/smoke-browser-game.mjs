#!/usr/bin/env node

import fs from "node:fs";
import http from "node:http";
import os from "node:os";
import path from "node:path";
import process from "node:process";
import { spawn } from "node:child_process";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import { CdpClient } from "./lib/cdp-client.mjs";
import { isExpectedMediaCancellation } from "./lib/network-gate.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const gameRoot = path.join(root, "apps", "game");
const gameRequire = createRequire(new URL("../apps/game/package.json", import.meta.url));
let WebSocket;
try {
  WebSocket = gameRequire("ws");
} catch (error) {
  throw new Error("browser smoke requires installed apps/game dependencies; run pnpm install", { cause: error });
}
const publicBase = "/GotYaForce/game/";
// GF_SMOKE_ROMWASM=threads drives the whole playable route on the
// threads-target relink (?romwasm=threads -> damage-core.threads.wasm with
// imported shared memory) and asserts the served module's memory model.
// Unset/default keeps the classic exported-memory build.
const romWasmVariant = process.env.GF_SMOKE_ROMWASM === "threads" ? "threads" : "default";
const ownedRoot = path.resolve(root, ".tmp", "game-browser-smoke");
// Use the real BOX DATA persistence seam, but give the edge regression enough
// deterministic reserves that combat cannot resolve during its first input polls.
// Repeated ids are valid force entries and deploy as distinct runtime actors.
const battleInputFixture = Object.freeze({
  slotNo: 1,
  name: "INPUT EDGE FIXTURE",
  randomSeed: 0x47f0c3a5,
  // A full reserve bench of the lowest-cost basic borg cannot exhaust or wipe
  // the fixed-seed opponent during the handful of input polls under test.
  borgIds: Object.freeze(Array.from({ length: 30 }, () => "pl0008")),
});

function delay(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

function contentType(file) {
  return {
    ".css": "text/css; charset=utf-8",
    ".glb": "model/gltf-binary",
    ".html": "text/html; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
    ".json": "application/json; charset=utf-8",
    ".ogg": "audio/ogg",
    ".png": "image/png",
    ".svg": "image/svg+xml",
    ".wasm": "application/wasm",
  }[path.extname(file).toLowerCase()] ?? "application/octet-stream";
}

async function buildProduction(buildDir) {
  // Build in-process: a timed-out package-manager child can leave Vite/esbuild
  // descendants behind. The smoke has no build subprocess to orphan.
  let viteEntry;
  try {
    viteEntry = gameRequire.resolve("vite");
  } catch (error) {
    throw new Error("browser smoke requires Vite from apps/game; run pnpm install", { cause: error });
  }
  const viteEsmEntry = path.join(path.dirname(viteEntry), "dist", "node", "index.js");
  const { build } = await import(pathToFileURL(viteEsmEntry).href);
  await build({
    root: gameRoot,
    build: { outDir: buildDir },
  });
}

function startStaticServer(dist) {
  const resolvedDist = path.resolve(dist);
  const server = http.createServer((request, response) => {
    const requestPath = decodeURIComponent(new URL(request.url ?? "/", "http://localhost").pathname);
    if (!requestPath.startsWith(publicBase)) {
      response.writeHead(404).end("Not found");
      return;
    }
    const relative = requestPath === publicBase ? "index.html" : requestPath.slice(publicBase.length);
    let target = path.resolve(resolvedDist, relative);
    if (target !== resolvedDist && !target.startsWith(`${resolvedDist}${path.sep}`)) {
      response.writeHead(403).end("Forbidden");
      return;
    }
    if (fs.existsSync(target) && fs.statSync(target).isDirectory()) target = path.join(target, "index.html");
    if (!fs.existsSync(target) || !fs.statSync(target).isFile()) {
      response.writeHead(404).end("Not found");
      return;
    }
    response.writeHead(200, {
      "content-type": contentType(target),
      // H1 cross-origin isolation: serve the gameplay route the way an
      // isolated production host behaves (GitHub Pages reaches the same state
      // via public/coi-serviceworker.js). With the headers present the
      // vendored SW deliberately no-ops, so the route runs without its
      // first-visit reload; the header-LESS SW path is proven separately by
      // the COI isolation phase at the end of this file.
      "cross-origin-opener-policy": "same-origin",
      "cross-origin-embedder-policy": "require-corp",
    });
    const stream = fs.createReadStream(target);
    stream.once("error", () => response.destroy());
    stream.pipe(response);
  });
  return new Promise((resolve, reject) => {
    server.once("error", reject);
    server.listen(0, "127.0.0.1", () => {
      const address = server.address();
      if (!address || typeof address === "string") {
        reject(new Error("could not allocate browser-smoke port"));
        return;
      }
      resolve({ server, url: `http://127.0.0.1:${address.port}${publicBase}` });
    });
  });
}

function isFile(candidate) {
  try {
    return Boolean(candidate) && fs.statSync(candidate).isFile();
  } catch {
    return false;
  }
}

function executableOnPath(names) {
  for (const directory of (process.env.PATH ?? "").split(path.delimiter)) {
    if (!directory) continue;
    for (const name of names) {
      const candidate = path.join(directory, name);
      if (isFile(candidate)) return candidate;
    }
  }
  return null;
}

function findBrowser() {
  const override = process.env.GF_BROWSER_PATH ?? process.env.BROWSER_PATH;
  if (override) {
    const resolved = path.resolve(override);
    if (!isFile(resolved)) throw new Error(`browser override does not exist: ${resolved}`);
    return resolved;
  }

  let candidates;
  let pathNames;
  if (process.platform === "win32") {
    candidates = [
      process.env.LOCALAPPDATA && path.join(process.env.LOCALAPPDATA, "Google", "Chrome", "Application", "chrome.exe"),
      process.env.LOCALAPPDATA && path.join(process.env.LOCALAPPDATA, "Microsoft", "Edge", "Application", "msedge.exe"),
      process.env.ProgramFiles && path.join(process.env.ProgramFiles, "Google", "Chrome", "Application", "chrome.exe"),
      process.env.ProgramFiles && path.join(process.env.ProgramFiles, "Microsoft", "Edge", "Application", "msedge.exe"),
      process.env["ProgramFiles(x86)"] && path.join(process.env["ProgramFiles(x86)"], "Google", "Chrome", "Application", "chrome.exe"),
      process.env["ProgramFiles(x86)"] && path.join(process.env["ProgramFiles(x86)"], "Microsoft", "Edge", "Application", "msedge.exe"),
    ];
    pathNames = ["chrome.exe", "msedge.exe", "chromium.exe"];
  } else if (process.platform === "darwin") {
    candidates = [
      "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome",
      "/Applications/Microsoft Edge.app/Contents/MacOS/Microsoft Edge",
      "/Applications/Chromium.app/Contents/MacOS/Chromium",
      path.join(os.homedir(), "Applications", "Google Chrome.app", "Contents", "MacOS", "Google Chrome"),
      path.join(os.homedir(), "Applications", "Microsoft Edge.app", "Contents", "MacOS", "Microsoft Edge"),
    ];
    pathNames = ["google-chrome", "chromium", "microsoft-edge"];
  } else {
    candidates = ["/usr/bin/google-chrome", "/usr/bin/chromium", "/usr/bin/chromium-browser", "/usr/bin/microsoft-edge"];
    pathNames = ["google-chrome", "google-chrome-stable", "chromium", "chromium-browser", "microsoft-edge"];
  }
  return candidates.find(isFile) ?? executableOnPath(pathNames);
}

async function waitForDevtools(profile, browserProcess, timeoutMs = 20_000) {
  const activePortFile = path.join(profile, "DevToolsActivePort");
  const deadline = Date.now() + timeoutMs;
  let spawnError = null;
  browserProcess.once("error", (error) => { spawnError = error; });
  while (Date.now() < deadline) {
    if (spawnError) throw spawnError;
    if (browserProcess.exitCode !== null) throw new Error(`browser exited before DevTools became ready (${browserProcess.exitCode})`);
    if (fs.existsSync(activePortFile)) {
      const [port] = fs.readFileSync(activePortFile, "utf8").trim().split(/\r?\n/);
      if (port) {
        try {
          const response = await fetch(`http://127.0.0.1:${port}/json/list`, {
            signal: AbortSignal.timeout(1000),
          });
          if (response.ok) {
            const pages = await response.json();
            const page = pages.find((entry) => entry.type === "page");
            if (page?.webSocketDebuggerUrl) return page.webSocketDebuggerUrl;
          }
        } catch {
          // Chrome writes the port before the HTTP endpoint is always ready.
        }
      }
    }
    await delay(50);
  }
  throw new Error("timed out waiting for Chrome DevTools endpoint");
}

async function evaluate(cdp, expression, timeoutMs) {
  const result = await cdp.send("Runtime.evaluate", { expression, awaitPromise: true, returnByValue: true }, timeoutMs);
  if (result.exceptionDetails) throw new Error(result.exceptionDetails.exception?.description ?? result.exceptionDetails.text);
  return result.result?.value;
}

async function waitFor(cdp, expression, label, timeoutMs = 30_000) {
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    if (await evaluate(cdp, expression)) return;
    await delay(100);
  }
  const snapshot = await evaluate(cdp, `({
    runtime: document.documentElement.dataset.gfRuntime,
    screen: window.__gf?.navigation?.screen,
    body: document.body?.innerText?.slice(0, 1000)
  })`);
  throw new Error(`timed out waiting for ${label}: ${JSON.stringify(snapshot)}`);
}

async function waitForBattle(cdp, expression, label, timeoutMs = 30_000) {
  return await waitFor(cdp, `(() => {
    const screen = window.__gf?.navigation?.screen;
    if (screen !== "battle") throw new Error("left battle while waiting for ${label}: " + screen);
    return Boolean(${expression});
  })()`, label, timeoutMs);
}

async function capturePauseState(cdp, label) {
  const state = await evaluate(cdp, `({
    screen: window.__gf?.navigation?.screen,
    paused: window.__gf?.session?.paused,
    pauseOverlay: Boolean(document.querySelector(".gf-pause-overlay"))
  })`);
  if (state.screen !== "battle") {
    throw new Error(`left battle while capturing ${label}: ${JSON.stringify(state)}`);
  }
  return state;
}

async function captureBattleFrame(cdp, label) {
  const state = await evaluate(cdp, `({
    screen: window.__gf?.navigation?.screen,
    frame: window.__gf?.session?.battle?.observe()?.frame
  })`);
  if (state.screen !== "battle" || !Number.isInteger(state.frame)) {
    throw new Error(`cannot capture battle frame for ${label}: ${JSON.stringify(state)}`);
  }
  return state.frame;
}

async function waitForBattleFrames(cdp, fromFrame, count, label) {
  await waitForBattle(
    cdp,
    `window.__gf?.session?.battle?.observe()?.frame >= ${fromFrame + count}`,
    label,
  );
}

async function click(cdp, selector) {
  await evaluate(cdp, `(() => {
    const node = document.querySelector(${JSON.stringify(selector)});
    if (!(node instanceof HTMLElement)) throw new Error("missing element: " + ${JSON.stringify(selector)});
    node.click();
    return true;
  })()`);
}

async function enterKey(cdp, type) {
  await cdp.send("Input.dispatchKeyEvent", {
    type,
    key: "Enter",
    code: "Enter",
    text: type === "keyDown" ? "\r" : "",
    unmodifiedText: type === "keyDown" ? "\r" : "",
    windowsVirtualKeyCode: 13,
    nativeVirtualKeyCode: 13,
  });
}

async function tapEnter(cdp) {
  await enterKey(cdp, "keyDown");
  await delay(50);
  await enterKey(cdp, "keyUp");
}

function remoteValue(value) {
  if ("value" in value) return JSON.stringify(value.value);
  return value.description ?? value.type ?? "unknown";
}

async function waitForNetworkIdle(pendingRequests, lastActivity, idleMs = 750, timeoutMs = 20_000) {
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    if (pendingRequests.size === 0 && Date.now() - lastActivity.value >= idleMs) return;
    await delay(50);
  }
  const pending = [...pendingRequests.values()].slice(0, 10);
  throw new Error(`network did not become idle; pending requests: ${JSON.stringify(pending)}`);
}

// `url` is what the browser navigates to (may carry ?romwasm=threads);
// `assetBase` is the query-less serving base the media-cancellation gate
// matches asset URLs against.
async function drivePlayableRoute(cdp, url, assetBase = url) {
  const errors = [];
  const networkErrors = [];
  const expectedMediaCancellations = [];
  const pendingRequests = new Map();
  const lastNetworkActivity = { value: Date.now() };
  const touchNetwork = () => { lastNetworkActivity.value = Date.now(); };
  cdp.on("Runtime.consoleAPICalled", (event) => {
    if (event.type === "error") errors.push(`console.error: ${event.args.map(remoteValue).join(" ")}`);
  });
  cdp.on("Runtime.exceptionThrown", (event) => {
    errors.push(`exception: ${event.exceptionDetails?.exception?.description ?? event.exceptionDetails?.text}`);
  });
  cdp.on("Log.entryAdded", (event) => {
    if (event.entry?.level === "error") {
      errors.push(`log.error: ${event.entry.text}${event.entry.url ? ` (${event.entry.url})` : ""}`);
    }
  });
  cdp.on("Network.responseReceived", (event) => {
    if (event.response?.status >= 400) networkErrors.push(`${event.response.status} ${event.response.url}`);
  });
  cdp.on("Network.requestWillBeSent", (event) => {
    pendingRequests.set(event.requestId, event.request?.url ?? event.requestId);
    touchNetwork();
  });
  cdp.on("Network.loadingFinished", (event) => {
    pendingRequests.delete(event.requestId);
    touchNetwork();
  });
  cdp.on("Network.loadingFailed", (event) => {
    const request = pendingRequests.get(event.requestId) ?? event.requestId;
    pendingRequests.delete(event.requestId);
    touchNetwork();
    // HTMLAudioElement intentionally aborts its current fetch when screen/BGM
    // routing replaces a sound. Permit only that explicit cancellation shape;
    // resets, timeouts, blocked requests, and every non-media failure stay fatal.
    if (isExpectedMediaCancellation(event, request, assetBase)) {
      expectedMediaCancellations.push(request);
      return;
    }
    networkErrors.push(
      `${event.errorText ?? "loading failed"} ${request}` +
      `${event.blockedReason ? ` blocked=${event.blockedReason}` : ""}` +
      `${event.canceled ? " canceled=true" : ""}`,
    );
  });

  await Promise.all([
    cdp.send("Page.enable"),
    cdp.send("Runtime.enable"),
    cdp.send("Log.enable"),
    cdp.send("Network.enable"),
  ]);
  await cdp.send("Page.addScriptToEvaluateOnNewDocument", {
    source: `
      localStorage.clear();
      localStorage.setItem("gf-force-slots-v1", ${JSON.stringify(JSON.stringify([
        {
          no: battleInputFixture.slotNo,
          name: battleInputFixture.name,
          borgIds: battleInputFixture.borgIds,
        },
      ]))});
      let gfSeed = ${battleInputFixture.randomSeed};
      Math.random = () => {
        gfSeed |= 0;
        gfSeed = (gfSeed + 0x6d2b79f5) | 0;
        let t = Math.imul(gfSeed ^ (gfSeed >>> 15), 1 | gfSeed);
        t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
        return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
      };
      window.addEventListener("unhandledrejection", (event) => {
        console.error("[unhandledrejection]", event.reason);
      });
    `,
  });
  await cdp.send("Page.navigate", { url });

  await waitFor(
    cdp,
    `document.documentElement.dataset.gfRuntime === "boot-ready" && window.__gf?.navigation?.screen === "title"`,
    "asset-backed boot-ready title",
    60_000,
  );
  await waitFor(cdp, `document.querySelector(".gf-title-intro")?.dataset.gfIntroDone === "true"`, "title Press Start", 75_000);
  await tapEnter(cdp);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "menu"`, "main menu");

  await click(cdp, `[data-mode="challenge"]`);
  await waitFor(cdp, `document.querySelector(".gf-mainmenu")?.dataset.mode === "challenge"`, "Challenge menu selection");
  await tapEnter(cdp);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "difficulty"`, "Challenge difficulty");

  await waitFor(cdp, `document.querySelector(".gf-select-difficulty")?.dataset.motionReady === "true"`, "difficulty input readiness");
  await click(cdp, `[data-diff="normal"]`);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "players"`, "player count");

  await waitFor(cdp, `document.querySelector(".gf-select-players")?.dataset.motionReady === "true"`, "player input readiness");
  await click(cdp, `[data-count="1"]`);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "load-box"`, "Load Box Data");

  await tapEnter(cdp);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "select-force"`, "Select Force");
  await tapEnter(cdp);
  await waitFor(cdp, `window.__gf?.navigation?.screen === "briefing"`, "battle briefing", 45_000);

  // Deliberately keep Enter held across the synchronous briefing -> battle
  // handoff. This reproduces the historical pause-edge leak.
  await enterKey(cdp, "keyDown");
  await waitFor(cdp, `window.__gf?.navigation?.screen === "battle" && document.querySelector(".gf-hud")`, "battle HUD", 60_000);
  // Hold through actual fixed-step boundaries rather than guessing how long a
  // busy browser needs to schedule requestAnimationFrame.
  const introHoldFrame = await captureBattleFrame(cdp, "held briefing confirmation");
  await waitForBattleFrames(cdp, introHoldFrame, 2, "held briefing confirmation polls");
  const battleState = await evaluate(cdp, `(() => {
    const hud = document.querySelector(".gf-hud");
    const rect = hud?.getBoundingClientRect();
    const style = hud ? getComputedStyle(hud) : null;
    const playerForce = window.__gf?.session?.config?.forces?.find(
      (force) => force.team === "player" && force.ownerPlayer === 0
    );
    return {
      screen: window.__gf?.navigation?.screen,
      paused: window.__gf?.session?.paused,
      pauseOverlay: Boolean(document.querySelector(".gf-pause-overlay")),
      hudVisible: Boolean(hud && rect && rect.width > 0 && rect.height > 0 && style?.display !== "none" && style?.visibility !== "hidden"),
      battleResult: window.__gf?.session?.battle?.observe()?.result,
      playerRoster: playerForce?.borgIds ?? null,
    };
  })()`);
  await enterKey(cdp, "keyUp");

  const fixtureRosterMatches =
    JSON.stringify(battleState.playerRoster) === JSON.stringify(battleInputFixture.borgIds);
  if (
    battleState.screen !== "battle" ||
    battleState.paused !== false ||
    battleState.pauseOverlay ||
    !battleState.hudVisible ||
    battleState.battleResult !== "ongoing" ||
    !fixtureRosterMatches
  ) {
    throw new Error(`battle did not reach a visible, unpaused HUD: ${JSON.stringify(battleState)}`);
  }

  // The release must be observed by real fixed steps before the fresh press.
  const introReleaseFrame = await captureBattleFrame(cdp, "briefing confirmation release");
  await waitForBattleFrames(cdp, introReleaseFrame, 2, "briefing confirmation release polls");

  // A fresh press must still pause after the consumed briefing edge. Keep it
  // down until Pause opens so a delayed animation frame cannot miss the edge.
  await enterKey(cdp, "keyDown");
  await waitForBattle(
    cdp,
    `window.__gf?.session?.paused === true && Boolean(document.querySelector(".gf-pause-overlay"))`,
    "first post-entry pause",
  );
  await enterKey(cdp, "keyUp");

  // Resume while Enter remains held. resumeBattle() must consume that edge so
  // the fixed-step poll cannot immediately reopen Pause.
  await enterKey(cdp, "keyDown");
  await waitForBattle(
    cdp,
    `window.__gf?.session?.paused === false && !document.querySelector(".gf-pause-overlay")`,
    "pause resume",
  );
  const resumeHoldFrame = await captureBattleFrame(cdp, "held-input resume");
  await waitForBattleFrames(cdp, resumeHoldFrame, 2, "held-input resume polls");
  const resumeState = await capturePauseState(cdp, "held-input resume");
  await enterKey(cdp, "keyUp");
  if (resumeState.paused !== false || resumeState.pauseOverlay) {
    throw new Error(`held resume input reopened Pause: ${JSON.stringify(resumeState)}`);
  }

  // Release must re-arm the latch: one more fresh press pauses again.
  const resumeReleaseFrame = await captureBattleFrame(cdp, "resume release");
  await waitForBattleFrames(cdp, resumeReleaseFrame, 2, "resume release polls");
  await enterKey(cdp, "keyDown");
  await waitForBattle(
    cdp,
    `window.__gf?.session?.paused === true && Boolean(document.querySelector(".gf-pause-overlay"))`,
    "second post-resume pause",
  );
  const pauseCycle = await capturePauseState(cdp, "second post-resume pause");
  await enterKey(cdp, "keyUp");

  await waitForNetworkIdle(pendingRequests, lastNetworkActivity);
  if (errors.length > 0 || networkErrors.length > 0) {
    throw new Error(`browser emitted runtime errors:\n${[...errors, ...networkErrors.map((error) => `network: ${error}`)].join("\n")}`);
  }
  // Optional deep proof (GF_SMOKE_ROM_HIT=1): land a real combat hit and watch
  // the ROM call counters rise past the boot gate's 256 — the moment a landed
  // hit's damage is computed by the ported GameCube code. Opt-in so the default
  // smoke stays free of combat-outcome nondeterminism.
  if (process.env.GF_SMOKE_ROM_HIT === "1") {
    const before = await evaluate(cdp, `window.__romDamage?.callCounts?.computeBaseDamage ?? -1`);
    if (before < 0) throw new Error("ROM-wasm not live before the hit phase");
    // The route above ends PAUSED (second post-resume pause) — a frozen sim
    // lands no hits. Resume via the pause menu before fighting.
    await tapEnter(cdp);
    await waitForBattle(
      cdp,
      `window.__gf?.session?.paused === false && !document.querySelector(".gf-pause-overlay")`,
      "battle resumed for the ROM hit phase",
    );
    const key = (code, vk, type) => cdp.send("Input.dispatchKeyEvent", {
      type, key: code.replace("Key", "").toLowerCase(), code,
      windowsVirtualKeyCode: vk, nativeVirtualKeyCode: vk,
    });
    // The CPU side attacks on its own; the player also holds lock-on + attack.
    // ANY landed hit (either direction) computes damage through the seam.
    await key("KeyU", 85, "keyDown");
    await key("KeyK", 75, "keyDown");
    try {
      await waitForBattle(
        cdp,
        `(window.__romDamage?.callCounts?.computeBaseDamage ?? 0) > ${before}`,
        "a landed hit computed by the ROM wasm",
        180_000,
      );
    } finally {
      await key("KeyK", 75, "keyUp");
      await key("KeyU", 85, "keyUp");
    }
    const after = await evaluate(cdp, `window.__romDamage.callCounts.computeBaseDamage`);
    process.stdout.write(`ROM combat hit PROVEN: computeBaseDamage ${before} -> ${after} during live battle
`);
  }

  // ROM-wasm proof: the ported damage-core unit must be LIVE (installed after
  // its 256-case fidelity gate) for the battle this smoke just played. The call
  // counts show how much of the session the ROM code actually served.
  const romDamage = await evaluate(cdp, `({
    live: Boolean(window.__romDamage),
    calls: window.__romDamage ? { ...window.__romDamage.callCounts } : null,
    shims: window.__romDamage ? { ...window.__romDamage.shimCounts } : null,
    memory: window.__romDamage?.memoryInfo ?? null
  })`);
  if (!romDamage.live) {
    throw new Error("ROM-wasm damage core is not live — the game fell back to the TS port");
  }
  // Step-8 threads proof (GF_SMOKE_ROMWASM=threads): the battle above must have
  // been served by the threads-target relink — imported SHARED memory, which
  // only instantiates under the COI headers this server sends.
  if (romWasmVariant === "threads") {
    if (!romDamage.memory?.imported || !romDamage.memory?.shared) {
      throw new Error(
        `threads smoke did not run on imported shared memory: ${JSON.stringify(romDamage.memory)}`,
      );
    }
  }

  // Gameplay proofs — deterministic sim battles built INSIDE the production bundle
  // (apps/game/src/sim/gameplayProof.ts, exposed as window.__gf.selfcheck). They run the
  // exact shipped combat code, ROM-wasm damage seam included, without touching the live
  // battle. Proves the owner-reported core loop: attack input → damage applied for three
  // different borgs (B attack AND X special each connect), a unit driven at the arena
  // edge is clamped inside stage bounds without falling out of the world, and a jump
  // arc rises then lands back on its takeoff surface.
  // These proofs step thousands of synchronous sim frames inside the page; on a loaded
  // machine they can exceed the default 15s CDP call timeout, so give them their own.
  const gameplay = {
    attacks: await evaluate(cdp, `window.__gf.selfcheck.attackDamage(["pl0615", "pl0102", "pl0008"])`, 180_000),
    bounds: await evaluate(cdp, `window.__gf.selfcheck.boundsClamp()`, 60_000),
    jump: await evaluate(cdp, `window.__gf.selfcheck.jumpArc()`, 60_000),
  };
  for (const proof of gameplay.attacks) {
    if (!(proof.attackDamage > 0)) {
      throw new Error(`B attack dealt no damage for ${proof.borgId}: ${JSON.stringify(gameplay.attacks)}`);
    }
    if (!(proof.specialDamage > 0)) {
      throw new Error(`X special dealt no damage for ${proof.borgId}: ${JSON.stringify(gameplay.attacks)}`);
    }
  }
  if (!gameplay.bounds.clamped) {
    throw new Error(`arena bounds clamp failed: ${JSON.stringify(gameplay.bounds)}`);
  }
  if (!gameplay.jump.rose || !gameplay.jump.landed) {
    throw new Error(`jump arc did not rise+land: ${JSON.stringify(gameplay.jump)}`);
  }

  // Animation liveness — the visual gap the state-only checks missed (T-pose regression,
  // 2026-08-25): every model-ready battle actor must be PLAYING at least one mixer clip
  // with effective weight. An actor with runningClips 0 renders its bind pose (T-pose)
  // no matter what the sim state says. battleScene.animationDebug() counts actions that
  // are running OR paused-with-weight (a clamped one-shot holding its end pose counts as
  // posed, not T-posed; permanently accumulating ones are the bug the crossfade fix
  // removed).
  // Clip loads are async right after an actor's model attaches, so allow a short grace
  // period before declaring an actor clipless.
  let readyActors = [];
  let tposed = [];
  for (let attempt = 0; attempt < 6; attempt += 1) {
    const animation = await evaluate(cdp, `window.__gf.animationDebug()`);
    readyActors = animation.filter((a) => a.ready && !a.placeholder);
    tposed = readyActors.filter((a) => a.runningClips === 0);
    if (readyActors.length > 0 && tposed.length === 0) break;
    await delay(500);
  }
  if (readyActors.length === 0) {
    throw new Error("no model-ready battle actors to verify animation on");
  }
  if (tposed.length > 0) {
    throw new Error(`T-pose regression: battle actors with no active animation clip: ${JSON.stringify(tposed)}`);
  }

  return {
    battle: battleState,
    animation: { actors: readyActors.length },
    resumed: resumeState,
    repaused: pauseCycle,
    expectedMediaCancellations: expectedMediaCancellations.length,
    romDamage,
    gameplay,
  };
}

const browser = findBrowser();
if (!browser) throw new Error("Chrome/Edge/Chromium not found; set GF_BROWSER_PATH to its executable");
fs.mkdirSync(ownedRoot, { recursive: true });
const buildDir = fs.mkdtempSync(path.join(ownedRoot, "build-"));
const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
let server;
let browserProcess;
let cdp;

try {
  await buildProduction(buildDir);
  const started = await startStaticServer(buildDir);
  server = started.server;
  browserProcess = spawn(browser, [
    "--headless=new",
    "--remote-debugging-port=0",
    "--disable-dev-shm-usage",
    "--disable-background-timer-throttling",
    "--disable-backgrounding-occluded-windows",
    "--disable-renderer-backgrounding",
    "--enable-unsafe-swiftshader",
    "--use-angle=swiftshader",
    "--no-first-run",
    "--no-default-browser-check",
    "--window-size=1280,960",
    `--user-data-dir=${profile}`,
    "about:blank",
  ], { cwd: root, windowsHide: true, stdio: "ignore" });
  const debuggerUrl = await waitForDevtools(profile, browserProcess);
  cdp = await CdpClient.connect(debuggerUrl, WebSocket);
  const routeUrl = romWasmVariant === "threads" ? `${started.url}?romwasm=threads` : started.url;
  const state = await drivePlayableRoute(cdp, routeUrl, started.url);
  process.stdout.write(
    `Browser smoke PASS (romwasm=${romWasmVariant}): ${path.basename(browser)} production title -> Challenge -> Normal -> 1P -> box -> force -> briefing -> unpaused battle HUD ${JSON.stringify(state)}\n`,
  );
} finally {
  if (cdp) {
    try { await cdp.send("Browser.close"); } catch { /* browser may already be gone */ }
    cdp.close();
  } else if (browserProcess && browserProcess.exitCode === null) {
    browserProcess.kill();
  }
  if (browserProcess && browserProcess.exitCode === null) {
    await Promise.race([
      new Promise((resolve) => browserProcess.once("close", resolve)),
      delay(3000),
    ]);
  }
  if (server) await new Promise((resolve) => server.close(resolve));
  for (const target of [profile, buildDir]) {
    const resolved = path.resolve(target);
    if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) throw new Error(`refusing to remove non-owned browser-smoke path: ${resolved}`);
    try {
      fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
    } catch (error) {
      if (error?.code !== "EPERM") throw error;
      process.stderr.write(`Browser smoke cleanup deferred (path still locked): ${resolved}\n`);
    }
  }
}

// ============================================================================
// >>> H1 COI ISOLATION PHASE (separate, self-contained — keep at end of file).
// Asserts window.crossOriginIsolated === true in dev-header mode (Vite
// server.headers) AND in production coi-serviceworker mode, tolerating the
// SW's first-load reload. Owns its own build/servers/browser; see
// scripts/smoke-coi-phase.mjs. Do not fold into the gameplay route above.
// ============================================================================
{
  const { runCoiPhase } = await import("./smoke-coi-phase.mjs");
  await runCoiPhase();
}
// >>> END H1 COI ISOLATION PHASE =============================================
