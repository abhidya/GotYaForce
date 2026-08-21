#!/usr/bin/env node

import { mkdtemp, rm } from "node:fs/promises";
import { tmpdir } from "node:os";
import { dirname, join, resolve } from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";

import { build } from "esbuild";

const repoRoot = resolve(dirname(fileURLToPath(import.meta.url)), "../../..");
const temporaryDirectory = await mkdtemp(join(tmpdir(), "gotyaforce-combat-lifecycle-"));
const bundlePath = join(temporaryDirectory, "lifecycle.selftest.mjs");

try {
  await build({
    absWorkingDir: repoRoot,
    entryPoints: ["packages/combat/src/lifecycle.selftest.ts"],
    outfile: bundlePath,
    bundle: true,
    platform: "node",
    format: "esm",
    alias: {
      "@gf/physics": resolve(repoRoot, "packages/physics/src/index.ts"),
      "@gf/render": resolve(repoRoot, "packages/render/src/index.ts"),
    },
    logLevel: "warning",
  });
  const selftest = await import(pathToFileURL(bundlePath).href);
  if (typeof selftest.runSelfTest !== "function") {
    throw new TypeError("combat lifecycle bundle does not export runSelfTest");
  }
  selftest.runSelfTest();
} finally {
  await rm(temporaryDirectory, { recursive: true, force: true });
}
