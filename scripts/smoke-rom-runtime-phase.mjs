#!/usr/bin/env node
// ============================================================================
// ROM-runtime bridge smoke phase (docs/playable-port-design.md V4 H2, V5
// I1/I2, verdict R2/R3). SELF-CONTAINED on purpose, mirroring
// scripts/smoke-coi-phase.mjs: owns its own bundle, server, browser and CDP
// session so it can be appended to scripts/smoke-browser-game.mjs as a single
// opt-in import line without touching anything above it.
//
// What it proves, in a real headless browser behind COOP/COEP isolation:
//   1. correct results through the Atomics RPC bridge — round trip,
//      trace-delta replay, REAL scaffold-backed damage adapters
//      (zz_003d344_/zz_0066298_), and the i64 PPC-r3 high-word rule;
//   2. per-frame bridged-call ledger entries ({gc_addr, count}, exposed at
//      window.__gf.bridgeLedger());
//   3. the I2 reentrant case green — a bridged call whose adapter invokes a
//      linked export through the worker's dispatch loop;
//   4. the nesting-overflow declared servicing error surfaced in the ledger
//      (plus async-servicing, no-adapter and ret_class-mismatch signals).
//
// Evidence (screenshots + console + ledger JSON) lands in
// .tmp/rom-runtime-smoke/evidence/.
//
// Runs standalone (node scripts/smoke-rom-runtime-phase.mjs) or via
// runRomRuntimePhase(). Opt-in from the browser smoke with
// GF_SMOKE_ROM_RUNTIME=1.
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
const pkgRoot = path.join(root, "packages", "rom-runtime");
const gameRequire = createRequire(pathToFileURL(path.join(root, "apps", "game", "package.json")).href);
const pkgRequire = createRequire(pathToFileURL(path.join(pkgRoot, "package.json")).href);
const ownedRoot = path.resolve(root, ".tmp", "rom-runtime-smoke");

function delay(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

async function bundlePage(outDir) {
  const esbuild = await import(pathToFileURL(pkgRequire.resolve("esbuild")).href);
  const common = {
    bundle: true,
    format: "esm",
    platform: "browser",
    target: "es2022",
    sourcemap: false,
    logLevel: "silent",
  };
  await esbuild.build({
    ...common,
    entryPoints: [path.join(pkgRoot, "src", "selftest", "selftestMain.ts")],
    outfile: path.join(outDir, "app.js"),
  });
  await esbuild.build({
    ...common,
    entryPoints: [path.join(pkgRoot, "src", "worker-entry.ts")],
    outfile: path.join(outDir, "rom-runtime-worker.js"),
  });
  fs.copyFileSync(path.join(pkgRoot, "test", "browser", "index.html"), path.join(outDir, "index.html"));
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "bridge-selftest", "bridge_selftest.threads.wasm"),
    path.join(outDir, "bridge_selftest.threads.wasm"),
  );
}

