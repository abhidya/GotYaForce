#!/usr/bin/env node
// asset-convert.mjs - run the offline asset pipeline for one region.

import { runAssetConversionPipeline } from "./lib/asset-pipeline.mjs";

const args = process.argv.slice(2);
const region = args.find((arg) => !arg.startsWith("--"));
const dryRun = args.includes("--dry-run");
const only = args
  .filter((arg) => arg.startsWith("--only="))
  .flatMap((arg) => arg.slice("--only=".length).split(",").map((item) => item.trim()).filter(Boolean));

if (!region) {
  console.error("usage: node scripts/asset-convert.mjs <GG4E|GG4J|GG4P> [--dry-run] [--only=audio,stages,ui,borg-model-library,stage-manifests]");
  process.exit(1);
}

try {
  const { context, results } = runAssetConversionPipeline({
    region,
    dryRun,
    ...(only.length > 0 ? { only } : {}),
  });
  console.log(JSON.stringify({
    region: context.region,
    dryRun,
    steps: results,
  }, null, 2));
} catch (error) {
  console.error(`asset-convert: ${error instanceof Error ? error.message : String(error)}`);
  process.exit(1);
}
