#!/usr/bin/env node

import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import process from "node:process";
import { spawn } from "node:child_process";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

function tail(text, length = 5000) {
  return text.length <= length ? text : text.slice(-length);
}

function contentType(file) {
  return {
    ".css": "text/css; charset=utf-8",
    ".html": "text/html; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
    ".json": "application/json; charset=utf-8",
    ".png": "image/png",
    ".svg": "image/svg+xml",
    ".wasm": "application/wasm",
  }[path.extname(file).toLowerCase()] ?? "application/octet-stream";
}

function startStaticServer(dist) {
  const resolvedDist = path.resolve(dist);
  const server = http.createServer((request, response) => {
    const requestPath = decodeURIComponent(new URL(request.url ?? "/", "http://localhost").pathname);
    const relative = requestPath === "/" ? "index.html" : requestPath.replace(/^\/+/, "");
    let target = path.resolve(resolvedDist, relative);
    if (target !== resolvedDist && !target.startsWith(`${resolvedDist}${path.sep}`)) {
      response.writeHead(403).end("Forbidden");
      return;
    }
    if (!fs.existsSync(target) || fs.statSync(target).isDirectory()) {
      target = path.join(resolvedDist, "index.html");
    }
    response.writeHead(200, { "content-type": contentType(target) });
    fs.createReadStream(target).pipe(response);
  });
  return new Promise((resolve, reject) => {
    server.once("error", reject);
    server.listen(0, "127.0.0.1", () => {
      const address = server.address();
      if (!address || typeof address === "string") {
        reject(new Error("could not allocate browser-smoke port"));
        return;
      }
      resolve({ server, url: `http://127.0.0.1:${address.port}/` });
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

async function dumpBrowserDom(browser, url, profileDir) {
  return await new Promise((resolve, reject) => {
    const child = spawn(browser, [
      "--headless=new",
      "--disable-gpu",
      "--disable-dev-shm-usage",
      "--no-first-run",
      "--no-default-browser-check",
      `--user-data-dir=${profileDir}`,
      "--virtual-time-budget=10000",
      "--dump-dom",
      url,
    ], { cwd: root, windowsHide: true });
    let stdout = "";
    let stderr = "";
    child.stdout.on("data", (chunk) => { stdout += chunk.toString(); });
    child.stderr.on("data", (chunk) => { stderr += chunk.toString(); });
    const timer = setTimeout(() => {
      child.kill();
      reject(new Error(`headless browser timed out\n${tail(stderr)}`));
    }, 45000);
    child.once("error", (error) => {
      clearTimeout(timer);
      reject(error);
    });
    child.once("close", (code) => {
      clearTimeout(timer);
      if (code !== 0) reject(new Error(`headless browser exited ${code}\n${tail(stderr)}`));
      else resolve({ stdout, stderr });
    });
  });
}

const browser = findBrowser();
if (!browser) throw new Error("Chrome/Edge not found for browser smoke");
const { server, url } = await startStaticServer(path.join(root, "apps", "game", "dist"));
const ownedRoot = path.resolve(root, ".tmp", "finish-game-port-browser");
fs.mkdirSync(ownedRoot, { recursive: true });
const profile = fs.mkdtempSync(path.join(ownedRoot, "profile-"));
try {
  const result = await dumpBrowserDom(browser, url, profile);
  if (!/data-gf-runtime="loaded"/.test(result.stdout)) {
    throw new Error(`browser runtime readiness signal missing\n${tail(result.stdout)}`);
  }
  process.stdout.write(`Browser smoke PASS: ${path.basename(browser)} data-gf-runtime=loaded\n`);
} finally {
  await new Promise((resolve) => server.close(resolve));
  const resolved = path.resolve(profile);
  if (!resolved.startsWith(`${ownedRoot}${path.sep}`)) {
    throw new Error(`refusing to remove non-owned browser profile: ${resolved}`);
  }
  fs.rmSync(resolved, { recursive: true, force: true });
}
