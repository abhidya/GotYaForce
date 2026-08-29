#!/usr/bin/env node
// ============================================================================
// COMPOSED-MODULE DISPATCH PILOT smoke phase (docs/composed-pilot.md;
// docs/playable-port-design.md V4 H2/H3, V5 I1/I2, verdict R2/R3).
//
// SELF-CONTAINED on purpose, mirroring scripts/smoke-coi-phase.mjs and
// scripts/smoke-rom-runtime-phase.mjs: it owns its own production build,
// server, browser and CDP session, so it can be appended to
// scripts/smoke-browser-game.mjs as a single opt-in import line without
// touching anything above it.
//
// Unlike the rom-runtime bridge phase — which proves the bridge against its
// own synthetic fixture module — this phase drives the REAL assembly-gate
// artifact inside the REAL game page:
//
//   1. the composed rung-0 module (apps/game/public/rom/composed-rung0.threads
//      .wasm) instantiates in-browser with its declared 2,155,479,040-byte
//      IMPORTED SHARED memory, under cross-origin isolation;
//   2. `__gf_dispatch` is callable through the bridge and returns a CORRECT
//      result — the reentrant invoke's value is computed by the ROM's own
//      compiled code from floats the pilot seeds into GC memory, so a stub
//      cannot fake it;
//   3. a table MISS routes through `__gf_dispatch_miss` into a bridged host
//      adapter, which services it and writes back into the shared arena;
//   4. the per-frame bridged-call ledger records every crossing, at the exact
//      per-frame count the driven window implies.
//
// What it deliberately does NOT assert: any behavioural claim about the five
// rung-0 units (their verification is SUSPENDED across the threads relink),
// and control inversion (run_main_game_loop is not in the window). See
// docs/composed-pilot.md for the gap statement.
//
// Evidence (screenshot + console + ledger/pilot JSON) lands in
// .tmp/composed-pilot-smoke/evidence/.
//
// Runs standalone (node scripts/smoke-composed-pilot-phase.mjs) or via
// runComposedPilotPhase(). Opt in from the browser smoke with
// GF_SMOKE_COMPOSED_PILOT=1.
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
const ownedRoot = path.resolve(root, ".tmp", "composed-pilot-smoke");
const publicBase = "/GotYaForce/game/";

// The pilot is driven in two batches on purpose. The first runs while the game
// is still loading its assets — the render loop is already ticking, so the
// pilot starts immediately. The second is requested AFTER the game reports
// boot-ready and the title screen is up, which is what makes "driven from the
// game's frame loop in a real game context" an assertion rather than a claim:
// those frames provably ran with the game live.
const PILOT_FRAMES_INITIAL = 8;
const PILOT_FRAMES_AFTER_BOOT = 8;
const PILOT_FRAMES = PILOT_FRAMES_INITIAL + PILOT_FRAMES_AFTER_BOOT;
/** Bridged crossings the driven window makes per frame:
 *    zz_01b9b1c_  -> zz_0085e00_ + zz_008aff0_        (2, DIRECT import edge)
 *    zz_01b9b68_  -> zz_006de10_ + zz_008aff0_        (2, DIRECT import edge)
 *    miss(zz_0085e00_)                                (1, MISS edge)
 *  A change here without a matching change in composedPilot.ts is a bug in
 *  one of the two, which is the point of pinning the number. */
const CROSSINGS_PER_FRAME = 5;
/** The composed module's declared shared-memory size (the gate's flat arena). */
const EXPECTED_SHARED_BYTES = 2155479040;
/** -(short)(int)(14.0f * 3.0f): zz_01b9be0_'s early-exit result. */
const EXPECTED_REENTRANT = -42;

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
  let viteEntry;
  try {
    viteEntry = gameRequire.resolve("vite");
  } catch (error) {
    throw new Error("composed-pilot smoke requires Vite from apps/game; run pnpm install", { cause: error });
  }
  const viteEsmEntry = path.join(path.dirname(viteEntry), "dist", "node", "index.js");
  const { build } = await import(pathToFileURL(viteEsmEntry).href);
  await build({ root: gameRoot, build: { outDir: buildDir }, logLevel: "warn" });
}

