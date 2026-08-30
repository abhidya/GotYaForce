#!/usr/bin/env node
// ============================================================================
// GX HLE-host smoke phase — the browser standing in for the GameCube's
// graphics hardware (docs/gx-hle-host.md; design V2 F2 "Stage D — SDK seam"
// and V3 non-fatal note 1's claim bar).
//
// SELF-CONTAINED on purpose, mirroring scripts/smoke-rom-runtime-phase.mjs:
// owns its own bundle, server, browser and CDP session so it can be appended
// to scripts/smoke-browser-game.mjs as a single opt-in import line without
// touching anything above it.
//
// What it proves, in a real headless browser behind COOP/COEP isolation:
//   1. a ROM-side wasm module's GX calls cross the H2 Atomics bridge through
//      signature-accurate import trampolines and land in the GX adapters,
//      recorded in the bridged-call ledger;
//   2. the write-gather-pipe decoder assembles the ROM's OWN vertex layouts —
//      S16 XY + RGBA8 direct, F32 XYZ + RGBA8 direct, and INDEX8 fetched
//      through GXSetArray — into the right primitives;
//   3. those primitives RASTERIZE: the WebGL2 framebuffer holds the expected
//      colours at the expected pixels, read back with readPixels in-page and
//      captured as a screenshot here;
//   4. an UNIMPLEMENTED GX entry point fails LOUDLY — a declared servicing
//      error in the ledger naming the symbol — instead of no-opping into a
//      frame that renders and is wrong.
//
// WHAT IT DOES NOT PROVE. Nothing about whether these frames match the
// GameCube. Every GX adapter is a synthetic stand-in, the fixture is not
// ported ROM code, and no output has ever been compared against a captured
// frame. This phase asserts that the SEAM works; the claim ceiling for the
// path even once verified is "framebuffer-equivalent, never pixel-identical".
//
// Evidence (screenshots + console + coverage JSON) lands in
// .tmp/gx-host-smoke/evidence/.
//
// Runs standalone (node scripts/smoke-gx-host-phase.mjs) or via runGxHostPhase().
// Opt in from the browser smoke with GF_SMOKE_GX_HOST=1.
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
const ownedRoot = path.resolve(root, ".tmp", "gx-host-smoke");

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
    entryPoints: [path.join(pkgRoot, "src", "gx", "selftest", "gxSelftestMain.ts")],
    outfile: path.join(outDir, "app.js"),
  });
  await esbuild.build({
    ...common,
    entryPoints: [path.join(pkgRoot, "src", "worker-entry.ts")],
    outfile: path.join(outDir, "rom-runtime-worker.js"),
  });
  fs.copyFileSync(path.join(pkgRoot, "test", "browser", "gx-index.html"), path.join(outDir, "index.html"));
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "gx-selftest", "gx_selftest.threads.wasm"),
    path.join(outDir, "gx_selftest.threads.wasm"),
  );
  // The gate-lowered REAL ROM unit (test/fixtures/gx-rom-unit/build.sh): the
  // assembly gate's own output for zz_0027c34_, not a hand-written fixture.
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "gx-rom-unit", "gx_rom_unit.threads.wasm"),
    path.join(outDir, "gx_rom_unit.threads.wasm"),
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
        reject(new Error("could not allocate GX smoke port"));
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
      throw new Error(`GX smoke browser exited before DevTools became ready (${browserProcess.exitCode})`);
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
  throw new Error("timed out waiting for the GX smoke DevTools endpoint");
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

