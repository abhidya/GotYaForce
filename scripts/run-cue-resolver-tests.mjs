#!/usr/bin/env node
// Runs packages/audio/src/cueResolver.ts self-tests by transpiling the resolver + its
// generated table dependency to ESM in a temp dir. Mirrors run-challenge-flow-tests.mjs.
//
//   node scripts/run-cue-resolver-tests.mjs
import { transpileModule } from "typescript";
import { readFileSync, writeFileSync, mkdirSync } from "node:fs";
import path from "node:path";

const SRC = "packages/audio/src";
const TMP = path.join("node_modules/.cache/cue-resolver-selftest");

mkdirSync(TMP, { recursive: true });
writeFileSync(path.join(TMP, "package.json"), JSON.stringify({ type: "module" }));

const transpile = (file, out) => {
  const src = readFileSync(file, "utf8");
  const { outputText } = transpileModule(src, {
    compilerOptions: { target: "es2022", module: "es2022", moduleResolution: "bundler" },
  });
  writeFileSync(out, outputText);
};

transpile(path.join(SRC, "cueResolverTable.generated.ts"), path.join(TMP, "cueResolverTable.generated.js"));
transpile(path.join(SRC, "cueResolver.ts"), path.join(TMP, "cueResolver.js"));

const mod = await import(pathToFileURL(path.join(TMP, "cueResolver.js")));

let failures = 0;
let checks = 0;
const assert = (cond, msg) => {
  checks += 1;
  if (!cond) {
    failures += 1;
    console.error(`FAIL: ${msg}`);
  }
};

function pathToFileURL(p) {
  const resolved = path.resolve(p).replace(/\\/g, "/");
  return `file:///${resolved}`;
}

mod.runCueResolverSelfTests(assert);

if (failures > 0) {
  console.error(`cueResolver.selftest: ${failures}/${checks} checks FAILED`);
  process.exit(1);
}
console.log(`cueResolver.selftest: ${checks}/${checks} checks passed`);
