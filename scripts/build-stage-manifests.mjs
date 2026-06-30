#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";

const region = process.argv[2] ?? "GG4E";
const stagesRoot = path.resolve("apps/game/public/stages");

function sortedDirEntries(dir) {
  return fs.existsSync(dir)
    ? fs.readdirSync(dir, { withFileTypes: true }).sort((a, b) => a.name.localeCompare(b.name))
    : [];
}

function fileRecord(filePath, root) {
  const stats = fs.statSync(filePath);
  return {
    path: path.relative(root, filePath).replaceAll("\\", "/"),
    bytes: stats.size,
  };
}

fs.mkdirSync(stagesRoot, { recursive: true });

const stages = [];
for (const entry of sortedDirEntries(stagesRoot)) {
  if (!entry.isDirectory() || !/^st[0-9a-f]{2}$/i.test(entry.name)) continue;
  const stageDir = path.join(stagesRoot, entry.name);
  const modelDir = path.join(stageDir, "model");
  const rawManifestPath = path.join(stageDir, "manifest.json");
  const rawManifest = fs.existsSync(rawManifestPath)
    ? JSON.parse(fs.readFileSync(rawManifestPath, "utf8"))
    : {};
  const models = sortedDirEntries(modelDir)
    .filter((modelEntry) => modelEntry.isFile() && /^model_\d+\.dae$/i.test(modelEntry.name))
    .map((modelEntry) => fileRecord(path.join(modelDir, modelEntry.name), stageDir));
  const collision = sortedDirEntries(path.join(stageDir, "collision"))
    .filter((collisionEntry) => collisionEntry.isFile())
    .map((collisionEntry) => fileRecord(path.join(stageDir, "collision", collisionEntry.name), stageDir));
  const setArcs = sortedDirEntries(path.join(stageDir, "set"))
    .filter((setEntry) => setEntry.isFile())
    .map((setEntry) => fileRecord(path.join(stageDir, "set", setEntry.name), stageDir));

  const manifest = {
    ...rawManifest,
    region,
    id: entry.name,
    modelCount: models.length,
    models,
    collision,
    setArcs,
    renderStatus: models.length > 0 ? "dae-exported" : "raw-only",
  };
  fs.writeFileSync(path.join(stageDir, "manifest.json"), `${JSON.stringify(manifest, null, 2)}\n`);
  stages.push({
    id: entry.name,
    modelCount: models.length,
    renderStatus: manifest.renderStatus,
    collisionCount: collision.length,
    setArcCount: setArcs.length,
  });
}

const rootManifest = {
  region,
  generatedBy: "scripts/build-stage-manifests.mjs",
  stages,
};
fs.writeFileSync(path.join(stagesRoot, "manifest.json"), `${JSON.stringify(rootManifest, null, 2)}\n`);
console.log(JSON.stringify(rootManifest, null, 2));
