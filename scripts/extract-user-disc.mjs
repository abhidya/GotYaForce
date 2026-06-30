#!/usr/bin/env node
// Validate a user-supplied Gotcha Force disc image and prepare the local extract folder.

import { createHash } from "crypto";
import fs from "fs";
import path from "path";

const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);
const [region, isoArg] = process.argv.slice(2);

function usage() {
  console.error("usage: node scripts/extract-user-disc.mjs <GG4E|GG4J|GG4P> <path-to-iso>");
  process.exit(1);
}

function fail(message) {
  console.error(`error: ${message}`);
  process.exit(1);
}

async function hashFile(filePath, algorithm) {
  const hash = createHash(algorithm);
  await new Promise((resolve, reject) => {
    const stream = fs.createReadStream(filePath);
    stream.on("data", (chunk) => hash.update(chunk));
    stream.on("error", reject);
    stream.on("end", resolve);
  });
  return hash.digest("hex");
}

if (!region || !isoArg) usage();
if (!REGIONS.has(region)) fail(`unsupported region "${region}"`);

const repoRoot = process.cwd();
const isoPath = path.resolve(repoRoot, isoArg);
if (!fs.existsSync(isoPath)) fail(`ISO does not exist: ${isoPath}`);
if (!fs.statSync(isoPath).isFile()) fail(`ISO path is not a file: ${isoPath}`);

const header = Buffer.alloc(6);
const fd = fs.openSync(isoPath, "r");
try {
  const bytesRead = fs.readSync(fd, header, 0, header.length, 0);
  if (bytesRead !== header.length) fail("ISO is too small to contain a GameCube disc id");
} finally {
  fs.closeSync(fd);
}

const discId = header.toString("ascii");
if (discId.slice(0, 4) !== region) {
  fail(`disc id mismatch: expected ${region}, found ${discId.slice(0, 4)}`);
}

const discDir = path.join(repoRoot, "user-data", region, "disc");
const rootDir = path.join(discDir, "root");
fs.mkdirSync(discDir, { recursive: true });

const [sha1, md5] = await Promise.all([hashFile(isoPath, "sha1"), hashFile(isoPath, "md5")]);

const hashFilePath = path.join(discDir, `${region}.hashes.json`);
const hashRecord = {
  region,
  discId,
  iso: path.relative(repoRoot, isoPath).replaceAll(path.sep, "/"),
  bytes: fs.statSync(isoPath).size,
  sha1,
  md5,
};
fs.writeFileSync(`${hashFilePath}.tmp`, `${JSON.stringify(hashRecord, null, 2)}\n`);
fs.renameSync(`${hashFilePath}.tmp`, hashFilePath);

console.log(`region: ${region}`);
console.log(`disc id: ${discId}`);
console.log(`sha1: ${sha1}`);
console.log(`md5: ${md5}`);
console.log(`hashes: ${path.relative(repoRoot, hashFilePath)}`);

if (fs.existsSync(rootDir)) {
  console.log(`extract: existing ${path.relative(repoRoot, rootDir)}; not re-extracting`);
} else {
  console.log(`extract: prepared ${path.relative(repoRoot, discDir)}`);
  console.log("extract: root/ is missing; unpack the ISO there with the project-approved extractor before continuing");
  process.exitCode = 2;
}
