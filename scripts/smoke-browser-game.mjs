#!/usr/bin/env node

import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import process from "node:process";
import { spawn } from "node:child_process";
import { fileURLToPath } from "node:url";
import WebSocket from "../apps/game/node_modules/ws/wrapper.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const publicBase = "/GotYaForce/game/";
const ownedRoot = path.resolve(root, ".tmp", "game-browser-smoke");

function tail(text, length = 8000) {
  return text.length <= length ? text : text.slice(-length);
}

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

async function run(command, args, timeoutMs) {
  return await new Promise((resolve, reject) => {
    const child = spawn(command, args, {
      cwd: root,
      windowsHide: true,
      // Windows cannot execute pnpm.cmd directly through CreateProcess.
      shell: process.platform === "win32" && command.toLowerCase().endsWith(".cmd"),
    });
    let stdout = "";
    let stderr = "";
    child.stdout.on("data", (chunk) => { stdout += chunk.toString(); });
    child.stderr.on("data", (chunk) => { stderr += chunk.toString(); });
    const timer = setTimeout(() => {
      child.kill();
      reject(new Error(`${command} timed out after ${timeoutMs}ms\n${tail(stderr)}`));
    }, timeoutMs);
    child.once("error", (error) => {
      clearTimeout(timer);
      reject(error);
    });
    child.once("close", (code) => {
      clearTimeout(timer);
      if (code === 0) resolve({ stdout, stderr });
      else reject(new Error(`${command} exited ${code}\n${tail(stdout)}\n${tail(stderr)}`));
    });
  });
}

async function buildProduction(buildDir) {
  const pnpmScript = process.env.npm_execpath;
  const pnpmIsScript = Boolean(pnpmScript && /\.(?:c|m)?js$/i.test(pnpmScript));
  const pnpm = pnpmIsScript
    ? process.execPath
    : (pnpmScript ?? (process.platform === "win32" ? "pnpm.cmd" : "pnpm"));
  const prefix = pnpmIsScript ? [pnpmScript] : [];
  await run(pnpm, [...prefix, "--filter", "game", "typecheck"], 120_000);
  return await run(
    pnpm,
    [...prefix, "--filter", "game", "exec", "vite", "build", "--outDir", buildDir],
    180_000,
  );
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

function findBrowser() {
  const candidates = process.platform === "win32"
    ? [
      "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe",
      "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe",
      "C:\\Program Files\\Microsoft\\Edge\\Application\\msedge.exe",
    ]
    : ["/usr/bin/google-chrome", "/usr/bin/chromium", "/usr/bin/chromium-browser"];
  return candidates.find((candidate) => fs.existsSync(candidate)) ?? null;
}

async function waitForDevtools(profile, browserProcess, timeoutMs = 20_000) {
  const activePortFile = path.join(profile, "DevToolsActivePort");
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    if (browserProcess.exitCode !== null) throw new Error(`browser exited before DevTools became ready (${browserProcess.exitCode})`);
    if (fs.existsSync(activePortFile)) {
      const [port] = fs.readFileSync(activePortFile, "utf8").trim().split(/\r?\n/);
      if (port) {
        try {
          const response = await fetch(`http://127.0.0.1:${port}/json/list`);
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

class CdpClient {
  constructor(socket) {
    this.socket = socket;
    this.nextId = 1;
    this.pending = new Map();
    this.listeners = new Map();
    socket.on("message", (data) => {
      const message = JSON.parse(data.toString());
      if (message.id) {
        const pending = this.pending.get(message.id);
        if (!pending) return;
        this.pending.delete(message.id);
        if (message.error) pending.reject(new Error(`${pending.method}: ${message.error.message}`));
        else pending.resolve(message.result ?? {});
        return;
      }
      for (const listener of this.listeners.get(message.method) ?? []) listener(message.params ?? {});
    });
  }

  static async connect(url) {
    const socket = new WebSocket(url);
    await new Promise((resolve, reject) => {
      socket.once("open", resolve);
      socket.once("error", reject);
    });
    return new CdpClient(socket);
  }

  on(method, listener) {
    const listeners = this.listeners.get(method) ?? [];
    listeners.push(listener);
    this.listeners.set(method, listeners);
  }

  send(method, params = {}) {
    const id = this.nextId++;
    return new Promise((resolve, reject) => {
      this.pending.set(id, { method, resolve, reject });
      this.socket.send(JSON.stringify({ id, method, params }));
    });
  }

  close() {
    this.socket.terminate();
  }
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

async function drivePlayableRoute(cdp, url) {
  const errors = [];
  const networkErrors = [];
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
  await delay(500);
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
  if (errors.length > 0 || networkErrors.length > 0) {
    throw new Error(`browser emitted runtime errors:\n${[...errors, ...networkErrors.map((error) => `network: ${error}`)].join("\n")}`);
  }
  return battleState;
}

const browser = findBrowser();
if (!browser) throw new Error("Chrome/Edge not found for browser smoke");
fs.mkdirSync(ownedRoot, { recursive: true });
const buildDir = fs.mkdtempSync(path.join(ownedRoot, "build-"));
const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
let server;
let browserProcess;
let cdp;

try {
  const build = await buildProduction(buildDir);
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
  cdp = await CdpClient.connect(debuggerUrl);
  const state = await drivePlayableRoute(cdp, started.url);
  process.stdout.write(
    `Browser smoke PASS: ${path.basename(browser)} production title -> Challenge -> Normal -> 1P -> box -> force -> briefing -> unpaused battle HUD ${JSON.stringify(state)}\n`,
  );
  if (build.stderr.trim()) process.stderr.write(tail(build.stderr));
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
