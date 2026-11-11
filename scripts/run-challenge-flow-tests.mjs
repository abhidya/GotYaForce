#!/usr/bin/env node
// Runs Challenge VM self-tests against the real generated table dependency graph.
// apps/game is noEmit, so emit isolated ESM modules without requiring a previous build.
//
//   node scripts/run-challenge-flow-tests.mjs
import path from "node:path";
import { fileURLToPath } from "node:url";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const graph = emitInlineModuleGraph({
  label: "challenge-flow-selftest",
  entry: path.join(root, "apps/game/src/ui/intro/challengeFlowVm.ts"),
  outDir: path.join(root, ".tmp/challenge-flow-selftest"),
  packages: {
    "@gf/missions": path.join(root, "packages/missions/src/challenge-spawn-pools.generated.ts"),
  },
});
const mod = await import(graph.url);

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

mod.runChallengeFlowVmSelfTests(assert);

if (failures > 0) {
  console.error(`challengeFlowVm.selftest: ${failures}/${checks} checks FAILED`);
  process.exit(1);
}
console.log(`challengeFlowVm.selftest: ${checks}/${checks} checks passed`);
