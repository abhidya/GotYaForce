import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import { createHash } from "node:crypto";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";
import { validateOracleResult } from "../lib/result-integrity.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.resolve(here, "..");
const root = path.resolve(harnessDir, "..", "..", "..");
const scratchRoot = process.env.ORACLE_TEST_TMP_ROOT;
assert.ok(scratchRoot, "run through pnpm test:oracle so scratch placement is explicit");
assert.equal(path.parse(scratchRoot).root, path.parse(root).root, "scratch must share the checkout drive");

function scratch(name) {
  const dir = path.join(scratchRoot, name);
  fs.mkdirSync(dir, { recursive: true });
  return dir;
}

function runDamage(name, extraEnv = {}) {
  const outDir = scratch(name);
  const run = spawnSync(process.execPath, ["run-unit.mjs", "--unit", "damage-core"], {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: outDir, ...extraEnv },
    encoding: "utf8",
  });
  return { run, outDir, resultPath: path.join(outDir, "damage-core.json") };
}

function readJson(file) {
  return JSON.parse(fs.readFileSync(file, "utf8"));
}

test("missing identity fails closed", async () => {
  const verdict = await validateOracleResult({
    result_schema: 1,
    unit: "damage-core",
    verdict: "pass",
  }, { root });
  assert.equal(verdict.valid, false);
  assert.equal(verdict.status, "invalid");
  assert.ok(verdict.issues.some((issue) => issue.code === "missing_identity"));
});

const ISSUE_CODES = new Set([
  "missing_identity",
  "identity_unavailable",
  "identity_mismatch",
  "invalid_evidence",
  "nonpass_evidence",
]);

// The two tracked pilot results are provenance, not coverage. This asserts the
// invariant -- a committed result file never counts on the strength of what it
// records -- and deliberately does NOT pin *which* identity is stale.
//
// The previous version asserted `identity_mismatch` on identity `wasm`
// specifically. That is a supersession *reason*, not the invariant: the port
// driver legitimately rebuilds one of these units and refreshes its result, at
// which point `wasm` agrees again and the drift moves to `spec`, `corpus` or
// `harness_revision` -- or the refusal moves to `nonpass_evidence` outright.
// CI then went red on a routine driver commit rather than on a defect.
//
// Non-vacuity: this cannot pass by the validator simply refusing everything --
// "clean damage-core replay is current" below asserts the same validator
// returns {valid:true,status:"current"} for freshly generated evidence.
test("tracked pilot results never count as current coverage", async () => {
  for (const unit of ["auto-c0034-018", "auto-c0035-002"]) {
    const resultPath = path.join(root, "research", "decomp", "data", "oracle-results", `${unit}.json`);
    const result = readJson(resultPath);

    // Guard the premise rather than the reason. These are pilot units whose
    // recorded evidence is non-passing, so no amount of identity freshness may
    // promote them. If the driver ever lands a genuine `pass` here, this fires
    // first and says so, instead of failing on an opaque reason mismatch.
    assert.notEqual(result.verdict, "pass", `${unit}: tracked pilot result now records a pass; revisit this test`);

    const verdict = await validateOracleResult(result, { root });
    assert.equal(verdict.valid, false, unit);
    assert.notEqual(verdict.status, "current", unit);
    assert.ok(verdict.issues.length > 0, `${unit}: a refusal must name at least one reason`);
    for (const issue of verdict.issues) {
      assert.ok(ISSUE_CODES.has(issue.code), `${unit}: unknown issue code ${issue.code}`);
      assert.equal(typeof issue.identity, "string", `${unit}: issue ${issue.code} must name an identity`);
    }
  }
});

test("tracked historical damage result does not count by file presence", async () => {
  const resultPath = path.join(root, "research", "decomp", "data", "oracle-results", "damage-core.json");
  const verdict = await validateOracleResult(readJson(resultPath), { root });
  assert.equal(verdict.valid, false);
  assert.equal(verdict.status, "superseded");
  assert.ok(verdict.issues.some((issue) => issue.identity === "harness_revision"));
});

test("clean damage-core replay is current and reproduces the exact Phase-1 gate", async () => {
  const { run, resultPath } = runDamage("clean");
  const log = (run.stdout ?? "") + (run.stderr ?? "");
  assert.equal(run.status, 0, log);
  const result = readJson(resultPath);
  assert.equal(result.verdict, "pass");
  assert.deepEqual(result.export_coverage, { covered: 4, exported: 4, uncovered: [] });
  assert.equal(result.functions.reduce((n, f) => n + f.cases, 0), 26232);
  assert.equal(result.functions.reduce((n, f) => n + f.unexplained, 0), 0);
  assert.deepEqual(result.functions.map(({ name, cases, exact, rounding_explained, unexplained }) =>
    ({ name, cases, exact, rounding_explained, unexplained })), [
    { name: "zz_003cd5c_", cases: 20000, exact: 19998, rounding_explained: 2, unexplained: 0 },
    { name: "zz_0066298_", cases: 232, exact: 232, rounding_explained: 0, unexplained: 0 },
    { name: "zz_003d344_", cases: 4000, exact: 4000, rounding_explained: 0, unexplained: 0 },
    { name: "FUN_80031634", cases: 2000, exact: 2000, rounding_explained: 0, unexplained: 0 },
  ]);
  const verdict = await validateOracleResult(result, { root });
  assert.deepEqual(verdict, { valid: true, status: "current", issues: [] });
});

