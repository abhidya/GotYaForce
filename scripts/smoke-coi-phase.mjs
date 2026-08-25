#!/usr/bin/env node
// ============================================================================
// H1 cross-origin isolation smoke phase (docs/playable-port-design.md,
// V4 AMENDMENTS H1 + V5 note 2). SELF-CONTAINED on purpose: it owns its own
// build, servers, browser, and CDP session so it can be appended to
// scripts/smoke-browser-game.mjs as a single import line without touching the
// gameplay route above it.
//
// Asserts window.crossOriginIsolated === true in BOTH serving modes:
//   dev-header mode : the real Vite dev server (apps/game/vite.config.ts sends
//                     COOP/COEP via server.headers); the coi-serviceworker must
//                     NO-OP (no controller).
//   production mode : the built bundle served WITHOUT any isolation headers,
//                     simulating GitHub Pages; the vendored
//                     public/coi-serviceworker.js must install, reload the page
//                     once, and re-serve everything isolated. The phase
//                     TOLERATES that first-load reload (V5 normative note 2) by
//                     polling across the navigation instead of assuming a
//                     stable execution context.
// Both modes must also reach the asset-backed boot-ready title screen, proving
// the game still boots under isolation.
//
// Runs standalone (node scripts/smoke-coi-phase.mjs) or via runCoiPhase().
// ============================================================================

import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import process from "node:process";
import { spawn } from "node:child_process";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import { CdpClient } from "./lib/cdp-client.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const gameRoot = path.join(root, "apps", "game");
const gameRequire = createRequire(pathToFileURL(path.join(gameRoot, "package.json")).href);
const publicBase = "/GotYaForce/game/";
const ownedRoot = path.resolve(root, ".tmp", "game-coi-smoke");

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

async function importVite() {
  let viteEntry;
  try {
    viteEntry = gameRequire.resolve("vite");
  } catch (error) {
    throw new Error("COI phase requires Vite from apps/game; run pnpm install", { cause: error });
  }
  const viteEsmEntry = path.join(path.dirname(viteEntry), "dist", "node", "index.js");
  return await import(pathToFileURL(viteEsmEntry).href);
}

async function buildProduction(buildDir) {
  const { build } = await importVite();
  await build({ root: gameRoot, build: { outDir: buildDir }, logLevel: "warn" });
}

// GitHub Pages simulation: static files, correct subpath base, and — the whole
// point of this phase — NO COOP/COEP response headers. Isolation must come
// from the vendored coi-serviceworker alone.
function startHeaderlessStaticServer(dist) {
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
        reject(new Error("could not allocate COI-phase static port"));
        return;
      }
      resolve({ server, url: `http://127.0.0.1:${address.port}${publicBase}` });
    });
  });
}

// The REAL dev server, loading apps/game/vite.config.ts, so this asserts the
// committed server.headers config rather than a re-declared copy of it.
async function startDevServer() {
  const { createServer } = await importVite();
  const server = await createServer({
    root: gameRoot,
    logLevel: "warn",
    server: { port: 0, host: "127.0.0.1" },
  });
  await server.listen();
  const address = server.httpServer?.address();
  if (!address || typeof address === "string") {
    await server.close();
    throw new Error("could not allocate COI-phase dev port");
  }
  return { server, url: `http://127.0.0.1:${address.port}/` };
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
    ];
    pathNames = ["google-chrome", "chromium", "microsoft-edge"];
  } else {
    candidates = ["/usr/bin/google-chrome", "/usr/bin/chromium", "/usr/bin/chromium-browser", "/usr/bin/microsoft-edge"];
    pathNames = ["google-chrome", "google-chrome-stable", "chromium", "chromium-browser", "microsoft-edge"];
  }
  return candidates.find(isFile) ?? executableOnPath(pathNames);
}

