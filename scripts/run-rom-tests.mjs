#!/usr/bin/env node
// Execute the real ROM selfcheck source graph without stale dist or Node/TS imports.
import { createRequire } from "node:module";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
// esbuild is the combat package's pinned test dependency, also used by lifecycle.
const require = createRequire(path.join(root, "packages/combat/package.json"));
const { build } = require("esbuild");
const result = await build({
  absWorkingDir: root,
  stdin: {
    contents: 'import { runSelfTest } from "./packages/combat/src/rom/rom.selfcheck.ts"; process.exitCode = runSelfTest();',
    resolveDir: root,
    sourcefile: "rom-selfcheck-entry.mjs",
  },
  bundle: true,
  platform: "node",
  format: "esm",
  write: false,
  logLevel: "warning",
});
await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString("base64")}`);
