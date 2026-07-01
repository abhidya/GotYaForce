#!/usr/bin/env node
// Bake EVERY animation bank in a Gotcha Force pl****mot.bin to the web app's
// models folder, using the proven HSDRaw-based baker (borg-anim-allbanks).
//
// Usage: node scripts/bake-all-borg-anims.mjs <borgId> [region]
//
// Bank labels are HEURISTIC (group/slot convention shared across borgs, anchored
// by a few human-verified clips for pl0615). See
// research/format-specs/borg-animation-banks.md for confidence per label.
import fs from "node:fs";
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { unpack as unpackPzz } from "../packages/formats/src/pzz.ts";

const region = process.argv[3] ?? "GG4E";
const borgId = (process.argv[2] ?? "pl0615").toLowerCase();
const repoRoot = path.resolve(".");
const rootDir = path.join(repoRoot, "user-data", region, "afs_data", "root");
const tempSourceDir = path.join(repoRoot, ".tmp", "pzz-bake-members", region, borgId);
const motPath = materializeSourceMember(`${borgId}mot.bin`, 3);
const modelPath = materializeSourceMember(`${borgId}_mdl.arc`, 4);
const outDir = path.join(repoRoot, "apps", "game", "public", "models", borgId);
const csproj = path.join(repoRoot, "user-data", region, "borg-anim-allbanks", "borg-anim-allbanks.csproj");

for (const f of [motPath.path, modelPath.path, csproj]) {
  if (!fs.existsSync(f)) { console.error(`missing ${f}`); process.exit(1); }
}
if (motPath.source === "pzz") console.log(`using ${borgId}.pzz member 003 -> ${rel(motPath.path)}`);
if (modelPath.source === "pzz") console.log(`using ${borgId}.pzz member 004 -> ${rel(modelPath.path)}`);

// (group,slot) -> short action label. Confidence noted in the banks .md.
// Group 0 = core locomotion/movement; group 1 = attack moveset;
// group 3 = damage/hit reactions; group 4 = special/long; group 5 = death/victory.
function label(group, slot, frames, loopErr, spanZ, spanX) {
  const g = group, s = slot;
  if (g === 0) {
    if (s === 0) return "idle";
    if (s === 1) return "move";
    if (s === 2) return "dash_fwd";
    if (s === 3) return "dash_back";
    if (s === 4) return "dash_left";
    if (s === 5) return "dash_right";
    if (s === 6) return "jump_takeoff";
    if (s === 7) return "jump_land";
    if (s === 8) return "turn";
    if (s === 9) return "fly_transition";
    if (s === 14 || s === 24) return "pose_short";
    if (s === 23) return "boost";
    return `move_s${s}`;
  }
  if (g === 1) {
    // attack moveset; ones with forward root Z motion are lunge attacks
    if (spanZ > 20) return `attack_lunge_s${s}`;
    return `attack_s${s}`;
  }
  if (g === 3) {
    // damage / hit reactions / guard; short clips
    if (frames <= 16) return `hit_react_s${s}`;
    return `guard_s${s}`;
  }
  if (g === 4) {
    // g4s0 is the knockdown/"down" pose, not a generic special — see
    // research/format-specs/borg-animation-banks.md's decomp cross-reference
    // (cross-referenced high confidence: knockdown=g4s0, matches the prior
    // human-labeled `down_candidate` anchor) and behavior-notes.md s5 item 3.
    if (s === 0) return "down_s0";
    return `special_s${s}`;
  }
  if (g === 5) {
    // longest non-looping clips: death / victory
    if (s === 1) return "death";
    if (s === 0) return "win_or_death";
    if (s === 2) return "victory";
    return `finisher_s${s}`;
  }
  return `g${g}_s${s}`;
}

const dll = path.join(
  repoRoot, "user-data", region, "borg-anim-allbanks",
  "bin", "Release", "net6.0-windows", "borg-anim-allbanks.dll",
);

// 1. get manifest
const man = spawnSync("dotnet", [dll, "manifest", motPath.path, modelPath.path, "0x100"], {
  cwd: repoRoot, shell: true, encoding: "utf8", maxBuffer: 64 * 1024 * 1024,
});
if ((man.status ?? 1) !== 0) { console.error(man.stderr); process.exit(1); }
const jsonStart = man.stdout.indexOf("{");
const manifest = JSON.parse(man.stdout.slice(jsonStart));

await mkdir(outDir, { recursive: true });
const index = [];
for (const b of manifest.banks) {
  if (b.frames < 1 || b.err) { console.warn(`skip g${b.group}s${b.slot}: ${b.err ?? "no frames"}`); continue; }
  const lbl = label(b.group, b.slot, b.frames, b.loopErr, b.rootSpanZ, b.rootSpanX);
  const name = `anim_g${String(b.group).padStart(2, "0")}_s${String(b.slot).padStart(2, "0")}_${lbl}.json`;
  const outPath = path.join(outDir, name);
  const r = spawnSync("dotnet", [
    dll, "bake", motPath.path, modelPath.path, "0x100", String(b.group), String(b.slot), "0", outPath,
  ], { cwd: repoRoot, shell: true, stdio: "ignore" });
  if ((r.status ?? 1) !== 0) { console.error(`bake failed g${b.group}s${b.slot}`); continue; }
  index.push({ file: name, group: b.group, slot: b.slot, label: lbl, frames: b.frames,
    animJoints: b.animJoints, rootSpanX: b.rootSpanX, rootSpanY: b.rootSpanY, rootSpanZ: b.rootSpanZ });
  console.log(`${borgId} g${b.group}s${b.slot} ${lbl} (${b.frames}f) -> ${name}`);
}
await writeFile(path.join(outDir, "anim_index.json"),
  JSON.stringify({ borg: borgId, bankCount: index.length, banks: index }, null, 2));
console.log(`\n${borgId}: baked ${index.length} clips + anim_index.json`);

function materializeSourceMember(fileName, memberIndex) {
  const loosePath = path.join(rootDir, fileName);
  if (fs.existsSync(loosePath)) return { path: loosePath, source: "loose" };

  const archivePath = path.join(rootDir, `${borgId}.pzz`);
  if (!fs.existsSync(archivePath)) return { path: loosePath, source: "missing" };

  const archive = unpackPzz(fs.readFileSync(archivePath));
  const member = archive.members[memberIndex];
  if (!member || member.payload.byteLength === 0) return { path: loosePath, source: "missing" };

  fs.mkdirSync(tempSourceDir, { recursive: true });
  const outPath = path.join(tempSourceDir, fileName);
  fs.writeFileSync(outPath, Buffer.from(member.payload));
  return { path: outPath, source: "pzz" };
}

function rel(filePath) {
  return path.relative(repoRoot, filePath).replaceAll(path.sep, "/");
}
