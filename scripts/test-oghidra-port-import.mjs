import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";

import {
  deriveBoundaryScenarios,
  verifyGeneratedCandidate,
} from "./lib/oghidra-port-auto-verify.mjs";
import {
  extractEagleJetFacts,
  importArtifact,
  validateArtifact,
} from "./lib/oghidra-port-import.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const fixture = path.join(root, "scripts", "fixtures", "oghidra-eagle-jet-artifact.json");
const testTempRoot = path.join(root, ".tmp", "oghidra-import-tests");
fs.mkdirSync(testTempRoot, { recursive: true });

function makeTemp(prefix) {
  return fs.mkdtempSync(path.join(testTempRoot, prefix));
}

test("artifact schema validation rejects unnormalized addresses", () => {
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  payload.function.address = "8012B458";
  assert.match(validateArtifact(payload).join("\n"), /normalized lowercase/);
});

test("Eagle Jet facts are recovered from verified claims", () => {
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  assert.deepEqual(Object.values(extractEagleJetFacts(payload)), Array(12).fill(true));
});

test("authoritative evidence cannot replace missing Qwen mechanics", () => {
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  payload.port_ir = null;
  for (const claim of payload.analysis.claims) {
    claim.value = {};
  }

  assert.deepEqual(Object.values(extractEagleJetFacts(payload)), Array(12).fill(false));
});

test("complete artifact generates, compiles, and verifies without handwritten scenarios", async () => {
  const temp = makeTemp("oghidra-import-");
  const generated = path.join(temp, "fn_8012b458.generated.ts");
  const report = path.join(temp, "8012b458-import-report.md");
  const verification = path.join(temp, "8012b458-auto-verification.json");
  const result = importArtifact({
    artifactPath: fixture,
    generatedPath: generated,
    reportPath: report,
  });
  assert.equal(result.fallback, false);
  assert.match(fs.readFileSync(generated, "utf8"), /actor\.timer = 45\.0/);
  assert.match(fs.readFileSync(generated, "utf8"), /actor\.cooldown = 0x10 \+ actor\.dt/);
  assert.match(fs.readFileSync(generated, "utf8"), /actor\.controlWord &= 0xfffffffc/);
  assert.match(fs.readFileSync(generated, "utf8"), /dispatchFullBodyCue\(actor, 0x1b\)/);
  assert.match(
    fs.readFileSync(report, "utf8"),
    /Production registration remains unchanged until automatic compile/,
  );

  const automatic = await verifyGeneratedCandidate({
    root,
    artifactPath: fixture,
    generatedPath: generated,
    verificationPath: verification,
    fallback: result.fallback,
  });
  assert.equal(automatic.compile.passed, true);
  assert.equal(automatic.handwritten_scenarios, 0);
  assert.equal(automatic.scenario_source, "artifact-boundary-matrix");
  assert.equal(automatic.behavior.failed, 0);
  assert.ok(automatic.behavior.scenarios.length > 0);
  assert.equal(automatic.status, "passed");
});

test("boundary scenarios are derived from artifact branches and timer comparisons", () => {
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  const scenarios = deriveBoundaryScenarios(payload);
  assert.ok(scenarios.length > 0);
  assert.ok(scenarios.every((scenario) => scenario.source === "artifact-boundary-matrix"));
  assert.ok(scenarios.some((scenario) => scenario.input.phase === 0));
  assert.ok(scenarios.some((scenario) => scenario.id.includes("above")));
  assert.ok(scenarios.some((scenario) => scenario.id.includes("exact")));
  assert.ok(scenarios.some((scenario) => scenario.id.includes("below")));
});

test("automatic behavior verification rejects a compiling semantic mutation", async () => {
  const temp = makeTemp("oghidra-mutation-");
  const generated = path.join(temp, "fn_8012b458.generated.ts");
  const report = path.join(temp, "8012b458-import-report.md");
  const result = importArtifact({
    artifactPath: fixture,
    generatedPath: generated,
    reportPath: report,
  });
  const mutated = fs.readFileSync(generated, "utf8").replace(
    "actor.effectMode = 0x83;",
    "actor.effectMode = 0x82;",
  );
  fs.writeFileSync(generated, mutated, "utf8");
  const automatic = await verifyGeneratedCandidate({
    root,
    artifactPath: fixture,
    generatedPath: generated,
    verificationPath: path.join(temp, "mutation-verification.json"),
    fallback: result.fallback,
  });
  assert.equal(automatic.compile.passed, true);
  assert.ok(automatic.behavior.failed > 0);
  assert.equal(automatic.status, "failed");
});

test("unresolved dependency emits an explicit generic fallback", () => {
  const temp = makeTemp("oghidra-fallback-");
  const artifact = path.join(temp, "artifact.json");
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  payload.analysis.dependencies[0].status = "unsupported";
  fs.writeFileSync(artifact, JSON.stringify(payload), "utf8");
  const generated = path.join(temp, "fallback.generated.ts");
  const result = importArtifact({
    artifactPath: artifact,
    generatedPath: generated,
    reportPath: path.join(temp, "report.md"),
  });
  assert.equal(result.fallback, true);
  assert.match(fs.readFileSync(generated, "utf8"), /return false/);
  assert.match(result.blockers.join("\n"), /unsupported/);
});

test("partially verified failed artifact is reportable but always falls back", () => {
  const temp = makeTemp("oghidra-partial-");
  const artifact = path.join(temp, "artifact.json");
  const payload = JSON.parse(fs.readFileSync(fixture, "utf8"));
  payload.verification.status = "failed";
  payload.verification.integration_status = "blocked";
  payload.analysis.claims[0].verification = "rejected";
  fs.writeFileSync(artifact, JSON.stringify(payload), "utf8");
  const generated = path.join(temp, "fallback.generated.ts");
  const result = importArtifact({
    artifactPath: artifact,
    generatedPath: generated,
    reportPath: path.join(temp, "report.md"),
  });
  assert.equal(validateArtifact(payload).length, 0);
  assert.equal(result.fallback, true);
  assert.match(fs.readFileSync(generated, "utf8"), /return false/);
  assert.match(result.blockers.join("\n"), /artifact verification status is failed/);
});

test("changed generated output is not overwritten without force", () => {
  const temp = makeTemp("oghidra-overwrite-");
  const generated = path.join(temp, "candidate.ts");
  const report = path.join(temp, "report.md");
  fs.writeFileSync(generated, "user edit", "utf8");
  assert.throws(
    () => importArtifact({ artifactPath: fixture, generatedPath: generated, reportPath: report }),
    /refusing to overwrite/,
  );
  assert.equal(fs.readFileSync(generated, "utf8"), "user edit");
});
