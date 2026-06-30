#!/usr/bin/env node
import { copyFile, mkdir, readdir, rm, stat, writeFile } from "node:fs/promises";
import path from "node:path";

const region = process.argv[2] ?? "GG4E";
const stageCode = (process.argv[3] ?? "00").toLowerCase();
const root = path.resolve(`user-data/${region}/afs_data/root`);
const outRoot = path.resolve("apps/game/public/stages");
const outDir = path.join(outRoot, `st${stageCode}`);

const stageArc = path.join(root, `st${stageCode}_mdl.arc`);
const stagePzz = path.join(root, `st${stageCode}.pzz`);
const hitBins = [`hit${stageCode}0.bin`, `hit${stageCode}1.bin`, `hit${stageCode}2.bin`].map((name) => path.join(root, name));
const setArcs = [`set${stageCode}00.arc`, `set${stageCode}01.arc`, `set${stageCode}02.arc`, `set${stageCode}03.arc`].map((name) => path.join(root, name));

async function exists(file) {
  try {
    await stat(file);
    return true;
  } catch {
    return false;
  }
}

async function copyIfExists(file, subdir) {
  if (!(await exists(file))) return null;
  const targetDir = path.join(outDir, subdir);
  await mkdir(targetDir, { recursive: true });
  const target = path.join(targetDir, path.basename(file));
  await copyFile(file, target);
  return path.relative(outRoot, target).replaceAll("\\", "/");
}

await mkdir(outRoot, { recursive: true });
await rm(outDir, { recursive: true, force: true });
await mkdir(outDir, { recursive: true });

const copied = {
  stageArc: await copyIfExists(stageArc, "raw"),
  stagePzz: await copyIfExists(stagePzz, "raw"),
  hitBins: (await Promise.all(hitBins.map((file) => copyIfExists(file, "collision")))).filter(Boolean),
  setArcs: (await Promise.all(setArcs.map((file) => copyIfExists(file, "set")))).filter(Boolean),
};

const manifest = {
  region,
  id: `st${stageCode}`,
  source: "user-data/GG4E/afs_data/root",
  status: copied.stageArc ? "raw-copied" : "missing-stage-arc",
  copied,
  notes: [
    "Raw stage assets copied from local ISO extraction.",
    "Rendering still needs HSD stage ARC export to DAE/GLB.",
    "Collision hit*.bin copied but not decoded.",
  ],
};

await writeFile(path.join(outDir, "manifest.json"), `${JSON.stringify(manifest, null, 2)}\n`);

const stageDirs = (await readdir(outRoot, { withFileTypes: true }))
  .filter((entry) => entry.isDirectory())
  .map((entry) => entry.name)
  .sort();
await writeFile(path.join(outRoot, "manifest.json"), `${JSON.stringify({ region, stages: stageDirs }, null, 2)}\n`);

console.log(JSON.stringify(manifest, null, 2));
