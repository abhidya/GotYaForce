#!/usr/bin/env node
// ============================================================================
// build-disc-index.mjs — turn an owner-supplied GameCube disc image into the
// FST index the DVD HLE host can serve reads from.
//
// WHY THIS IS SEPARATE FROM THE HOST. This repository contains NO disc bytes:
// `research/disc/` holds one .gitkeep and `.gitignore` excludes `*.iso`,
// `*.gcm`, `*.ciso` and `research/disc/*/`. Every other extractor in this
// directory reads the same untracked `user-data/GG4E/…` tree. So the DVD host
// ships with a disc it BUILDS IN MEMORY (packages/rom-runtime/src/dvd/disc.ts,
// `SyntheticDisc`) and this script is how an owner who has the real disc
// produces something the host's `ImageDisc` can read instead.
//
// WHAT IT EMITS. `research/disc/<REGION>-fst.json`:
//   { discId, discName, imageBytes, imageSha1, fstOffset, fstSize,
//     entries: [{ index, path, isDir, startAddr, length }] }
// Offsets and lengths are disc-absolute, which is exactly what
// gnt4_DVDOpen_bl writes into a DVDFileInfo (+0x30 / +0x34) — see
// docs/audio-dvd-hle-host.md §4.
//
// It does NOT copy any disc bytes into the repository. The index is a table of
// contents; reads still go to the image the owner keeps outside the tree.
//
// Usage:
//   node scripts/build-disc-index.mjs <path-to-disc-image.iso|gcm> [--region GG4E]
// ============================================================================

import crypto from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

/** [SDK] boot.bin keeps the FST pointer at 0x0424 and its size at 0x0428. */
const BOOT_FST_OFFSET = 0x0424;
const BOOT_FST_SIZE = 0x0428;
/** [CORPUS] gnt4_DVDOpen_bl indexes the FST as `entrynum * 0xc`. */
const FST_ENTRY_BYTES = 12;

function fail(message) {
  process.stderr.write(`build-disc-index: ${message}\n`);
  process.exit(2);
}

const args = process.argv.slice(2);
const imagePath = args.find((a) => !a.startsWith("--"));
const regionIndex = args.indexOf("--region");
const region = regionIndex >= 0 ? args[regionIndex + 1] : null;
if (!imagePath) fail("usage: node scripts/build-disc-index.mjs <disc-image> [--region GG4E]");
if (!fs.existsSync(imagePath)) fail(`no such file: ${imagePath}`);

const image = fs.readFileSync(imagePath);
if (image.length < 0x0440) fail(`${imagePath} is only ${image.length} bytes — that is not a GameCube disc image`);

// [SDK] the 6-byte disc id is at offset 0, the game name is a NUL-terminated
// string at 0x20.
const discId = image.subarray(0, 6).toString("latin1");
const nameEnd = image.indexOf(0, 0x20);
const discName = image.subarray(0x20, nameEnd < 0 ? 0x20 : Math.min(nameEnd, 0x20 + 0x3e0)).toString("latin1");
if (region && discId !== region) {
  fail(`disc id is ${discId}, not the requested ${region}`);
}

const fstOffset = image.readUInt32BE(BOOT_FST_OFFSET);
const fstSize = image.readUInt32BE(BOOT_FST_SIZE);
if (fstOffset + fstSize > image.length) {
  fail(`boot.bin points the FST at 0x${fstOffset.toString(16)}+${fstSize}, past the ${image.length}-byte image`);
}
const fst = image.subarray(fstOffset, fstOffset + fstSize);
const count = fst.readUInt32BE(8);
if (count < 1 || count * FST_ENTRY_BYTES > fst.length) {
  fail(`FST root claims ${count} entries, which does not fit in ${fst.length} bytes`);
}
const stringTableAt = count * FST_ENTRY_BYTES;

function nameAt(offset) {
  const at = stringTableAt + offset;
  const end = fst.indexOf(0, at);
  if (end < 0) fail(`unterminated FST name string at 0x${at.toString(16)}`);
  return fst.subarray(at, end).toString("latin1");
}

// Directory extents are a half-open [i+1, next) range, so one walk with a
// directory stack yields every path. Identical to `parseGcFst` in
// packages/rom-runtime/src/dvd/disc.ts, which is what will read this back.
const entries = [];
const stack = [];
for (let i = 0; i < count; i++) {
  const at = i * FST_ENTRY_BYTES;
  const w0 = fst.readUInt32BE(at + 0);
  const w1 = fst.readUInt32BE(at + 4);
  const w2 = fst.readUInt32BE(at + 8);
  const isDir = i === 0 || (w0 & 0xff000000) !== 0;
  while (stack.length > 0 && i >= stack[stack.length - 1].end) stack.pop();
  const parent = stack[stack.length - 1];
  const name = i === 0 ? "" : nameAt(w0 & 0x00ffffff);
  const entryPath = i === 0 ? "/" : `${parent ? parent.path : ""}/${name}`;
  entries.push({
    index: i,
    path: entryPath,
    isDir,
    startAddr: isDir ? 0 : w1,
    length: isDir ? 0 : w2,
  });
  if (isDir) stack.push({ path: i === 0 ? "" : entryPath, end: w2 });
}

const out = {
  generatedBy: "scripts/build-disc-index.mjs",
  note:
    "Table of contents only — NO disc bytes are copied into the repository. Reads still go to the image " +
    "the owner keeps outside the tree. Offsets and lengths are disc-absolute, which is what " +
    "gnt4_DVDOpen_bl writes into a DVDFileInfo at +0x30 and +0x34.",
  discId,
  discName,
  image: path.resolve(imagePath),
  imageBytes: image.length,
  imageSha1: crypto.createHash("sha1").update(image).digest("hex"),
  fstOffset,
  fstSize,
  entryCount: count,
  fileCount: entries.filter((e) => !e.isDir).length,
  entries,
};

const outDir = path.join(root, "research", "disc");
fs.mkdirSync(outDir, { recursive: true });
const outPath = path.join(outDir, `${discId.trim() || "disc"}-fst.json`);
fs.writeFileSync(outPath, `${JSON.stringify(out, null, 2)}\n`);
process.stdout.write(
  `disc ${discId} "${discName}": ${out.fileCount} files in ${count} FST entries -> ${path.relative(root, outPath)}\n`,
);