test("every file-backed identity supersedes fresh evidence after a byte change", async () => {
  const { run, resultPath } = runDamage("mutation-source");
  assert.equal(run.status, 0, (run.stdout ?? "") + (run.stderr ?? ""));
  const result = readJson(resultPath);
  const canonical = [
    ["wasm", "wasm", path.join(root, "research", "decomp", "port-units", "damage-core", "unit.wasm")],
    ["spec", "spec", path.join(harnessDir, "specs", "damage-core.spec.mjs")],
    ["corpus", "corpus", path.join(harnessDir, "corpora", "damage-core-poc.jsonl")],
    ["arena", "arena", path.join(root, "research", "decomp", "poc", "wasm-port-poc", "arena.json")],
    ["field_map", "field_map", path.join(harnessDir, "actor-field-map.json")],
    ["field_map_source", "field_map_source", path.join(root, "packages", "combat", "src", "rom", "actor.ts")],
    ["harness", "harness_content", path.join(harnessDir, "run-unit.mjs")],
  ];
  for (const [override, identity, source] of canonical) {
    const copy = path.join(scratch(`mutated-${override}`), path.basename(source));
    const bytes = fs.readFileSync(source);
    bytes[Math.floor(bytes.length / 2)] ^= 0xff;
    fs.writeFileSync(copy, bytes);
    const verdict = await validateOracleResult(result, {
      root,
      expectedPaths: { [override]: copy },
    });
    assert.equal(verdict.valid, false, identity);
    assert.equal(verdict.status, "superseded", identity);
    assert.ok(verdict.issues.some((issue) => issue.code === "identity_mismatch" && issue.identity === identity), identity);
  }
});

test("field-map source binding and harness revision are independently enforced", async () => {
  const { run, resultPath } = runDamage("binding-source");
  assert.equal(run.status, 0, (run.stdout ?? "") + (run.stderr ?? ""));
  const result = readJson(resultPath);

  const actorCopy = path.join(scratch("actor-binding"), "actor.ts");
  const actorBytes = fs.readFileSync(path.join(root, "packages", "combat", "src", "rom", "actor.ts"));
  actorBytes[Math.floor(actorBytes.length / 2)] ^= 0x01;
  fs.writeFileSync(actorCopy, actorBytes);
  const forged = structuredClone(result);
  forged.field_map.source.sha256 = createHash("sha256")
    .update(Buffer.from(actorBytes.toString("utf8").replace(/\r\n/g, "\n"), "utf8"))
    .digest("hex");
  const sourceVerdict = await validateOracleResult(forged, {
    root,
    expectedPaths: { field_map_source: actorCopy },
  });
  assert.equal(sourceVerdict.valid, false);
  assert.ok(sourceVerdict.issues.some((issue) => issue.identity === "field_map_source_binding"));

  const oldRevision = structuredClone(result);
  oldRevision.harness.git_rev = "0".repeat(40);
  const revisionVerdict = await validateOracleResult(oldRevision, { root });
  assert.equal(revisionVerdict.status, "superseded");
  assert.ok(revisionVerdict.issues.some((issue) => issue.identity === "harness_revision"));
});

test("recorded corpus count must agree with the evidence counts", async () => {
  const { run, resultPath } = runDamage("corpus-count");
  assert.equal(run.status, 0, (run.stdout ?? "") + (run.stderr ?? ""));
  const result = readJson(resultPath);
  result.corpus.n++;
  const verdict = await validateOracleResult(result, { root });
  assert.equal(verdict.valid, false);
  assert.ok(verdict.issues.some((issue) => issue.identity === "corpus"));
});

test("two clean results are identical modulo generated_at", () => {
  const a = runDamage("determinism-a");
  const b = runDamage("determinism-b");
  assert.equal(a.run.status, 0, (a.run.stdout ?? "") + (a.run.stderr ?? ""));
  assert.equal(b.run.status, 0, (b.run.stdout ?? "") + (b.run.stderr ?? ""));
  const ar = readJson(a.resultPath);
  const br = readJson(b.resultPath);
  delete ar.generated_at;
  delete br.generated_at;
  assert.deepEqual(ar, br);
});

test("deliberate-red is nonzero and produces rejected, unmistakable evidence", async () => {
  const { run, resultPath } = runDamage("deliberate-red", { ORACLE_FLIP_ARENA_BYTE: "804335e0" });
  const log = (run.stdout ?? "") + (run.stderr ?? "");
  assert.notEqual(run.status, 0, log);
  const result = readJson(resultPath);
  assert.equal(result.verdict, "fail");
  assert.equal(result.rehearsal.flip_arena_byte, "0x804335e0");
  const verdict = await validateOracleResult(result, { root });
  assert.equal(verdict.valid, false);
  assert.equal(verdict.status, "rejected");
  assert.ok(verdict.issues.some((issue) => issue.code === "nonpass_evidence"));
});
