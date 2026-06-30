#!/usr/bin/env node
import { copyFile, mkdir, readdir, readFile, rm, stat, writeFile } from "node:fs/promises";
import { existsSync } from "node:fs";
import path from "node:path";
import crypto from "node:crypto";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const scriptPath = "scripts/export-ui-scenes.mjs";
const args = process.argv.slice(2);
const exportMode = args.includes("--export");
const region = args.find((arg) => !arg.startsWith("--")) ?? "GG4E";

const sourceRootRel = `user-data/${region}/afs_data/root`;
const sourceRoot = abs(sourceRootRel);
const existingExportRootRel = `user-data/${region}/gltf-export`;
const existingExportRoot = abs(existingExportRootRel);
const publicScenesRootRel = "apps/game/public/ui/scenes";
const publicScenesRoot = abs(publicScenesRootRel);

const requiredSceneNames = [
  "tl00",
  "optn00",
  "staff00",
  "box00",
  "entry00",
  "brif00",
  "vsel00",
  "vsel01",
  "rpot20",
  "rpot21",
  "rpot22",
  "rpot23",
];

function abs(file) {
  return path.resolve(repoRoot, file);
}

function rel(file) {
  return path.relative(repoRoot, path.resolve(file)).replaceAll(path.sep, "/");
}

function slash(file) {
  return file.replaceAll(path.sep, "/");
}

function archiveNameFor(sceneName) {
  return `${sceneName}_mdl.arc`;
}

function sceneNameFromArchive(fileName) {
  return fileName.replace(/_mdl\.arc$/i, "");
}

function publicPath(file) {
  return `/${rel(file).replace(/^apps\/game\/public\//, "")}`;
}

async function sha1File(file) {
  return crypto.createHash("sha1").update(await readFile(file)).digest("hex");
}

async function listFilesRecursive(root) {
  if (!existsSync(root)) return [];
  const files = [];
  async function walk(dir) {
    const entries = await readdir(dir, { withFileTypes: true });
    for (const entry of entries) {
      const fullPath = path.join(dir, entry.name);
      if (entry.isDirectory()) await walk(fullPath);
      else if (entry.isFile()) files.push(fullPath);
    }
  }
  await walk(root);
  return files.sort((a, b) => rel(a).localeCompare(rel(b)));
}

async function discoverRawArchives() {
  if (!existsSync(sourceRoot)) {
    throw new Error(`missing ${sourceRootRel}; run extraction before exporting UI scenes`);
  }

  const entries = await readdir(sourceRoot, { withFileTypes: true });
  const rawByScene = new Map();
  for (const entry of entries) {
    if (!entry.isFile() || !/_mdl\.arc$/i.test(entry.name)) continue;
    const sceneName = sceneNameFromArchive(entry.name).toLowerCase();
    if (!requiredSceneNames.includes(sceneName) && !sceneName.startsWith("face")) continue;
    const file = path.join(sourceRoot, entry.name);
    const fileStat = await stat(file);
    rawByScene.set(sceneName, {
      sourceName: entry.name,
      sourcePath: rel(file),
      sourceBytes: fileStat.size,
    });
  }
  return rawByScene;
}

async function discoverExistingExport(sceneName) {
  const exportDir = path.join(existingExportRoot, sceneName);
  const files = await listFilesRecursive(exportDir);
  const models = [];
  const textures = [];
  const otherFiles = [];

  for (const file of files) {
    const ext = path.extname(file).toLowerCase();
    const record = {
      sourcePath: rel(file),
      sourceBytes: (await stat(file)).size,
      sha1: await sha1File(file),
    };
    if (ext === ".dae") models.push(record);
    else if (ext === ".png") textures.push(record);
    else otherFiles.push(record);
  }

  return {
    sourceDir: existsSync(exportDir) ? rel(exportDir) : null,
    models,
    textures,
    otherFiles,
  };
}

async function makeCandidate(sceneName, rawByScene) {
  const raw = rawByScene.get(sceneName) ?? null;
  const existingExport = await discoverExistingExport(sceneName);
  const status =
    existingExport.models.length > 0
      ? "copy-ready"
      : raw
        ? "raw-archive-discovered"
        : "missing-source";
  const caveats = [];

  if (status === "copy-ready") {
    caveats.push("Using existing HSDRawViewer DAE export output; this script does not infer runtime menu layout.");
  } else if (raw) {
    caveats.push("Raw UI HSD archive found, but no validated DAE/glTF export output exists yet.");
  } else {
    caveats.push(`Expected ${archiveNameFor(sceneName)} was not found under ${sourceRootRel}.`);
  }

  return {
    id: sceneName,
    kind: sceneName.startsWith("face") ? "face-model" : "ui-scene-model",
    requested: requiredSceneNames.includes(sceneName),
    rawSource: raw,
    existingExport,
    status,
    outputDir: `${publicScenesRootRel}/${sceneName}`,
    modelFiles: [],
    textureFiles: [],
    textureCount: existingExport.textures.length,
    caveats,
  };
}

