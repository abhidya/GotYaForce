import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";

import {
  appendAutomaticVerification,
  verifyGeneratedCandidate,
} from "./lib/oghidra-port-auto-verify.mjs";
import { importArtifact } from "./lib/oghidra-port-import.mjs";

const root = path.resolve(import.meta.dirname, "..");
const artifactPath = path.join(root, "research", "decomp", "generated", "8012b458.port.json");
const validationPath = path.join(
  root,
  "research",
  "decomp",
  "generated",
  "8012b458.port.validation.json",
);
const generatedPath = path.join(
  root,
  "packages",
  "combat",
  "src",
  "generated",
  "oghidra",
  "fn_8012b458.generated.ts",
);
const reportPath = path.join(
  root,
  "research",
  "decomp",
  "generated",
  "8012b458-import-report.md",
);
const automaticVerificationPath = path.join(
  root,
  "research",
  "decomp",
  "generated",
  "8012b458-auto-verification.json",
);

const artifact = JSON.parse(fs.readFileSync(artifactPath, "utf8"));
const validation = JSON.parse(fs.readFileSync(validationPath, "utf8"));
assert.equal(validation.passed, true);
assert.equal(validation.checks_failed, 0);

const imported = importArtifact({
  artifactPath,
  generatedPath,
  reportPath,
  force: true,
});
assert.equal(imported.fallback, false);

const automatic = await verifyGeneratedCandidate({
  root,
  artifactPath,
  generatedPath,
  verificationPath: automaticVerificationPath,
  fallback: imported.fallback,
});
appendAutomaticVerification(
  reportPath,
  path.relative(root, automaticVerificationPath).replaceAll("\\", "/"),
  automatic,
);
assert.equal(automatic.compile.passed, true);
assert.equal(automatic.behavior.failed, 0);
assert.ok(automatic.behavior.scenarios.length > 0);
assert.equal(automatic.handwritten_scenarios, 0);
assert.equal(automatic.status, "passed");

process.stdout.write(`${JSON.stringify({
  artifact: artifactPath,
  model: artifact.producer.model_name,
  artifactChecks: artifact.verification.checks.length,
  recoveredFacts: Object.keys(imported.facts).length,
  generatedCandidate: generatedPath,
  automaticVerification: automaticVerificationPath,
  compilation: "PASS",
  scenarioSource: automatic.scenario_source,
  handwrittenScenarios: automatic.handwritten_scenarios,
  scenarios: automatic.behavior.scenarios.length,
  scenariosPassed: automatic.behavior.passed,
  independentOracle: automatic.oracle,
  result: "PASS",
}, null, 2)}\n`);
