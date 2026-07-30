import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { spawnSync } from "node:child_process";
import { pathToFileURL } from "node:url";

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
const checkedInCandidate = path.join(
  root,
  "packages",
  "combat",
  "src",
  "generated",
  "oghidra",
  "fn_8012b458.generated.ts",
);

const artifact = JSON.parse(fs.readFileSync(artifactPath, "utf8"));
const validation = JSON.parse(fs.readFileSync(validationPath, "utf8"));
assert.equal(artifact.function.address, "0x8012b458");
assert.equal(artifact.producer.model_provider, "custom_api");
assert.match(artifact.producer.model_name, /Qwen3\.6-35B-A3B/);
assert.equal(artifact.verification.status, "verified");
assert.equal(
  artifact.verification.checks.length,
  4 + (artifact.analysis.claims.length * 3),
);
assert.ok(artifact.verification.checks.every((check) => check.passed));
assert.ok(artifact.analysis.claims.every((claim) => claim.verification === "verified"));
assert.equal(validation.passed, true);
assert.equal(validation.checks_failed, 0);
assert.ok(validation.claim_prunings.some((claim) =>
  claim.claim_id === "claim:init_byte_write"
  && claim.value.includes('"value": 0')));

const tempRoot = path.join(root, ".tmp", "oghidra-live-verify");
fs.mkdirSync(tempRoot, { recursive: true });
const temp = fs.mkdtempSync(path.join(tempRoot, "run-"));
const generated = path.join(temp, "fn_8012b458.generated.ts");
const report = path.join(temp, "import-report.md");
const imported = importArtifact({
  artifactPath,
  generatedPath: generated,
  reportPath: report,
  force: true,
});
assert.equal(imported.fallback, false);
assert.deepEqual(Object.values(imported.facts), Array(12).fill(true));
assert.deepEqual(imported.blockers, []);
assert.equal(fs.readFileSync(generated, "utf8"), fs.readFileSync(checkedInCandidate, "utf8"));

const outDir = path.join(temp, "out");
const tsc = spawnSync(
  process.execPath,
  [
    path.join(root, "node_modules", "typescript", "bin", "tsc"),
    "--target", "ES2022",
    "--module", "ES2022",
    "--moduleResolution", "Bundler",
    "--outDir", outDir,
    generated,
  ],
  { encoding: "utf8" },
);
assert.equal(tsc.status, 0, `${tsc.stdout}\n${tsc.stderr}`);

const generatedModule = await import(
  `${pathToFileURL(path.join(outDir, "fn_8012b458.generated.js")).href}?run=${Date.now()}`
);
const generatedStep = generatedModule.tryStepFun8012b458;
assert.equal(typeof generatedStep, "function");

function referenceStep(actor, host) {
  actor.effectMode = 0x83;
  if (actor.phase === 0) {
    actor.phase = 1;
    actor.timer = 45.0;
    host.retireHitbox(actor, 0x7F);
    host.playCue(actor, 0x20);
    if (actor.borgNumber === 0x607) {
      host.preparePart(actor, 1, 0);
      host.preparePart(actor, 2, 0);
    } else if (actor.borgNumber === 0x61B) {
      host.preparePart(actor, 4, 0);
      host.preparePart(actor, 5, 0);
    }
    return true;
  }
  actor.timer -= actor.dt;
  if (actor.timer <= 0) {
    actor.cooldown = 0x10 + actor.dt;
    actor.housekeeping = 0;
    actor.controlWord &= 0xFFFFFFFC;
    host.dispatchFullBodyCue(actor, 0x1B);
  }
  return true;
}

function run(step, initial) {
  const actor = structuredClone(initial);
  const events = [];
  const host = {
    retireHitbox(_actor, kind) {
      events.push(["retireHitbox", kind]);
    },
    playCue(_actor, cue) {
      events.push(["playCue", cue]);
    },
    preparePart(_actor, slot, value) {
      events.push(["preparePart", slot, value]);
    },
    dispatchFullBodyCue(_actor, cue) {
      events.push(["dispatchFullBodyCue", cue]);
    },
  };
  const handled = step(actor, host);
  return { handled, actor, events };
}

const scenarios = [
  {
    name: "initialize Eagle Jet 0x61b",
    actor: {
      borgNumber: 0x61B,
      phase: 0,
      timer: 99,
      dt: 1,
      effectMode: 0,
      cooldown: 0,
      housekeeping: 7,
      controlWord: 0xFFFFFFFF,
    },
  },
  {
    name: "initialize sibling 0x607 part route",
    actor: {
      borgNumber: 0x607,
      phase: 0,
      timer: 0,
      dt: 0.5,
      effectMode: 0,
      cooldown: 0,
      housekeeping: 1,
      controlWord: 7,
    },
  },
  {
    name: "decrement active timer without exit",
    actor: {
      borgNumber: 0x61B,
      phase: 1,
      timer: 10,
      dt: 1,
      effectMode: 0,
      cooldown: 3,
      housekeeping: 4,
      controlWord: 7,
    },
  },
  {
    name: "expire timer and run exact cleanup",
    actor: {
      borgNumber: 0x61B,
      phase: 1,
      timer: 0.5,
      dt: 1,
      effectMode: 0,
      cooldown: 0,
      housekeeping: 9,
      controlWord: 0xFFFFFFFF,
    },
  },
  {
    name: "exact zero boundary exits",
    actor: {
      borgNumber: 0x61B,
      phase: 1,
      timer: 1,
      dt: 1,
      effectMode: 0,
      cooldown: 0,
      housekeeping: 9,
      controlWord: 3,
    },
  },
];

for (const scenario of scenarios) {
  assert.deepEqual(
    run(generatedStep, scenario.actor),
    run(referenceStep, scenario.actor),
    scenario.name,
  );
}

process.stdout.write(`${JSON.stringify({
  artifact: artifactPath,
  model: artifact.producer.model_name,
  artifactChecks: artifact.verification.checks.length,
  recoveredFacts: Object.keys(imported.facts).length,
  scenarios: scenarios.map((scenario) => scenario.name),
  result: "PASS",
}, null, 2)}\n`);