async function makeManifest(candidates, writeResults = new Map()) {
  const assets = candidates.map((candidate) => {
    const written = writeResults.get(candidate.id);
    return {
      id: candidate.id,
      kind: candidate.kind,
      requested: candidate.requested,
      status: written?.status ?? (exportMode ? "not-exported" : candidate.status),
      sourceArchive: candidate.rawSource,
      existingExport: {
        sourceDir: candidate.existingExport.sourceDir,
        modelCount: candidate.existingExport.models.length,
        textureCount: candidate.existingExport.textures.length,
        models: candidate.existingExport.models,
        textures: candidate.existingExport.textures,
      },
      outputDir: candidate.outputDir,
      modelFiles: written?.modelFiles ?? [],
      textureFiles: written?.textureFiles ?? [],
      textureCount: written?.textureFiles?.length ?? 0,
      caveats: [
        ...candidate.caveats,
        ...(written?.caveats ?? []),
      ],
    };
  });

  return {
    generatedBy: scriptPath,
    generatedAt: new Date().toISOString(),
    region,
    mode: exportMode ? "export" : "dry-run",
    sourceRoot: sourceRootRel,
    existingExportRoot: existingExportRootRel,
    publicScenesRoot: publicScenesRootRel,
    counts: {
      candidates: assets.length,
      requestedCandidates: assets.filter((asset) => asset.requested).length,
      faceCandidates: assets.filter((asset) => asset.kind === "face-model").length,
      copyReady: candidates.filter((candidate) => candidate.status === "copy-ready").length,
      exported: assets.filter((asset) => asset.status === "exported").length,
      modelFiles: assets.reduce((sum, asset) => sum + asset.modelFiles.length, 0),
      textureFiles: assets.reduce((sum, asset) => sum + asset.textureFiles.length, 0),
    },
    caveats: [
      "Asset plumbing only: no runtime UI replacement, menu layout reconstruction, camera setup, or UI behavior is generated here.",
      "Archives without existing validated DAE/glTF output are listed for follow-up instead of guessed or hand-built.",
    ],
    assets,
  };
}

async function copyCandidate(candidate) {
  if (candidate.status !== "copy-ready") {
    return {
      status: "not-exported",
      modelFiles: [],
      textureFiles: [],
      caveats: ["No validated model export output to copy."],
    };
  }

  const outputDir = abs(candidate.outputDir);
  const resolvedOutput = path.resolve(outputDir);
  const resolvedRoot = path.resolve(publicScenesRoot);
  if (resolvedOutput !== resolvedRoot && !resolvedOutput.startsWith(`${resolvedRoot}${path.sep}`)) {
    throw new Error(`refusing to write outside ${publicScenesRootRel}: ${resolvedOutput}`);
  }

  await rm(outputDir, { recursive: true, force: true });
  await mkdir(outputDir, { recursive: true });

  const modelFiles = [];
  for (const model of candidate.existingExport.models) {
    const source = abs(model.sourcePath);
    const target = path.join(outputDir, path.basename(model.sourcePath));
    await copyFile(source, target);
    modelFiles.push({
      path: rel(target),
      publicPath: publicPath(target),
      bytes: (await stat(target)).size,
      sha1: await sha1File(target),
      sourcePath: model.sourcePath,
    });
  }

  const textureFiles = [];
  for (const texture of candidate.existingExport.textures) {
    const source = abs(texture.sourcePath);
    const target = path.join(outputDir, path.basename(texture.sourcePath));
    await copyFile(source, target);
    textureFiles.push({
      path: rel(target),
      publicPath: publicPath(target),
      bytes: (await stat(target)).size,
      sha1: await sha1File(target),
      sourcePath: texture.sourcePath,
    });
  }

  return {
    status: "exported",
    modelFiles,
    textureFiles,
    caveats: ["Copied real extracted DAE/PNG assets from existing local HSDRawViewer export output."],
  };
}

function printSummary(manifest) {
  const ready = manifest.assets.filter((asset) => asset.existingExport.modelCount > 0);
  const pending = manifest.assets.filter((asset) => asset.status === "raw-archive-discovered" || asset.status === "not-exported");
  console.log(`ui scene export ${manifest.mode}`);
  console.log(`region: ${manifest.region}`);
  console.log(`candidates: ${manifest.counts.candidates} (${manifest.counts.requestedCandidates} requested, ${manifest.counts.faceCandidates} face models)`);
  console.log(`copy-ready existing DAE exports: ${ready.length}`);
  console.log(`exported models: ${manifest.counts.modelFiles}`);
  console.log(`exported textures: ${manifest.counts.textureFiles}`);
  if (ready.length > 0) console.log(`ready: ${ready.map((asset) => asset.id).join(", ")}`);
  if (pending.length > 0) console.log(`pending exporter support: ${pending.slice(0, 16).map((asset) => asset.id).join(", ")}${pending.length > 16 ? `, +${pending.length - 16} more` : ""}`);
  if (!exportMode) console.log("dry run only; rerun with --export to write apps/game/public/ui/scenes");
}

async function main() {
  const rawByScene = await discoverRawArchives();
  const sceneNames = [...new Set([...requiredSceneNames, ...[...rawByScene.keys()].filter((name) => name.startsWith("face"))])].sort((a, b) => {
    const requiredDelta = Number(requiredSceneNames.includes(b)) - Number(requiredSceneNames.includes(a));
    return requiredDelta || a.localeCompare(b);
  });
  const candidates = [];
  for (const sceneName of sceneNames) {
    candidates.push(await makeCandidate(sceneName, rawByScene));
  }

  const writeResults = new Map();
  if (exportMode) {
    await mkdir(publicScenesRoot, { recursive: true });
    for (const candidate of candidates) {
      writeResults.set(candidate.id, await copyCandidate(candidate));
    }
  }

  const manifest = await makeManifest(candidates, writeResults);
  if (exportMode) {
    await writeFile(path.join(publicScenesRoot, "manifest.json"), `${JSON.stringify(manifest, null, 2)}\n`, "utf8");
  }

  printSummary(manifest);
  if (exportMode) console.log(`wrote ${slash(path.join(publicScenesRootRel, "manifest.json"))}`);
}

main().catch((error) => {
  console.error(`export-ui-scenes: ${error.stack ?? error.message}`);
  process.exit(1);
});
