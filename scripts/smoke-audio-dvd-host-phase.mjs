#!/usr/bin/env node
// ============================================================================
// Audio/DVD HLE-host smoke phase — the browser standing in for the GameCube's
// DAC and its disc drive (docs/audio-dvd-hle-host.md; design V2 F2 "Stage D —
// SDK seam", V3 non-fatal note 1's claim bar, R3's interrupt delivery).
//
// SELF-CONTAINED on purpose, mirroring scripts/smoke-gx-host-phase.mjs: owns
// its own bundle, server, browser and CDP session so it can be appended to
// scripts/smoke-browser-game.mjs as a single opt-in import line without
// touching anything above it.
//
// What it proves, in a real headless browser behind COOP/COEP isolation:
//   1. a ROM-side wasm module's DVD calls cross the H2 Atomics bridge through
//      signature-accurate import trampolines, resolve a path against a real
//      GameCube FST, and deliver the right BYTES into GC memory;
//   2. an async DVD read's completion callback comes back into the module as
//      an INVOKE-REQUEST at a worker park point (design R3) and the ROM-side
//      callback sees the transferred byte count;
//   3. an UNIMPLEMENTED DVD entry point fails LOUDLY — a declared servicing
//      error naming the symbol — instead of no-opping into a buffer of zeroes
//      that the game would parse as an asset;
//   4. AI/DSP register access reaches the register file and the ROM's own
//      address masking round-trips, and the MusyX mailbox spin loop
//      TERMINATES rather than hanging on a DSP that is not there;
//   5. VERBATIM ROM CODE — AIInitDMA and AIStartDMA, decompiled and MMIO-
//      lowered — moves DSP-ADPCM-decoded PCM out of the arena into a WebAudio
//      AudioBuffer whose samples are the decoder's samples;
//   6. VERBATIM ROM CODE — gcCiGetFileSize @0x802756fc — builds a path with
//      the ROM's own strcat, opens it, and returns the file's real length.
//
// WHAT IT DOES NOT PROVE, and this matters more here than it did for GX:
//   * nothing about whether any of this matches a GameCube. Every adapter is a
//     synthetic stand-in; no read has been compared against a real drive and
//     no sample against console audio;
//   * the disc is one the PAGE BUILT. This repository contains no disc bytes;
//   * THE MIXER IS ABSENT. The PCM in proof 5 was placed by the page, not
//     produced by the game. Gotcha Force mixes in MusyX microcode on the
//     GameCube DSP, which is not PowerPC code and is not translated. A real
//     composed module would DMA silence.
//
// Evidence (page screenshot + console + results JSON) lands in
// .tmp/audio-dvd-host-smoke/evidence/.
//
// Runs standalone (node scripts/smoke-audio-dvd-host-phase.mjs) or via
// runAudioDvdHostPhase(). Opt in from the browser smoke with
// GF_SMOKE_AUDIO_DVD_HOST=1.
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
const ownedRoot = path.resolve(root, ".tmp", "audio-dvd-host-smoke");

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
    entryPoints: [path.join(pkgRoot, "src", "selftest", "hleSelftestMain.ts")],
    outfile: path.join(outDir, "app.js"),
  });
  await esbuild.build({
    ...common,
    entryPoints: [path.join(pkgRoot, "src", "worker-entry.ts")],
    outfile: path.join(outDir, "rom-runtime-worker.js"),
  });
  fs.copyFileSync(path.join(pkgRoot, "test", "browser", "hle-index.html"), path.join(outDir, "index.html"));
  // Leg A: hand-written ROM-SHAPED call sequences.
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "hle-selftest", "hle_selftest.threads.wasm"),
    path.join(outDir, "hle_selftest.threads.wasm"),
  );
  // Leg B: the VERBATIM ROM decompilation with its AI/DSP MMIO lowered
  // (test/fixtures/hle-rom-unit/build.sh lists every rewrite applied).
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "hle-rom-unit", "hle_rom_unit.threads.wasm"),
    path.join(outDir, "hle_rom_unit.threads.wasm"),
  );
  // The DSP-ADPCM cross-check vector, produced by the PYTHON decoder in
  // scripts/export-combat-se.py (see test/fixtures/adpcm/gen-vector.py). The
  // page decodes the same inputs with the TypeScript port and compares.
  fs.copyFileSync(
    path.join(pkgRoot, "test", "fixtures", "adpcm", "adpcm-vector.json"),
    path.join(outDir, "adpcm-vector.json"),
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
        reject(new Error("could not allocate audio/DVD smoke port"));
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
      process.env["ProgramFiles(x86)"] &&
        path.join(process.env["ProgramFiles(x86)"], "Google", "Chrome", "Application", "chrome.exe"),
      process.env["ProgramFiles(x86)"] &&
        path.join(process.env["ProgramFiles(x86)"], "Microsoft", "Edge", "Application", "msedge.exe"),
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
  browserProcess.once("error", (error) => {
    spawnError = error;
  });
  while (Date.now() < deadline) {
    if (spawnError) throw spawnError;
    if (browserProcess.exitCode !== null) {
      throw new Error(`audio/DVD smoke browser exited before DevTools became ready (${browserProcess.exitCode})`);
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
  throw new Error("timed out waiting for the audio/DVD smoke DevTools endpoint");
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
  while (Date.now() < deadline) {
    if (await evaluate(cdp, expression)) return;
    await delay(100);
  }
  throw new Error(`timed out waiting for ${label}`);
}

export async function runAudioDvdHostPhase() {
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

    browserProcess = spawn(
      browser,
      [
        "--headless=new",
        "--remote-debugging-port=0",
        "--disable-dev-shm-usage",
        // An AudioContext is suspended until a gesture by default, and headless
        // has no gestures. The proof asserts on the AudioBuffer the backend
        // hands the device, so the context must at least be constructible and
        // runnable.
        "--autoplay-policy=no-user-gesture-required",
        "--no-first-run",
        "--no-default-browser-check",
        "--window-size=1280,1200",
        `--user-data-dir=${profile}`,
        "about:blank",
      ],
      { cwd: root, windowsHide: true, stdio: "ignore" },
    );
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
    if (!cdp) {
      throw new Error(`audio/DVD smoke could not connect to DevTools: ${lastConnectError?.message ?? "unknown"}`);
    }
    await Promise.all([cdp.send("Page.enable"), cdp.send("Runtime.enable")]);
    cdp.on("Runtime.consoleAPICalled", (params) => {
      consoleLines.push(`[${params.type}] ${params.args.map((a) => a.value ?? a.description ?? "").join(" ")}`);
    });
    cdp.on("Runtime.exceptionThrown", (params) => {
      consoleLines.push(
        `[exception] ${params.exceptionDetails?.exception?.description ?? params.exceptionDetails?.text ?? ""}`,
      );
    });

    await cdp.send("Page.navigate", { url: started.url });
    await waitFor(cdp, "window.__gfHleSelfTest?.done === true", "audio/DVD self-test completion", 120_000);

    const state = await evaluate(cdp, "window.__gfHleSelfTest");

    const screenshot = await cdp.send("Page.captureScreenshot", { format: "png", captureBeyondViewport: true });
    fs.writeFileSync(path.join(evidenceDir, "hle-selftest.png"), Buffer.from(screenshot.data, "base64"));
    fs.writeFileSync(path.join(evidenceDir, "console.log"), `${consoleLines.join("\n")}\n`);
    fs.writeFileSync(path.join(evidenceDir, "hle-selftest-results.json"), JSON.stringify({ state }, null, 2));

    // --- assertions -----------------------------------------------------------
    if (state.crossOriginIsolated !== true) {
      throw new Error("audio/DVD smoke ran without crossOriginIsolated — proof invalid");
    }
    const failed = (state.results ?? []).filter((r) => !r.pass);
    if (state.pass !== true || failed.length > 0) {
      throw new Error(`audio/DVD host self-test FAILED: ${JSON.stringify({ error: state.error, failed }, null, 2)}`);
    }
    const names = (state.results ?? []).map((r) => r.name);
    const requireCheck = (fragment) => {
      if (!names.some((name) => name.includes(fragment))) {
        throw new Error(`audio/DVD host self-test missing required check: ${fragment}`);
      }
    };
    // The ADPCM port is checked against the PYTHON decoder that produced the
    // shipped combat-SE OGGs — an independent implementation, not itself.
    requireCheck("samples match the Python reference");
    requireCheck("the bytes in GC memory are the disc's bytes"); // proof 1
    requireCheck("DVDOpen wrote the file's real length"); // proof 1
    requireCheck("the ROM-side callback ran exactly once"); // proof 2
    requireCheck("it was handed the transferred byte count"); // proof 2
    requireCheck("unimplemented DVDInquiryAsync rejects with ADAPTER_THREW"); // proof 3
    requireCheck("the unimplemented hit is named"); // proof 3
    requireCheck("AIVR bits 0-7 decoded as the LEFT volume"); // proof 4
    requireCheck("the DSP mailbox spin loop terminated"); // proof 4
    requireCheck("REAL ROM CODE started exactly one DMA transfer"); // proof 5
    requireCheck("the DMA reconstructed the address the ROM gave it"); // proof 5
    requireCheck("its first left sample is the decoded PCM, normalized"); // proof 5
    requireCheck("REAL ROM CODE returned the file's real length"); // proof 6

    // The ROM-code leg is the whole point of this phase. A green run that
    // quietly skipped it is exactly the false progress the phase exists to
    // prevent.
    const legB = state.report?.legB;
    if (!legB || !String(legB.source ?? "").startsWith("VERBATIM ROM decompilation")) {
      throw new Error(`the verbatim-ROM leg did not run: ${JSON.stringify(legB?.source ?? null)}`);
    }
    if (legB.audio?.dma?.blocks !== 1) {
      throw new Error(`the ROM leg did not drive exactly one AI DMA transfer: ${JSON.stringify(legB.audio?.dma)}`);
    }
    if (legB.audio?.dspMicrocodeAbsent !== true) {
      throw new Error("the audio host stopped reporting that the DSP microcode is absent — that gap has not closed");
    }

    for (const [legName, leg] of Object.entries(state.report ?? {})) {
      if (!leg || typeof leg !== "object" || !leg.audio) continue;
      if (leg.audio.verified !== false || !String(leg.audio.behaviouralClaim ?? "").startsWith("NONE")) {
        throw new Error(`${legName}: the audio host failed to state that it carries no behavioural claim`);
      }
      if (leg.dvd.verified !== false || !String(leg.dvd.behaviouralClaim ?? "").startsWith("NONE")) {
        throw new Error(`${legName}: the DVD host failed to state that it carries no behavioural claim`);
      }
    }
    if (state.verified !== false) {
      throw new Error("the audio/DVD self-test payload failed to state that it carries no behavioural claim");
    }

    const ledgerA = state.report?.legA?.ledger;
    if (!ledgerA || typeof ledgerA.totals?.bridgedCalls !== "number" || ledgerA.totals.bridgedCalls < 20) {
      throw new Error(`audio/DVD bridged-call ledger implausibly small: ${JSON.stringify(ledgerA?.totals)}`);
    }

    const dvdCoverage = state.report?.legA?.dvd?.coverage;
    const audioCoverage = state.report?.legA?.audio?.coverage;
    if (!dvdCoverage || typeof dvdCoverage.translated?.callSitePct !== "number") {
      throw new Error("the DVD host did not report tiered coverage of the measured inventory");
    }
    if (!audioCoverage || typeof audioCoverage.bridged?.totalCallSites !== "number") {
      throw new Error("the audio host did not report its bridged/in-window seam split");
    }

    const summary = {
      checks: state.results.length,
      bridgedCalls: ledgerA.totals.bridgedCalls,
      dvd: {
        reads: state.report?.legA?.dvd?.reads?.length,
        unimplementedHits: state.report?.legA?.dvd?.unimplementedHits,
        coverage:
          `${dvdCoverage.translated.implementedSymbols}/${dvdCoverage.translated.totalSymbols} entry points translated, ` +
          `${dvdCoverage.translated.callSitePct}% of ROM call sites (+ latched/nop: ` +
          `${dvdCoverage.all.callSitePct}%)`,
      },
      audio: {
        bridgedCoverage:
          `${audioCoverage.bridged.implementedSymbols}/${audioCoverage.bridged.totalSymbols} bridged entry points, ` +
          `${audioCoverage.bridged.coveredCallSites}/${audioCoverage.bridged.totalCallSites} bridged call sites`,
        inWindowCallSites: audioCoverage.inWindow.callSites,
        dspMicrocodeAbsent: true,
      },
      verbatimRomLeg: {
        dmaBlocks: legB.audio?.dma?.blocks,
        frames: legB.audioBackend?.frames,
        sampleRate: legB.audio?.dma?.sampleRate,
        dvdReads: legB.dvd?.reads?.length ?? 0,
      },
      verified: false,
      evidence: path.relative(root, evidenceDir),
    };
    process.stdout.write(
      `Audio/DVD HLE-host phase PASS (seam only, NO behavioural claim, mixer ABSENT): ${JSON.stringify(summary)}\n`,
    );
    return { state, evidenceDir };
  } finally {
    if (cdp) {
      try {
        await cdp.send("Browser.close");
      } catch {
        /* browser may already be gone */
      }
      cdp.close();
    }
    if (browserProcess && browserProcess.exitCode === null) {
      browserProcess.kill();
    }
    if (browserProcess && browserProcess.exitCode === null) {
      await Promise.race([new Promise((resolve) => browserProcess.once("close", resolve)), delay(3000)]);
    }
    if (staticServer) await new Promise((resolve) => staticServer.close(resolve));
    for (const target of [profile, siteDir]) {
      const resolved = path.resolve(target);
      if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) {
        throw new Error(`refusing to remove non-owned audio/DVD smoke path: ${resolved}`);
      }
      try {
        fs.rmSync(resolved, { recursive: true, force: true, maxRetries: 10, retryDelay: 250 });
      } catch (error) {
        if (error?.code !== "EPERM") throw error;
        process.stderr.write(`audio/DVD smoke cleanup deferred (path still locked): ${resolved}\n`);
      }
    }
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await runAudioDvdHostPhase();
}
