#!/usr/bin/env node
// Rebuild the browser model library manifest from production GLB files.

import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";

const repoRoot = process.cwd();
const libraryRoot = path.join(repoRoot, "apps", "game", "public", "models", "library");
const manifestPath = path.join(libraryRoot, "manifest.json");

function fail(message) {
  console.error(`build-model-library-manifest: ${message}`);
  process.exit(1);
}

function sortedEntries(dir, options) {
  return fs.readdirSync(dir, options).sort((a, b) => a.name.localeCompare(b.name));
}

function sha1File(filePath) {
  return createHash("sha1").update(fs.readFileSync(filePath)).digest("hex");
}

function readExistingManifest() {
  if (!fs.existsSync(manifestPath)) return new Map();
  const records = JSON.parse(fs.readFileSync(manifestPath, "utf8"));
  if (!Array.isArray(records)) fail(`manifest is not an array: ${path.relative(repoRoot, manifestPath)}`);
  return new Map(records.filter((record) => record && record.id).map((record) => [record.id, record]));
}

function buildRecord(dir, existingRecords) {
  const id = path.basename(dir);
  const files = fs.readdirSync(dir).sort();
  const glbs = files.filter((name) => name.toLowerCase().endsWith(".glb"));
  if (glbs.length !== 1) fail(`${id} must contain exactly one GLB, found ${glbs.length}`);

  const existing = existingRecords.get(id) ?? {};
  const { dae: _oldDae, ...rest } = existing;
  const textures = files.filter((name) => /\.(png|jpg|jpeg|webp)$/i.test(name));
  const runtimeFiles = files.filter((name) => !/\.dae$/i.test(name));
  return {
    ...rest,
    id,
    name: rest.name ?? id,
    glb: glbs[0],
    textures,
    files: runtimeFiles.map((name) => ({
      name,
      bytes: fs.statSync(path.join(dir, name)).size,
      sha1: sha1File(path.join(dir, name)),
    })),
  };
}

if (!fs.existsSync(libraryRoot)) fail(`missing ${path.relative(repoRoot, libraryRoot)}`);

const existingRecords = readExistingManifest();
const modelDirs = sortedEntries(libraryRoot, { withFileTypes: true })
  .filter((entry) => entry.isDirectory())
  .map((entry) => path.join(libraryRoot, entry.name));
const manifest = modelDirs.map((dir) => buildRecord(dir, existingRecords));

fs.writeFileSync(`${manifestPath}.tmp`, `${JSON.stringify(manifest, null, 2)}\n`);
fs.renameSync(`${manifestPath}.tmp`, manifestPath);

console.log(`model library manifest: ${manifest.length} GLB records`);
