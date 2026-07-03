#!/usr/bin/env node
// Copy exported model assets into the browser public folder and rebuild the library manifest.

import { createHash } from "crypto";
import fs from "fs";
import path from "path";
import { spawnSync } from "node:child_process";

const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);
const [region] = process.argv.slice(2);

function usage() {
  console.error("usage: node scripts/sync-exported-assets.mjs <GG4E|GG4J|GG4P>");
  process.exit(1);
}

function fail(message) {
  console.error(`error: ${message}`);
  process.exit(1);
}

function sortedEntries(dir, options) {
  return fs.readdirSync(dir, options).sort((a, b) => a.name.localeCompare(b.name));
}

function copyDirContents(source, dest) {
  fs.rmSync(dest, { recursive: true, force: true });
  fs.mkdirSync(dest, { recursive: true });

  let files = 0;
  for (const entry of sortedEntries(source, { withFileTypes: true })) {
    const from = path.join(source, entry.name);
    const to = path.join(dest, entry.name);
    if (entry.isDirectory()) {
      files += copyDirContents(from, to);
    } else if (entry.isFile()) {
      fs.copyFileSync(from, to);
      files += 1;
    }
  }
  return files;
}

function sha1File(filePath) {
  return createHash("sha1").update(fs.readFileSync(filePath)).digest("hex");
}

function readExistingManifest(manifestPath) {
  if (!fs.existsSync(manifestPath)) return new Map();
  const records = JSON.parse(fs.readFileSync(manifestPath, "utf8"));
  if (!Array.isArray(records)) fail(`manifest is not an array: ${manifestPath}`);
  return new Map(records.filter((record) => record && record.id).map((record) => [record.id, record]));
}

function buildRecord(dir, existingRecords) {
  const id = path.basename(dir);
  const files = fs.readdirSync(dir).sort();
  const glb = files.find((name) => name.toLowerCase().endsWith(".glb"));
  if (!glb) fail(`missing .glb in copied model directory: ${dir}`);

  const textures = files.filter((name) => /\.(png|jpg|jpeg|webp)$/i.test(name));
  const runtimeFiles = files.filter((name) => !/\.dae$/i.test(name));
  const existing = existingRecords.get(id) ?? {};
  return {
    ...existing,
    id,
    name: existing.name ?? id,
    glb,
    textures,
    files: runtimeFiles.map((name) => ({
      name,
      bytes: fs.statSync(path.join(dir, name)).size,
      sha1: sha1File(path.join(dir, name)),
    })),
  };
}

function firstExistingDir(candidates) {
  return candidates.find((candidate) => fs.existsSync(candidate) && fs.statSync(candidate).isDirectory());
}

function convertRuntimeModels(root) {
  const relRoot = path.relative(repoRoot, root);
  const result = spawnSync(process.execPath, ["scripts/convert-runtime-models-to-glb.mjs", relRoot], {
    cwd: repoRoot,
    stdio: "inherit",
  });
  if (result.status !== 0) fail(`GLB conversion failed for ${relRoot}`);
}

function removePublicSourceModels(root) {
  const resolvedRoot = path.resolve(root);
  const resolvedPublicModels = path.resolve(repoRoot, "apps", "game", "public", "models");
  if (resolvedRoot !== resolvedPublicModels && !resolvedRoot.startsWith(`${resolvedPublicModels}${path.sep}`)) {
    fail(`refusing to remove source models outside ${path.relative(repoRoot, resolvedPublicModels)}: ${resolvedRoot}`);
  }
  for (const entry of sortedEntries(resolvedRoot, { withFileTypes: true })) {
    const file = path.join(resolvedRoot, entry.name);
    if (entry.isDirectory()) removePublicSourceModels(file);
    else if (entry.isFile() && entry.name.toLowerCase().endsWith(".dae")) fs.rmSync(file);
  }
}

if (!region) usage();
if (!REGIONS.has(region)) fail(`unsupported region "${region}"`);

const repoRoot = process.cwd();
const sourceRoot = path.join(repoRoot, "user-data", region, "models-export");
const libraryRoot = path.join(repoRoot, "apps", "game", "public", "models", "library");
const manifestPath = path.join(libraryRoot, "manifest.json");

if (!fs.existsSync(sourceRoot)) fail(`models export does not exist: ${path.relative(repoRoot, sourceRoot)}`);
fs.mkdirSync(libraryRoot, { recursive: true });

const existingRecords = readExistingManifest(manifestPath);
let copiedDirs = 0;
let copiedFiles = 0;

for (const entry of sortedEntries(sourceRoot, { withFileTypes: true })) {
  if (!entry.isDirectory()) continue;
  copiedFiles += copyDirContents(path.join(sourceRoot, entry.name), path.join(libraryRoot, entry.name));
  copiedDirs += 1;
}

const pl0615Source = firstExistingDir([
  path.join(repoRoot, "user-data", region, "pl0615"),
  path.join(repoRoot, "user-data", region, "anim-test", "pl0615"),
  path.join(repoRoot, "apps", "slice", "models", "pl0615"),
]);

let animationSummary = "not found";
if (pl0615Source) {
  const animationFiles = fs
    .readdirSync(pl0615Source)
    .filter((name) => /^anim_.*\.json$/i.test(name) || /^model_00\.(dae|glb)$/i.test(name) || /\.(png|jpg|jpeg|webp)$/i.test(name))
    .sort();
  if (animationFiles.length > 0) {
    const animationDest = path.join(repoRoot, "apps", "game", "public", "models", "pl0615");
    fs.mkdirSync(animationDest, { recursive: true });
    for (const file of animationFiles) {
      fs.copyFileSync(path.join(pl0615Source, file), path.join(animationDest, file));
    }
    animationSummary = `${animationFiles.length} files from ${path.relative(repoRoot, pl0615Source)}`;
  }
}

convertRuntimeModels(path.join(repoRoot, "apps", "game", "public", "models"));
removePublicSourceModels(path.join(repoRoot, "apps", "game", "public", "models"));

const modelDirs = sortedEntries(libraryRoot, { withFileTypes: true })
  .filter((entry) => entry.isDirectory())
  .map((entry) => path.join(libraryRoot, entry.name));

const manifest = modelDirs.map((dir) => buildRecord(dir, existingRecords));
fs.writeFileSync(`${manifestPath}.tmp`, `${JSON.stringify(manifest, null, 2)}\n`);
fs.renameSync(`${manifestPath}.tmp`, manifestPath);

console.log(`region: ${region}`);
console.log(`models: copied ${copiedDirs} dirs / ${copiedFiles} files`);
console.log(`manifest: wrote ${manifest.length} records to ${path.relative(repoRoot, manifestPath)}`);
console.log(`pl0615 animation assets: ${animationSummary}`);
