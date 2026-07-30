#!/usr/bin/env node

import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

import { importArtifact } from "./lib/oghidra-port-import.mjs";

function parseArgs(argv) {
  const result = { force: false };
  for (let index = 0; index < argv.length; index += 1) {
    const value = argv[index];
    if (value === "--force") result.force = true;
    else if (value === "--artifact") result.artifactPath = argv[++index];
    else if (value === "--generated") result.generatedPath = argv[++index];
    else if (value === "--report") result.reportPath = argv[++index];
    else throw new Error(`unknown argument: ${value}`);
  }
  if (!result.artifactPath) throw new Error("--artifact is required");
  return result;
}

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

try {
  const args = parseArgs(process.argv.slice(2));
  const address = path.basename(args.artifactPath).match(/[0-9a-f]{8}/i)?.[0]?.toLowerCase() ?? "unknown";
  const result = importArtifact({
    artifactPath: path.resolve(args.artifactPath),
    generatedPath: path.resolve(
      args.generatedPath
      ?? path.join(root, "packages", "combat", "src", "generated", "oghidra", `fn_${address}.generated.ts`),
    ),
    reportPath: path.resolve(
      args.reportPath
      ?? path.join(root, "research", "decomp", "generated", `${address}-import-report.md`),
    ),
    force: args.force,
  });
  process.stdout.write(`${JSON.stringify(result, null, 2)}\n`);
  process.exitCode = result.fallback ? 2 : 0;
} catch (error) {
  process.stderr.write(`${error instanceof Error ? error.message : String(error)}\n`);
  process.exitCode = 1;
}
