#!/usr/bin/env node
// build-manifest.mjs - emit hash-keyed manifest for browser-ready public assets.

import path from "node:path";
import { buildAssetManifest } from "./lib/asset-pipeline.mjs";

const args = process.argv.slice(2);
const region = args.find((arg) => !arg.startsWith("--"));
const sourceArg = args.find((arg) => arg.startsWith("--source="));
const outArg = args.find((arg) => arg.startsWith("--out="));

if (!region) {
  console.error("usage: node scripts/build-manifest.mjs <GG4E|GG4J|GG4P> [--source=apps/game/public] [--out=apps/game/public/asset-manifest.json]");
  process.exit(1);
}

try {
  const { context, manifest, outPath } = buildAssetManifest({
    region,
    ...(sourceArg ? { sourceRoot: path.resolve(sourceArg.slice("--source=".length)) } : {}),
    ...(outArg ? { outPath: path.resolve(outArg.slice("--out=".length)) } : {}),
  });
  console.log(
    [
      `region: ${context.region}`,
      `discSha1: ${manifest.disc.sha1 ?? "unknown"}`,
      `assets: ${manifest.assets.length}`,
      `manifest: ${path.relative(context.repoRoot, outPath).replaceAll("\\", "/")}`,
    ].join("\n"),
  );
} catch (error) {
  console.error(`build-manifest: ${error instanceof Error ? error.message : String(error)}`);
  process.exit(1);
}
