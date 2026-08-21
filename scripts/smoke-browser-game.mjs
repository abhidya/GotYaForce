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
const ownedRoot = path.resolve(root, ".tmp", "game-browser-smoke");

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
    response.writeHead(200, { "content-type": contentType(target) });
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

async function evaluate(cdp, expression) {
  const result = await cdp.send("Runtime.evaluate", { expression, awaitPromise: true, returnByValue: true });
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

async function drivePlayableRoute(cdp, url) {
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
    if (isExpectedMediaCancellation(event, request, url)) {
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
      let gfSeed = 0x47f0c3a5;
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
  // Several 60 Hz polls are enough to prove the held Intro key is consumed;
  // pause promptly so a very short deterministic battle cannot resolve first.
  await delay(75);
  const battleState = await evaluate(cdp, `(() => {
    const hud = document.querySelector(".gf-hud");
    const rect = hud?.getBoundingClientRect();
    const style = hud ? getComputedStyle(hud) : null;
    return {
      screen: window.__gf?.navigation?.screen,
      paused: window.__gf?.session?.paused,
      pauseOverlay: Boolean(document.querySelector(".gf-pause-overlay")),
      hudVisible: Boolean(hud && rect && rect.width > 0 && rect.height > 0 && style?.display !== "none" && style?.visibility !== "hidden"),
    };
  })()`);
  await enterKey(cdp, "keyUp");

  if (battleState.screen !== "battle" || battleState.paused !== false || battleState.pauseOverlay || !battleState.hudVisible) {
    throw new Error(`battle did not reach a visible, unpaused HUD: ${JSON.stringify(battleState)}`);
  }

  // A fresh press must still pause after the consumed briefing edge.
  await delay(50);
  await tapEnter(cdp);
  await waitFor(
    cdp,
    `window.__gf?.session?.paused === true && Boolean(document.querySelector(".gf-pause-overlay"))`,
    "first post-entry pause",
  );

  // Resume while Enter remains held. resumeBattle() must consume that edge so
  // the fixed-step poll cannot immediately reopen Pause.
  await enterKey(cdp, "keyDown");
  await waitFor(
    cdp,
    `window.__gf?.session?.paused === false && !document.querySelector(".gf-pause-overlay")`,
    "pause resume",
  );
  await delay(75);
  const resumeState = await evaluate(cdp, `({
    paused: window.__gf?.session?.paused,
    pauseOverlay: Boolean(document.querySelector(".gf-pause-overlay"))
  })`);
  await enterKey(cdp, "keyUp");
  if (resumeState.paused !== false || resumeState.pauseOverlay) {
    throw new Error(`held resume input reopened Pause: ${JSON.stringify(resumeState)}`);
  }

  // Release must re-arm the latch: one more fresh press pauses again.
  await delay(50);
  await tapEnter(cdp);
  await waitFor(
    cdp,
    `window.__gf?.session?.paused === true && Boolean(document.querySelector(".gf-pause-overlay"))`,
    "second post-resume pause",
  );
  const pauseCycle = await evaluate(cdp, `({
    paused: window.__gf?.session?.paused,
    pauseOverlay: Boolean(document.querySelector(".gf-pause-overlay"))
  })`);

  await waitForNetworkIdle(pendingRequests, lastNetworkActivity);
  if (errors.length > 0 || networkErrors.length > 0) {
    throw new Error(`browser emitted runtime errors:\n${[...errors, ...networkErrors.map((error) => `network: ${error}`)].join("\n")}`);
  }
  return {
    battle: battleState,
    resumed: resumeState,
    repaused: pauseCycle,
    expectedMediaCancellations: expectedMediaCancellations.length,
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
  const state = await drivePlayableRoute(cdp, started.url);
  process.stdout.write(
    `Browser smoke PASS: ${path.basename(browser)} production title -> Challenge -> Normal -> 1P -> box -> force -> briefing -> unpaused battle HUD ${JSON.stringify(state)}\n`,
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