async function waitForDevtools(profile, browserProcess, timeoutMs = 60_000) {
  const activePortFile = path.join(profile, "DevToolsActivePort");
  const deadline = Date.now() + timeoutMs;
  let spawnError = null;
  browserProcess.once("error", (error) => { spawnError = error; });
  while (Date.now() < deadline) {
    if (spawnError) throw spawnError;
    if (browserProcess.exitCode !== null) throw new Error(`COI-phase browser exited before DevTools became ready (${browserProcess.exitCode})`);
    if (fs.existsSync(activePortFile)) {
      const [port] = fs.readFileSync(activePortFile, "utf8").trim().split(/\r?\n/);
      if (port) {
        try {
          const response = await fetch(`http://127.0.0.1:${port}/json/list`, { signal: AbortSignal.timeout(1000) });
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
  throw new Error("timed out waiting for the COI-phase Chrome DevTools endpoint");
}

async function evaluate(cdp, expression) {
  const result = await cdp.send("Runtime.evaluate", { expression, awaitPromise: true, returnByValue: true });
  if (result.exceptionDetails) throw new Error(result.exceptionDetails.exception?.description ?? result.exceptionDetails.text);
  return result.result?.value;
}

// Reload-tolerant poll: the coi-serviceworker's first-visit reload destroys the
// execution context mid-poll, which surfaces as protocol/evaluate errors here.
// Those are EXPECTED during this phase — swallow them and keep polling until
// the predicate holds in the post-reload context or the deadline passes.
async function waitForAcrossReloads(cdp, expression, label, timeoutMs) {
  const deadline = Date.now() + timeoutMs;
  let lastError = null;
  while (Date.now() < deadline) {
    try {
      if (await evaluate(cdp, expression)) return;
      lastError = null;
    } catch (error) {
      lastError = error;
    }
    await delay(100);
  }
  throw new Error(`timed out waiting for ${label}${lastError ? ` (last evaluate error: ${lastError.message})` : ""}`);
}

async function captureIsolationState(cdp) {
  return await evaluate(cdp, `({
    crossOriginIsolated: window.crossOriginIsolated,
    sharedArrayBuffer: typeof SharedArrayBuffer === "function",
    serviceWorkerController: navigator.serviceWorker?.controller?.scriptURL ?? null,
    navigationType: performance.getEntriesByType("navigation")[0]?.type ?? null,
    runtime: document.documentElement.dataset.gfRuntime ?? null,
    screen: window.__gf?.navigation?.screen ?? null,
  })`);
}

async function driveIsolationCheck(cdp, url, { expectServiceWorker, label }) {
  await cdp.send("Page.navigate", { url });
  // Gate 1 (H1): isolation itself, tolerant of the SW first-load reload.
  await waitForAcrossReloads(cdp, "window.crossOriginIsolated === true", `${label}: crossOriginIsolated`, 60_000);
  // Gate 2: the game still boots to the asset-backed title under isolation.
  await waitForAcrossReloads(
    cdp,
    `window.crossOriginIsolated === true && document.documentElement.dataset.gfRuntime === "boot-ready" && window.__gf?.navigation?.screen === "title"`,
    `${label}: boot-ready title under isolation`,
    120_000,
  );
  const state = await captureIsolationState(cdp);
  if (state.crossOriginIsolated !== true) {
    throw new Error(`${label}: crossOriginIsolated is not true after settle: ${JSON.stringify(state)}`);
  }
  if (!state.sharedArrayBuffer) {
    throw new Error(`${label}: SharedArrayBuffer unavailable despite isolation: ${JSON.stringify(state)}`);
  }
  if (expectServiceWorker && !state.serviceWorkerController) {
    throw new Error(`${label}: expected the coi-serviceworker to control the page: ${JSON.stringify(state)}`);
  }
  if (!expectServiceWorker && state.serviceWorkerController) {
    throw new Error(`${label}: coi-serviceworker registered although headers were already present: ${JSON.stringify(state)}`);
  }
  return state;
}

export async function runCoiPhase() {
  const browser = findBrowser();
  if (!browser) throw new Error("Chrome/Edge/Chromium not found; set GF_BROWSER_PATH to its executable");
  const gameWebSocket = gameRequire("ws");

  fs.mkdirSync(ownedRoot, { recursive: true });
  const buildDir = fs.mkdtempSync(path.join(ownedRoot, "build-"));
  const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
  let devServer;
  let staticServer;
  let browserProcess;
  let cdp;
  try {
    // Dev mode runs FIRST and the dev server closes before the production
    // build: an in-process vite build() tears down the shared esbuild
    // transform service, which kills a still-running dev server's transforms.
    devServer = await startDevServer();

    browserProcess = spawn(browser, [
      "--headless=new",
      "--remote-debugging-port=0",
      "--disable-dev-shm-usage",
      "--enable-unsafe-swiftshader",
      "--use-angle=swiftshader",
      "--no-first-run",
      "--no-default-browser-check",
      "--window-size=1280,960",
      `--user-data-dir=${profile}`,
      "about:blank",
    ], { cwd: root, windowsHide: true, stdio: "ignore" });
    // This phase often runs right after the gameplay smoke closed ITS browser;
    // on a loaded machine the fresh instance can accept /json/list before its
    // DevTools WebSocket endpoint keeps up. Retry the connect, re-resolving
    // the endpoint each attempt.
    let lastConnectError = null;
    for (let attempt = 0; attempt < 4 && !cdp; attempt += 1) {
      const debuggerUrl = await waitForDevtools(profile, browserProcess);
      try {
        cdp = await CdpClient.connect(debuggerUrl, gameWebSocket, 20_000);
      } catch (error) {
        lastConnectError = error;
        await delay(1000);
      }
    }
    if (!cdp) throw new Error(`COI phase could not connect to DevTools: ${lastConnectError?.message ?? "unknown"}`);
    await Promise.all([cdp.send("Page.enable"), cdp.send("Runtime.enable")]);

    const dev = await driveIsolationCheck(cdp, devServer.url, {
      expectServiceWorker: false,
      label: "dev-header mode",
    });
    await cdp.send("Page.navigate", { url: "about:blank" });
    await devServer.server.close();
    devServer = null;

    await buildProduction(buildDir);
    const staticStarted = await startHeaderlessStaticServer(buildDir);
    staticServer = staticStarted.server;
    const production = await driveIsolationCheck(cdp, staticStarted.url, {
      expectServiceWorker: true,
      label: "production coi-serviceworker mode",
    });
    if (production.navigationType !== "reload") {
      throw new Error(`production coi-serviceworker mode: expected the settled page to be the post-install reload: ${JSON.stringify(production)}`);
    }
    process.stdout.write(`COI isolation phase PASS: ${JSON.stringify({ dev, production })}\n`);
    return { dev, production };
  } finally {
    if (cdp) {
      try { await cdp.send("Browser.close"); } catch { /* browser may already be gone */ }
      cdp.close();
    }
    // Browser.close can itself time out on a hung target; never leak the
    // browser (a leaked instance keeps the profile locked and starves retries).
    if (browserProcess && browserProcess.exitCode === null) {
      browserProcess.kill();
    }
    if (browserProcess && browserProcess.exitCode === null) {
      await Promise.race([
        new Promise((resolve) => browserProcess.once("close", resolve)),
        delay(3000),
      ]);
    }
    if (devServer) await devServer.server.close();
    if (staticServer) await new Promise((resolve) => staticServer.close(resolve));
    for (const target of [profile, buildDir]) {
      const resolved = path.resolve(target);
      if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) throw new Error(`refusing to remove non-owned COI-smoke path: ${resolved}`);
      try {
        fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
      } catch (error) {
        if (error?.code !== "EPERM") throw error;
        process.stderr.write(`COI phase cleanup deferred (path still locked): ${resolved}\n`);
      }
    }
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await runCoiPhase();
}