// COOP/COEP-isolated static server: the runtime NEEDS crossOriginIsolated
// (SharedArrayBuffer control block + shared WebAssembly.Memory).
function startIsolatedStaticServer(dir) {
  const resolvedDir = path.resolve(dir);
  const types = {
    ".html": "text/html; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
    ".json": "application/json; charset=utf-8",
    ".wasm": "application/wasm",
  };
  const server = http.createServer((request, response) => {
    const requestPath = decodeURIComponent(new URL(request.url ?? "/", "http://localhost").pathname);
    const relative = requestPath === "/" ? "index.html" : requestPath.slice(1);
    const target = path.resolve(resolvedDir, relative);
    if (target !== resolvedDir && !target.startsWith(`${resolvedDir}${path.sep}`)) {
      response.writeHead(403).end("Forbidden");
      return;
    }
    if (!fs.existsSync(target) || !fs.statSync(target).isFile()) {
      response.writeHead(404).end("Not found");
      return;
    }
    response.writeHead(200, {
      "content-type": types[path.extname(target).toLowerCase()] ?? "application/octet-stream",
      "cross-origin-opener-policy": "same-origin",
      "cross-origin-embedder-policy": "require-corp",
    });
    fs.createReadStream(target).pipe(response);
  });
  return new Promise((resolve, reject) => {
    server.once("error", reject);
    server.listen(0, "127.0.0.1", () => {
      const address = server.address();
      if (!address || typeof address === "string") {
        reject(new Error("could not allocate rom-runtime smoke port"));
        return;
      }
      resolve({ server, url: `http://127.0.0.1:${address.port}/` });
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
      throw new Error(`rom-runtime smoke browser exited before DevTools became ready (${browserProcess.exitCode})`);
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
  throw new Error("timed out waiting for the rom-runtime smoke DevTools endpoint");
}

async function evaluate(cdp, expression) {
  const result = await cdp.send("Runtime.evaluate", { expression, awaitPromise: true, returnByValue: true });
  if (result.exceptionDetails) throw new Error(result.exceptionDetails.exception?.description ?? result.exceptionDetails.text);
  return result.result?.value;
}

async function waitFor(cdp, expression, label, timeoutMs) {
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    if (await evaluate(cdp, expression)) return;
    await delay(100);
  }
  throw new Error(`timed out waiting for ${label}`);
}

export async function runRomRuntimePhase() {
  const browser = findBrowser();
  if (!browser) throw new Error("Chrome/Edge/Chromium not found; set GF_BROWSER_PATH to its executable");
  const gameWebSocket = gameRequire("ws");

  fs.mkdirSync(ownedRoot, { recursive: true });
  const siteDir = fs.mkdtempSync(path.join(ownedRoot, "site-"));
  const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
  const evidenceDir = path.join(ownedRoot, "evidence");
  fs.mkdirSync(evidenceDir, { recursive: true });
  const consoleLines = [];
  let staticServer;
  let browserProcess;
  let cdp;
  try {
    await bundlePage(siteDir);
    const started = await startIsolatedStaticServer(siteDir);
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
        cdp = await CdpClient.connect(debuggerUrl, gameWebSocket, 20_000);
      } catch (error) {
        lastConnectError = error;
        await delay(1000);
      }
    }
    if (!cdp) throw new Error(`rom-runtime smoke could not connect to DevTools: ${lastConnectError?.message ?? "unknown"}`);
    await Promise.all([cdp.send("Page.enable"), cdp.send("Runtime.enable")]);
    cdp.on("Runtime.consoleAPICalled", (params) => {
      consoleLines.push(`[${params.type}] ${params.args.map((a) => a.value ?? a.description ?? "").join(" ")}`);
    });
    cdp.on("Runtime.exceptionThrown", (params) => {
      consoleLines.push(`[exception] ${params.exceptionDetails?.exception?.description ?? params.exceptionDetails?.text ?? ""}`);
    });

    await cdp.send("Page.navigate", { url: started.url });
    await waitFor(cdp, "window.__gfRomRuntimeSelfTest?.done === true", "rom-runtime self-test completion", 60_000);

    const state = await evaluate(cdp, "window.__gfRomRuntimeSelfTest");
    const ledger = await evaluate(cdp, "window.__gf.bridgeLedger()");
    const adapters = await evaluate(cdp, "window.__gf.bridgeAdapters()");

    // Evidence capture: screenshot, console log, ledger + results JSON.
    const screenshot = await cdp.send("Page.captureScreenshot", { format: "png" });
    fs.writeFileSync(path.join(evidenceDir, "selftest.png"), Buffer.from(screenshot.data, "base64"));
    fs.writeFileSync(path.join(evidenceDir, "console.log"), consoleLines.join("\n") + "\n");
    fs.writeFileSync(
      path.join(evidenceDir, "selftest-results.json"),
      JSON.stringify({ state, ledger, adapters }, null, 2),
    );

    // The four required proofs, asserted here as well as in-page.
    if (state.crossOriginIsolated !== true) {
      throw new Error("rom-runtime smoke ran without crossOriginIsolated — proof invalid");
    }
    const failed = (state.results ?? []).filter((r) => !r.pass);
    if (state.pass !== true || failed.length > 0) {
      throw new Error(`rom-runtime self-test FAILED: ${JSON.stringify({ error: state.error, failed }, null, 2)}`);
    }
    const byName = new Map(state.results.map((r) => [r.name, r]));
    const requireCheck = (fragment) => {
      const hit = [...byName.keys()].find((name) => name.includes(fragment));
      if (!hit) throw new Error(`rom-runtime self-test missing required check: ${fragment}`);
    };
    requireCheck("roundtrip");                       // proof 1: correct results
    requireCheck("ledger frame 0 has the roundtrip"); // proof 2: ledger entries
    requireCheck("reentrant(5,7)");                  // proof 3: reentrant green
    requireCheck("nesting overflow surfaced");       // proof 4: overflow loud
    if (!ledger || typeof ledger.totals?.bridgedCalls !== "number" || ledger.totals.bridgedCalls < 10) {
      throw new Error(`rom-runtime ledger implausibly small: ${JSON.stringify(ledger?.totals)}`);
    }

    const summary = {
      checks: state.results.length,
      bridgedCalls: ledger.totals.bridgedCalls,
      servicingErrors: ledger.totals.servicingErrors,
      frames: ledger.frames.length,
      adapters: adapters.length,
      evidence: path.relative(root, evidenceDir),
    };
    process.stdout.write(`ROM-runtime bridge phase PASS: ${JSON.stringify(summary)}\n`);
    return { state, ledger, adapters, evidenceDir };
  } finally {
    if (cdp) {
      try { await cdp.send("Browser.close"); } catch { /* browser may already be gone */ }
      cdp.close();
    }
    if (browserProcess && browserProcess.exitCode === null) {
      browserProcess.kill();
    }
    if (browserProcess && browserProcess.exitCode === null) {
      await Promise.race([
        new Promise((resolve) => browserProcess.once("close", resolve)),
        delay(3000),
      ]);
    }
    if (staticServer) await new Promise((resolve) => staticServer.close(resolve));
    for (const target of [profile, siteDir]) {
      const resolved = path.resolve(target);
      if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) throw new Error(`refusing to remove non-owned rom-runtime smoke path: ${resolved}`);
      try {
        fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
      } catch (error) {
        if (error?.code !== "EPERM") throw error;
        process.stderr.write(`rom-runtime smoke cleanup deferred (path still locked): ${resolved}\n`);
      }
    }
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await runRomRuntimePhase();
}
