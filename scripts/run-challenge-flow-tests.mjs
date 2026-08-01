#!/usr/bin/env node
// Runs apps/game/src/ui/intro/challengeFlowVm.ts self-tests by transpiling the VM + its
// generated-tables dependency to ESM in a temp dir (apps/game is noEmit, so there's no
// dist to import). Mirrors the run-burst-tests.mjs precedent but for the app package.
//
//   node scripts/run-challenge-flow-tests.mjs
import { transpileModule } from "typescript";
import { readFileSync, writeFileSync, mkdirSync } from "node:fs";
import path from "node:path";

const SRC = "apps/game/src/ui";
const TMP = path.join("node_modules/.cache/challenge-flow-selftest");

mkdirSync(path.join(TMP, "intro"), { recursive: true });
writeFileSync(path.join(TMP, "package.json"), JSON.stringify({ type: "module" }));

const transpile = (file, out) => {
  const src = readFileSync(file, "utf8");
  const { outputText } = transpileModule(src, {
    compilerOptions: { target: "es2022", module: "es2022", moduleResolution: "bundler" },
  });
  writeFileSync(out, outputText);
};

transpile(path.join(SRC, "challengeFlowTables.generated.ts"), path.join(TMP, "challengeFlowTables.generated.js"));
transpile(path.join(SRC, "intro/challengeFlowVm.ts"), path.join(TMP, "intro/challengeFlowVm.js"));

const mod = await import(pathToFileURL(path.join(TMP, "intro/challengeFlowVm.js")));

let failures = 0;
let checks = 0;
const assert = {
  equal(actual, expected, label) {
    checks += 1;
    if (actual !== expected) {
      failures += 1;
      console.error(`FAIL: ${label} — expected ${String(expected)}, got ${String(actual)}`);
    }
  },
  ok(cond, label) {
    checks += 1;
    if (!cond) {
      failures += 1;
      console.error(`FAIL: ${label}`);
    }
  },
};

function pathToFileURL(p) {
  const resolved = path.resolve(p).replace(/\\/g, "/");
  return `file:///${resolved}`;
}

mod.runChallengeFlowVmSelfTests(assert);

if (failures > 0) {
  console.error(`challengeFlowVm.selftest: ${failures}/${checks} checks FAILED`);
  process.exit(1);
}
console.log(`challengeFlowVm.selftest: ${checks}/${checks} checks passed`);
