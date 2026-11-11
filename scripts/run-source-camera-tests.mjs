#!/usr/bin/env node
// Exercise the render compatibility path and the one pure camera implementation.
// No prior build or browser is required.
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const scratch = fs.mkdtempSync(path.join(os.tmpdir(), "gf-camera-selfcheck-"));
try {
  const graph = emitInlineModuleGraph({
    label: "sourceCamera.selftest",
    entry: path.join(root, "packages/render/src/camera/sourceCamera.ts"),
    outDir: path.join(scratch, "modules"),
    packages: {
      "@gf/camera-math": path.join(root, "packages/camera-math/src/index.ts"),
    },
  });
  assert(graph.modules.includes(path.join(root, "packages/camera-math/src/sourceCamera.ts")),
    "render compatibility path must exercise the shared camera implementation");
  const camera = await import(graph.url);
  camera.runSourceCameraSelfTests((condition, message) => assert(condition, message));
  console.log("sourceCamera.selftest: all checks passed through the shared camera package");
} finally {
  fs.rmSync(scratch, { recursive: true, force: true });
}