// COOP/COEP: the composed module needs crossOriginIsolated for its shared
// WebAssembly.Memory and the SharedArrayBuffer control block (design H1).
function startIsolatedStaticServer(dist) {
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
        reject(new Error("could not allocate composed-pilot smoke port"));
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
    if (browserProcess.exitCode !== null) {
      throw new Error(`composed-pilot smoke browser exited before DevTools became ready (${browserProcess.exitCode})`);
    }
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
  throw new Error("timed out waiting for the composed-pilot smoke DevTools endpoint");
}

async function evaluate(cdp, expression) {
  const result = await cdp.send("Runtime.evaluate", { expression, awaitPromise: true, returnByValue: true });
  if (result.exceptionDetails) {
    throw new Error(result.exceptionDetails.exception?.description ?? result.exceptionDetails.text);
  }
  return result.result?.value;
}

async function waitFor(cdp, expression, label, timeoutMs) {
  const deadline = Date.now() + timeoutMs;
  let last;
  while (Date.now() < deadline) {
    last = await evaluate(cdp, expression);
    if (last) return last;
    await delay(150);
  }
  throw new Error(`timed out waiting for ${label}`);
}

export async function runComposedPilotPhase() {
  const browser = findBrowser();
  if (!browser) throw new Error("Chrome/Edge/Chromium not found; set GF_BROWSER_PATH to its executable");
  const WebSocket = gameRequire("ws");

  fs.mkdirSync(ownedRoot, { recursive: true });
  const buildDir = fs.mkdtempSync(path.join(ownedRoot, "dist-"));
  const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
  const evidenceDir = path.join(ownedRoot, "evidence");
  fs.mkdirSync(evidenceDir, { recursive: true });
  const consoleLines = [];
  let staticServer;
  let browserProcess;
  let cdp;
  try {
    await buildProduction(buildDir);
    const started = await startIsolatedStaticServer(buildDir);
    staticServer = started.server;

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
    let lastConnectError = null;
    for (let attempt = 0; attempt < 4 && !cdp; attempt += 1) {
      const debuggerUrl = await waitForDevtools(profile, browserProcess);
      try {
        cdp = await CdpClient.connect(debuggerUrl, WebSocket, 20_000);
      } catch (error) {
        lastConnectError = error;
        await delay(1000);
      }
    }
    if (!cdp) throw new Error(`composed-pilot smoke could not connect to DevTools: ${lastConnectError?.message ?? "unknown"}`);
    await Promise.all([cdp.send("Page.enable"), cdp.send("Runtime.enable")]);
    cdp.on("Runtime.consoleAPICalled", (params) => {
      consoleLines.push(`[${params.type}] ${params.args.map((a) => a.value ?? a.description ?? "").join(" ")}`);
    });
    cdp.on("Runtime.exceptionThrown", (params) => {
      consoleLines.push(`[exception] ${params.exceptionDetails?.exception?.description ?? params.exceptionDetails?.text ?? ""}`);
    });

    await cdp.send("Page.navigate", { url: `${started.url}?composed=${PILOT_FRAMES_INITIAL}` });
    await waitFor(cdp, "window.crossOriginIsolated === true", "cross-origin isolation", 60_000);
    // The pilot handle appears only after the module instantiated, the arena
    // landed and the adapters registered — its presence IS the instantiation
    // proof; `finished` waits for the frame budget to be driven by the render
    // loop. Boot failures are surfaced by the console warning, so a timeout
    // here always comes with the reason in the captured console log.
    await waitFor(cdp, "window.__gf?.composedPilot?.() != null", "composed module boot", 120_000);
    await waitFor(cdp, "window.__gf.composedPilot().finished === true", "first pilot batch", 120_000);

    // Now let the game finish booting, and drive the second batch with the
    // title screen actually up: same render loop, live game.
    await waitFor(
      cdp,
      "document.documentElement.dataset.gfRuntime === 'boot-ready'",
      "game boot-ready (real game context for the second batch)",
      180_000,
    );
    const bootedScreen = await evaluate(cdp, "window.__gf.navigation?.screen ?? null");
    await evaluate(cdp, `window.__gf.composedRun(${PILOT_FRAMES_AFTER_BOOT})`);
    await waitFor(
      cdp,
      `window.__gf.composedPilot().framesDriven === ${PILOT_FRAMES} && window.__gf.composedPilot().finished === true`,
      "second pilot batch (game live)",
      120_000,
    );

    const pilot = await evaluate(cdp, "window.__gf.composedPilot()");
    const ledger = await evaluate(cdp, "window.__gf.bridgeLedger()");
    const adapters = await evaluate(cdp, "window.__gf.bridgeAdapters()");
    const imports = await evaluate(cdp, "window.__gf.bridgeImports()");
    const isolated = await evaluate(cdp, "window.crossOriginIsolated");

    const screenshot = await cdp.send("Page.captureScreenshot", { format: "png" });
    fs.writeFileSync(path.join(evidenceDir, "composed-pilot.png"), Buffer.from(screenshot.data, "base64"));
    fs.writeFileSync(path.join(evidenceDir, "console.log"), consoleLines.join("\n") + "\n");
    fs.writeFileSync(
      path.join(evidenceDir, "composed-pilot-results.json"),
      JSON.stringify({ crossOriginIsolated: isolated, bootedScreen, pilot, ledger, adapters, imports }, null, 2),
    );

    // ---- Proof 0: the second batch really did run in a live game. The game
    //      reported boot-ready and was sitting on its title screen before
    //      composedRun() was called, and the frames after that came from the
    //      same render loop that was drawing it.
    if (bootedScreen !== "title") {
      throw new Error(`game was not on the title screen when the second pilot batch was requested: ${bootedScreen}`);
    }

    // ---- Proof 1: the REAL composed module instantiated, in-browser, with
    //      its declared 2GB imported SHARED memory, under COI.
    if (isolated !== true) throw new Error("composed-pilot smoke ran without crossOriginIsolated — proof invalid");
    if (pilot.module.sharedMemoryBytes !== EXPECTED_SHARED_BYTES) {
      throw new Error(
        `composed module memory ${pilot.module.sharedMemoryBytes} != the gate's ${EXPECTED_SHARED_BYTES}`,
      );
    }
    if (pilot.module.tableSize !== 40 || pilot.module.rung !== 0) {
      throw new Error(`unexpected composed artifact: rung ${pilot.module.rung}, table ${pilot.module.tableSize}`);
    }
    if (!Array.isArray(imports) || imports.length < 30) {
      throw new Error(`declared bridge boundary implausibly small: ${imports?.length} imports`);
    }

    // ---- Proof 2: __gf_dispatch is callable through the bridge with a
    //      CORRECT result, every driven frame.
    if (pilot.framesDriven !== PILOT_FRAMES) {
      throw new Error(`pilot drove ${pilot.framesDriven} frames, expected ${PILOT_FRAMES}`);
    }
    const failedFrames = pilot.frames.filter((f) => !f.pass);
    if (!pilot.pass || failedFrames.length > 0) {
      throw new Error(`composed dispatch pilot FAILED: ${JSON.stringify({ errors: pilot.errors, failedFrames }, null, 2)}`);
    }
    for (const frame of pilot.frames) {
      if (frame.reentrantResult !== EXPECTED_REENTRANT) {
        throw new Error(
          `frame ${frame.frame}: reentrant invoke returned ${frame.reentrantResult}, expected ${EXPECTED_REENTRANT} — ` +
            "the composed module did not compute the value",
        );
      }
    }

    // ---- Proof 3: the MISS handler routed to a bridged adapter. The pilot
    //      dispatches an out-of-window address on purpose; zz_0085e00_ is
    //      absent from the 40-entry table, so its ledger entries can only come
    //      from __gf_dispatch_miss and the direct import trampoline.
    const missSymbol = adapters.find((a) => a.name === "zz_0085e00_");
    if (!missSymbol) throw new Error("no adapter registered for the pilot's miss target zz_0085e00_");
    const missTotal = ledger.totals.byAddr.find((e) => e.gcAddr === "80085e00");
    if (!missTotal || missTotal.count !== PILOT_FRAMES * 2) {
      throw new Error(`miss-routed crossings for 80085e00: ${missTotal?.count ?? 0}, expected ${PILOT_FRAMES * 2}`);
    }
    // ...and the DIRECT-import edge on its own. zz_008aff0_ and zz_006de10_ are
    // never dispatched by the host: their only route into the ledger is a
    // linked function calling them by name through the declared import
    // trampoline, so their counts isolate H2's second edge from the miss path.
    for (const [addr, expected] of [
      ["8008aff0", PILOT_FRAMES * 2],
      ["8006de10", PILOT_FRAMES],
    ]) {
      const entry = ledger.totals.byAddr.find((e) => e.gcAddr === addr);
      if (!entry || entry.count !== expected) {
        throw new Error(`direct-import crossings for ${addr}: ${entry?.count ?? 0}, expected ${expected}`);
      }
    }

    // ---- Proof 4: the ledger recorded the crossings, per frame, exactly.
    const drivenLedgerFrames = ledger.frames.filter((f) => f.frame >= 1 && f.frame <= PILOT_FRAMES);
    if (drivenLedgerFrames.length !== PILOT_FRAMES) {
      throw new Error(`ledger holds ${drivenLedgerFrames.length} driven frames, expected ${PILOT_FRAMES}`);
    }
    for (const frame of drivenLedgerFrames) {
      if (frame.bridgedCallCount !== CROSSINGS_PER_FRAME) {
        throw new Error(
          `ledger frame ${frame.frame}: ${frame.bridgedCallCount} crossings, expected ${CROSSINGS_PER_FRAME}`,
        );
      }
      if (frame.errors.length > 0) {
        throw new Error(`ledger frame ${frame.frame} carries servicing errors: ${JSON.stringify(frame.errors)}`);
      }
    }
    if (ledger.totals.servicingErrors !== 0) {
      throw new Error(`ledger recorded ${ledger.totals.servicingErrors} servicing errors`);
    }

    const summary = {
      gate: pilot.gate,
      artifact: pilot.module.artifact,
      sha256: pilot.module.sha256.slice(0, 16),
      sharedMemoryBytes: pilot.module.sharedMemoryBytes,
      tableSize: pilot.module.tableSize,
      declaredBridgedImports: imports.length,
      adapters: adapters.length,
      framesDriven: pilot.framesDriven,
      framesAfterGameBoot: PILOT_FRAMES_AFTER_BOOT,
      gameScreenAtSecondBatch: bootedScreen,
      crossings: ledger.totals.bridgedCalls,
      servicingErrors: ledger.totals.servicingErrors,
      evidence: path.relative(root, evidenceDir),
    };
    process.stdout.write(`Composed-module dispatch pilot PASS: ${JSON.stringify(summary)}\n`);
    return { pilot, ledger, adapters, imports, evidenceDir };
  } finally {
    if (cdp) {
      try { await cdp.send("Browser.close"); } catch { /* browser may already be gone */ }
      cdp.close();
    }
    if (browserProcess && browserProcess.exitCode === null) browserProcess.kill();
    if (browserProcess && browserProcess.exitCode === null) {
      await Promise.race([
        new Promise((resolve) => browserProcess.once("close", resolve)),
        delay(3000),
      ]);
    }
    if (staticServer) await new Promise((resolve) => staticServer.close(resolve));
    for (const target of [profile, buildDir]) {
      const resolved = path.resolve(target);
      if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) {
        throw new Error(`refusing to remove non-owned composed-pilot smoke path: ${resolved}`);
      }
      try {
        fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
      } catch (error) {
        if (error?.code !== "EPERM") throw error;
        process.stderr.write(`composed-pilot smoke cleanup deferred (path still locked): ${resolved}\n`);
      }
    }
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await runComposedPilotPhase();
}
