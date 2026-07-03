import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { spawnSync } from "node:child_process";

export const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);

export function normalizeRegion(value) {
  const region = String(value ?? "").trim().toUpperCase();
  if (!REGIONS.has(region)) throw new Error(`unsupported region "${value}"`);
  return region;
}

export function createAssetPipelineContext(region, repoRoot = process.cwd()) {
  const normalized = normalizeRegion(region);
  return {
    region: normalized,
    repoRoot: path.resolve(repoRoot),
    userDataRoot: path.resolve(repoRoot, "user-data", normalized),
    convertedRoot: path.resolve(repoRoot, "user-data", "converted", normalized),
    publicRoot: path.resolve(repoRoot, "apps", "game", "public"),
    discRoot: path.resolve(repoRoot, "research", "disc", normalized),
  };
}

export function assetConversionSteps(region) {
  return [
    {
      name: "audio",
      command: ["node", "scripts/export-audio-assets.mjs", region],
      outputs: ["apps/game/public/audio"],
    },
    {
      name: "stages",
      command: ["node", "scripts/export-all-stages.mjs", region],
      outputs: ["apps/game/public/stages"],
    },
    {
      name: "ui",
      command: ["node", "scripts/export-ui-assets.mjs", region],
      outputs: ["apps/game/public/ui"],
    },
    {
      name: "borg-model-library",
      command: ["node", "scripts/sync-exported-assets.mjs", region],
      outputs: ["apps/game/public/models/library"],
    },
    {
      name: "stage-manifests",
      command: ["node", "scripts/build-stage-manifests.mjs", region],
      outputs: ["apps/game/public/stages/manifest.json", "apps/game/src/stages/catalog.generated.ts"],
    },
  ];
}

export function runAssetConversionPipeline(options) {
  const context = createAssetPipelineContext(options.region, options.repoRoot);
  const dryRun = options.dryRun === true;
  const selected = new Set(options.only ?? []);
  const steps = assetConversionSteps(context.region).filter((step) => selected.size === 0 || selected.has(step.name));
  if (steps.length === 0) throw new Error(`no conversion steps selected for ${context.region}`);

  const results = [];
  for (const step of steps) {
    if (dryRun) {
      results.push({ name: step.name, status: "dry-run", command: step.command, outputs: step.outputs });
      continue;
    }
    const result = spawnSync(step.command[0], step.command.slice(1), {
      cwd: context.repoRoot,
      stdio: "inherit",
      shell: process.platform === "win32",
    });
    if ((result.status ?? 1) !== 0) {
      throw new Error(`asset conversion step failed: ${step.name} exit=${result.status ?? 1}`);
    }
    results.push({ name: step.name, status: "ok", command: step.command, outputs: step.outputs });
  }
  return { context, results };
}

export function buildAssetManifest(options) {
  const context = createAssetPipelineContext(options.region, options.repoRoot);
  const sourceRoot = path.resolve(options.sourceRoot ?? context.publicRoot);
  const outPath = path.resolve(options.outPath ?? path.join(context.publicRoot, "asset-manifest.json"));
  const assets = walkFiles(sourceRoot)
    .filter((file) => path.resolve(file) !== outPath)
    .map((file) => {
      const stat = fs.statSync(file);
      return {
        path: rel(sourceRoot, file),
        type: classifyAsset(file),
        bytes: stat.size,
        sha1: sha1File(file),
      };
    });

  const manifest = {
    generatedBy: "scripts/build-manifest.mjs",
    region: context.region,
    disc: {
      region: context.region,
      sha1: readDiscSha1(context),
    },
    sourceRoot: rel(context.repoRoot, sourceRoot),
    assets,
  };
  fs.mkdirSync(path.dirname(outPath), { recursive: true });
  fs.writeFileSync(`${outPath}.tmp`, `${JSON.stringify(manifest, null, 2)}\n`);
  fs.renameSync(`${outPath}.tmp`, outPath);
  return { context, manifest, outPath };
}

function readDiscSha1(context) {
  if (!fs.existsSync(context.discRoot)) return null;
  for (const file of walkFiles(context.discRoot)) {
    if (!/\.(?:sha1|hashes|txt)$/i.test(file)) continue;
    const text = fs.readFileSync(file, "utf8");
    const match = /\b[0-9a-f]{40}\b/i.exec(text);
    if (match) return match[0].toLowerCase();
  }
  return null;
}

function walkFiles(root) {
  if (!fs.existsSync(root)) return [];
  const out = [];
  for (const entry of fs.readdirSync(root, { withFileTypes: true }).sort((a, b) => a.name.localeCompare(b.name))) {
    const file = path.join(root, entry.name);
    if (entry.isDirectory()) out.push(...walkFiles(file));
    else if (entry.isFile()) out.push(file);
  }
  return out;
}

function classifyAsset(file) {
  const ext = path.extname(file).toLowerCase();
  if ([".json"].includes(ext)) return "json";
  if ([".dae", ".glb", ".gltf"].includes(ext)) return "model";
  if ([".png", ".jpg", ".jpeg", ".webp", ".tpl"].includes(ext)) return "texture";
  if ([".ogg", ".opus", ".wav", ".adx"].includes(ext)) return "audio";
  if ([".webm", ".mp4", ".sfd"].includes(ext)) return "video";
  if ([".bin", ".arc", ".pzz", ".afs"].includes(ext)) return "binary";
  if ([".js", ".ts", ".css", ".html"].includes(ext)) return "runtime";
  return ext ? ext.slice(1) : "unknown";
}

function sha1File(file) {
  return createHash("sha1").update(fs.readFileSync(file)).digest("hex");
}

function rel(root, file) {
  return path.relative(root, file).replaceAll("\\", "/");
}