export async function runGxHostPhase() {
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
      // The GX host needs a real WebGL2 context; SwiftShader supplies one in
      // headless, which is why this phase can assert on actual pixels.
      "--enable-unsafe-swiftshader",
      "--use-angle=swiftshader",
      "--no-first-run",
      "--no-default-browser-check",
      "--window-size=1280,1200",
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
    if (!cdp) throw new Error(`GX smoke could not connect to DevTools: ${lastConnectError?.message ?? "unknown"}`);
    await Promise.all([cdp.send("Page.enable"), cdp.send("Runtime.enable")]);
    cdp.on("Runtime.consoleAPICalled", (params) => {
      consoleLines.push(`[${params.type}] ${params.args.map((a) => a.value ?? a.description ?? "").join(" ")}`);
    });
    cdp.on("Runtime.exceptionThrown", (params) => {
      consoleLines.push(`[exception] ${params.exceptionDetails?.exception?.description ?? params.exceptionDetails?.text ?? ""}`);
    });

    await cdp.send("Page.navigate", { url: started.url });
    await waitFor(cdp, "window.__gfGxSelfTest?.done === true", "GX self-test completion", 90_000);

    const state = await evaluate(cdp, "window.__gfGxSelfTest");
    const ledger = await evaluate(cdp, "window.__gf.bridgeLedger()");
    const adapterRoster = await evaluate(cdp, "window.__gf.bridgeAdapters()");

    // Evidence capture: the framebuffer itself, the page, console, and the
    // machine-readable report.
    const canvasPng = await evaluate(
      cdp,
      "document.getElementById('gx-canvas').toDataURL('image/png').split(',')[1]",
    );
    if (typeof canvasPng === "string" && canvasPng.length > 0) {
      fs.writeFileSync(path.join(evidenceDir, "gx-framebuffer.png"), Buffer.from(canvasPng, "base64"));
    }
    // Two framebuffers, because the two legs draw over the same canvas: the
    // fixture frame (hand-written ROM-shaped call sequences) and the frame the
    // GATE-LOWERED ROM unit produced.
    for (const [field, file] of [
      ["fixtureFramebufferPng", "gx-framebuffer-fixture.png"],
      ["romFramebufferPng", "gx-framebuffer-rom-unit.png"],
    ]) {
      const dataUrl = state?.[field];
      if (typeof dataUrl === "string" && dataUrl.includes(",")) {
        fs.writeFileSync(path.join(evidenceDir, file), Buffer.from(dataUrl.split(",")[1], "base64"));
      }
    }
    const screenshot = await cdp.send("Page.captureScreenshot", { format: "png", captureBeyondViewport: true });
    fs.writeFileSync(path.join(evidenceDir, "gx-selftest.png"), Buffer.from(screenshot.data, "base64"));
    fs.writeFileSync(path.join(evidenceDir, "console.log"), consoleLines.join("\n") + "\n");
    fs.writeFileSync(
      path.join(evidenceDir, "gx-selftest-results.json"),
      JSON.stringify({ state, ledger, adapters: adapterRoster }, null, 2),
    );

    // --- assertions -----------------------------------------------------------
    if (state.crossOriginIsolated !== true) {
      throw new Error("GX smoke ran without crossOriginIsolated — proof invalid");
    }
    const failed = (state.results ?? []).filter((r) => !r.pass);
    if (state.pass !== true || failed.length > 0) {
      throw new Error(`GX host self-test FAILED: ${JSON.stringify({ error: state.error, failed }, null, 2)}`);
    }
    const names = (state.results ?? []).map((r) => r.name);
    const requireCheck = (fragment) => {
      if (!names.some((name) => name.includes(fragment))) {
        throw new Error(`GX host self-test missing required check: ${fragment}`);
      }
    };
    requireCheck("three primitives assembled");                       // proof 2
    requireCheck("primitive 2 resolved its INDEX8 positions");        // proof 2
    requireCheck("centre pixel G == strip green G");                  // proof 3
    requireCheck("corner pixel B == fullscreen quad B");              // proof 3
    requireCheck("unimplemented GXSetFog rejects with ADAPTER_THREW"); // proof 4
    requireCheck("the loud failure is in the bridged-call ledger");   // proof 4
    requireCheck("TEV konst-only stage: R is GX_KCOLOR0");            // proof 5 (TEV combiner)
    requireCheck("stage 1 read it back as GX_CC_C0");                 // proof 5 (TEV registers)
    requireCheck("GXSetAlphaCompare discarded the failing fragment"); // proof 5 (alpha test)
    requireCheck("GX_TF_RGBA8 texel R decoded out of the arena");     // proof 6 (texture sampling)
    requireCheck("lit channel R == the light's own R");               // proof 7 (lighting)
    requireCheck("the ROM's 4-stage program set the stage count");    // proof 8 (real ROM TEV program)
    // proof 9 — the browser leg finally driving GATE-LOWERED REAL ROM CODE
    // rather than a purpose-built fixture.
    requireCheck("the gate-lowered ROM unit submitted exactly one primitive");
    requireCheck("the ROM's own RGBA8 colour word reached the framebuffer path");
    requireCheck("ROM unit framebuffer centre R");

    // The gate-lowered ROM unit is the whole point of the browser leg now: a
    // green run that quietly skipped it would be exactly the kind of false
    // progress this phase exists to prevent.
    const romUnit = state.report?.romUnit;
    if (!romUnit || romUnit.primitives !== 1 || romUnit.droppedFifoBytes !== 0) {
      throw new Error(`the gate-lowered ROM unit leg did not run cleanly: ${JSON.stringify(romUnit)}`);
    }
    if (romUnit.verified !== false || !String(romUnit.behaviouralClaim ?? "").startsWith("NONE")) {
      throw new Error("the gate-lowered ROM unit report failed to state that it carries no behavioural claim");
    }

    if (!ledger || typeof ledger.totals?.bridgedCalls !== "number" || ledger.totals.bridgedCalls < 60) {
      throw new Error(`GX bridged-call ledger implausibly small: ${JSON.stringify(ledger?.totals)}`);
    }

    // The whole GX adapter set is synthetic BY DESIGN. Assert that, so a
    // future adapter cannot quietly relabel itself "verified" and inherit
    // credibility this path has not earned.
    const verified = (adapterRoster.adapters ?? []).filter((a) => a.evidenceClass === "verified");
    if (verified.length > 0) {
      throw new Error(
        `a GX adapter claims evidenceClass "verified" but the GX path has no trace verification behind it: ` +
          JSON.stringify(verified.map((a) => a.name)),
      );
    }
    if (adapterRoster.behaviouralClaim?.startsWith("NONE") !== true) {
      throw new Error("the GX host roster failed to state that it carries no behavioural claim");
    }
    if (state.verified !== false || !String(state.behaviouralClaim ?? "").startsWith("NONE")) {
      throw new Error("the GX self-test payload failed to state that it carries no behavioural claim");
    }

    const coverage = state.report?.coverage;
    if (!coverage || typeof coverage.translated?.callSitePct !== "number") {
      throw new Error("the GX host did not report tiered coverage of the measured inventory");
    }

    const summary = {
      checks: state.results.length,
      bridgedCalls: ledger.totals.bridgedCalls,
      primitives: state.report?.fifo?.primitives,
      droppedFifoBytes: state.report?.fifo?.droppedBytes,
      unimplementedHits: state.report?.unimplementedHits,
      gateLoweredRomUnit: {
        primitives: state.report?.romUnit?.primitives,
        droppedFifoBytes: state.report?.romUnit?.droppedFifoBytes,
        gxCalls: Array.isArray(state.report?.romUnit?.calls) ? state.report.romUnit.calls.length : null,
      },
      coverage: {
        translated: `${coverage.translated.implementedSymbols}/${coverage.translated.totalSymbols} entry points, ` +
          `${coverage.translated.callSitePct}% of ROM call sites`,
        translatedAndLatched: `${coverage.translatedAndLatched.implementedSymbols}/${coverage.translatedAndLatched.totalSymbols} entry points, ` +
          `${coverage.translatedAndLatched.callSitePct}% of ROM call sites`,
      },
      verified: false,
      evidence: path.relative(root, evidenceDir),
    };
    process.stdout.write(`GX HLE-host phase PASS (seam only, NO behavioural claim): ${JSON.stringify(summary)}\n`);
    return { state, ledger, adapters: adapterRoster.adapters, evidenceDir };
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
      if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) throw new Error(`refusing to remove non-owned GX smoke path: ${resolved}`);
      try {
        fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
      } catch (error) {
        if (error?.code !== "EPERM") throw error;
        process.stderr.write(`GX smoke cleanup deferred (path still locked): ${resolved}\n`);
      }
    }
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await runGxHostPhase();
}
