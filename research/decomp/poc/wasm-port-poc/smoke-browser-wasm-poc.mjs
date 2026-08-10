#!/usr/bin/env node
// smoke-browser-wasm-poc.mjs — POC §5 browser step. New module (no edits to the living
// scripts/smoke-browser-game.mjs), modeled on it: static-serve apps/game/dist, boot the
// REAL game app in headless Chrome, inject poc-run.js which waits for window.__gf,
// loads unit_poc.wasm + arena into the live page, replays the node-verified corpus,
// and publishes the verdict on <html data-gf-wasm-poc>.
//
// Also maps the GH-Pages base prefix (/GotYaForce/game/*) onto dist/* — the current
// dist is built with that base, which is why the stock smoke script cannot boot it.
import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import { spawn } from "node:child_process";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");
const dist = path.join(root, "apps", "game", "dist");

const MIME = {
  ".css": "text/css", ".html": "text/html", ".js": "text/javascript",
  ".json": "application/json", ".png": "image/png", ".svg": "image/svg+xml",
  ".wasm": "application/wasm",
};
const pocHtml = fs.readFileSync(path.join(dist, "index.html"), "utf8")
  .replace("</body>", '<script type="module" src="/__poc/poc-run.js"></script></body>');

const server = http.createServer((req, res) => {
  let p = decodeURIComponent(new URL(req.url ?? "/", "http://x").pathname);
  if (p.startsWith("/GotYaForce/game/")) p = p.slice("/GotYaForce/game".length);
  if (p === "/" || p === "/index.html") {
    res.writeHead(200, { "content-type": "text/html; charset=utf-8" }).end(pocHtml);
    return;
  }
  let file;
  if (p.startsWith("/__poc/")) file = path.resolve(here, p.slice("/__poc/".length));
  else file = path.resolve(dist, p.replace(/^\/+/, ""));
  if ((!file.startsWith(dist + path.sep) && !file.startsWith(here + path.sep)) ||
      !fs.existsSync(file) || fs.statSync(file).isDirectory()) {
    res.writeHead(404).end("nf");
    return;
  }
  res.writeHead(200, { "content-type": MIME[path.extname(file).toLowerCase()] ?? "application/octet-stream" });
  fs.createReadStream(file).pipe(res);
});
const url = await new Promise((resolve) => server.listen(0, "127.0.0.1", () => resolve(`http://127.0.0.1:${server.address().port}/`)));

const browser = [
  "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe",
  "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe",
  "C:\\Program Files\\Microsoft\\Edge\\Application\\msedge.exe",
].find((c) => fs.existsSync(c));
if (!browser) throw new Error("Chrome/Edge not found");
const profile = fs.mkdtempSync(path.join(here, "profile-"));
const dom = await new Promise((resolve, reject) => {
  const child = spawn(browser, [
    "--headless=new", "--disable-gpu", "--disable-dev-shm-usage", "--no-first-run",
    "--no-default-browser-check", `--user-data-dir=${profile}`,
    "--virtual-time-budget=45000", "--timeout=90000", "--dump-dom", url,
  ], { windowsHide: true });
  let out = "", err = "";
  child.stdout.on("data", (d) => { out += d; });
  child.stderr.on("data", (d) => { err += d; });
  const t = setTimeout(() => { child.kill(); reject(new Error("browser timed out\n" + err.slice(-3000))); }, 120000);
  child.once("close", (code) => { clearTimeout(t); code === 0 ? resolve(out) : reject(new Error(`browser exited ${code}\n` + err.slice(-3000))); });
});
server.close();
try { fs.rmSync(profile, { recursive: true, force: true, maxRetries: 5, retryDelay: 200 }); } catch {}

const runtime = /data-gf-runtime="([^"]*)"/.exec(dom)?.[1];
const poc = /data-gf-wasm-poc="([^"]*)"/.exec(dom)?.[1];
console.log(`game runtime : ${runtime ?? "MISSING"}`);
console.log(`wasm poc     : ${poc ?? "MISSING"}`);
if (runtime !== "loaded" || !poc?.startsWith("pass:32/32")) {
  console.error("BROWSER POC FAIL");
  process.exit(1);
}
console.log("BROWSER POC PASS: real app booted (window.__gf live) + wasm unit exact-matched node corpus in-page");
