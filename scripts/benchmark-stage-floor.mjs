#!/usr/bin/env node
// Reproducible synthetic query workload over the committed st00 STIH layers.
import { createRequire } from "node:module";
import { fileURLToPath } from "node:url";
import path from "node:path";
const root = fileURLToPath(new URL("../", import.meta.url));
const require = createRequire(path.join(root, "packages/combat/package.json"));
const { build } = require("esbuild");
const result = await build({absWorkingDir:root, entryPoints:["scripts/benchmark-stage-floor.ts"],
  bundle:true,platform:"node",format:"esm",conditions:["development"],write:false,logLevel:"warning"});
process.chdir(root);
await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString("base64")}`);
