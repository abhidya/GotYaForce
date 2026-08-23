import fs from "node:fs";
import path from "node:path";
import { createHash } from "node:crypto";
import { execFileSync } from "node:child_process";
import { pathToFileURL } from "node:url";

const HEX256 = /^[0-9a-f]{64}$/;
const sha256 = (bytes) => createHash("sha256").update(bytes).digest("hex");
const normalizedSha256 = (bytes) => sha256(Buffer.from(bytes.toString("utf8").replace(/\r\n/g, "\n"), "utf8"));

function issue(issues, code, identity, detail) {
  issues.push({ code, identity, detail });
}

function recordedSha(value, identity, issues) {
  if (typeof value !== "string" || !HEX256.test(value)) {
    issue(issues, "missing_identity", identity, `${identity} needs a lowercase SHA-256`);
    return null;
  }
  return value;
}

function compareFile(recorded, file, identity, issues, normalise = false) {
  const want = recordedSha(recorded, identity, issues);
  if (want == null) return;
  if (typeof file !== "string" || !fs.existsSync(file) || !fs.statSync(file).isFile()) {
    issue(issues, "identity_unavailable", identity, `current ${identity} file is unavailable`);
    return;
  }
  const bytes = fs.readFileSync(file);
  const got = normalise ? normalizedSha256(bytes) : sha256(bytes);
  if (got !== want) issue(issues, "identity_mismatch", identity, `recorded ${want}, current ${got}`);
}

function currentRevision(root, issues) {
  try {
    return execFileSync("git", ["rev-parse", "HEAD"], { cwd: root, encoding: "utf8" }).trim();
  } catch {
    issue(issues, "identity_unavailable", "harness_revision", "cannot resolve the current git revision");
    return null;
  }
}

function checkEvidence(result, issues) {
  if (result.verdict !== "pass" || result.rehearsal != null) {
    issue(issues, "nonpass_evidence", "verdict", "only a non-rehearsal pass result can count as current coverage");
    return;
  }
  if (!Array.isArray(result.functions) || result.functions.length === 0
      || result.functions.some((fn) => fn?.verdict !== "pass" || fn?.unexplained !== 0 || !Number.isInteger(fn?.cases) || fn.cases <= 0)) {
    issue(issues, "invalid_evidence", "functions", "pass evidence needs nonempty, passing function records with zero unexplained cases");
  } else {
    const cases = result.functions.reduce((total, fn) => total + fn.cases, 0);
    if (result.corpus?.n !== cases) {
      issue(issues, "identity_mismatch", "corpus", `recorded corpus n=${result.corpus?.n ?? "(missing)"}, function records total ${cases}`);
    }
  }
  const coverage = result.coverage;
  if (coverage == null || coverage.offsets_read_unwritten !== 0
      || coverage.sentinel_reads_detected !== false
      || !Array.isArray(coverage.stray_writes) || coverage.stray_writes.length !== 0
      || (coverage.class_mismatches != null
        && (!Array.isArray(coverage.class_mismatches) || coverage.class_mismatches.length !== 0))) {
    issue(issues, "invalid_evidence", "coverage", "pass evidence needs clean, explicit coverage fields");
  }
  const exports = result.export_coverage;
  if (exports == null || !Number.isInteger(exports.covered) || exports.covered <= 0
      || exports.covered !== exports.exported
      || !Array.isArray(exports.uncovered) || exports.uncovered.length !== 0) {
    issue(issues, "invalid_evidence", "export_coverage", "pass evidence must cover every exported function");
  }
}

/**
 * Validate one oracle result against the current checkout. Result files are
 * evidence, never verdicts: only {valid:true,status:"current"} may count.
 * expectedPaths exists solely for isolated mutation tests; production callers
 * omit it and use paths derived from the current unit spec.
 */
export async function validateOracleResult(result, { root, expectedPaths = {} } = {}) {
  const issues = [];
  if (root == null) throw new TypeError("validateOracleResult requires the checkout root");
  if (result == null || typeof result !== "object" || Array.isArray(result)) {
    return { valid: false, status: "invalid", issues: [{ code: "invalid_evidence", identity: "result", detail: "result must be an object" }] };
  }
  if (result.result_schema !== 1 || typeof result.unit !== "string" || !/^[\w-]+$/.test(result.unit)) {
    issue(issues, "invalid_evidence", "result", "result_schema 1 and a safe unit name are required");
    return { valid: false, status: "invalid", issues };
  }

  const harnessDir = path.join(root, "research", "decomp", "oracle-harness");
  const harnessPath = expectedPaths.harness ?? path.join(harnessDir, "run-unit.mjs");
  const specPath = expectedPaths.spec ?? path.join(harnessDir, "specs", `${result.unit}.spec.mjs`);
  if (!fs.existsSync(specPath)) {
    issue(issues, "identity_unavailable", "spec", "current unit spec is unavailable");
    return { valid: false, status: "invalid", issues };
  }

  let spec;
  try {
    spec = await import(`${pathToFileURL(path.join(harnessDir, "specs", `${result.unit}.spec.mjs`)).href}?integrity=${Date.now()}`);
  } catch (error) {
    issue(issues, "identity_unavailable", "spec", `current unit spec cannot load: ${error.message}`);
    return { valid: false, status: "invalid", issues };
  }
  const meta = spec.meta ?? {};
  const wasmPath = expectedPaths.wasm ?? path.resolve(harnessDir, meta.wasmDefault ?? "");
  const arenaPath = expectedPaths.arena ?? path.resolve(harnessDir, meta.arena ?? "");
  const fieldMapPath = expectedPaths.field_map ?? path.join(harnessDir, "actor-field-map.json");
  const actorPath = expectedPaths.field_map_source ?? path.join(root, "packages", "combat", "src", "rom", "actor.ts");

  compareFile(result.wasm?.sha256, wasmPath, "wasm", issues);
  compareFile(result.spec_sha256, specPath, "spec", issues);
  compareFile(result.arena?.sha256, arenaPath, "arena", issues);
  compareFile(result.field_map?.sha256, fieldMapPath, "field_map", issues);
  compareFile(result.field_map?.source?.sha256, actorPath, "field_map_source", issues, true);
  compareFile(result.harness?.sha256, harnessPath, "harness_content", issues);

  const expectedHarnessEntry = "research/decomp/oracle-harness/run-unit.mjs";
  if (result.harness?.entry !== expectedHarnessEntry) {
    issue(issues, "missing_identity", "harness_entry", `harness entry must be ${expectedHarnessEntry}`);
  }
  const recordedRevision = result.harness?.git_rev;
  if (typeof recordedRevision !== "string" || !/^[0-9a-f]{40}$/.test(recordedRevision)) {
    issue(issues, "missing_identity", "harness_revision", "harness git revision must be a full commit SHA");
  } else {
    const revision = currentRevision(root, issues);
    if (revision != null && revision !== recordedRevision) {
      issue(issues, "identity_mismatch", "harness_revision", `recorded ${recordedRevision}, current ${revision}`);
    }
  }

  const mapSource = result.field_map?.source;
  if (result.field_map?.path !== "research/decomp/oracle-harness/actor-field-map.json") {
    issue(issues, "missing_identity", "field_map_path", "canonical field-map path is required");
  }
  if (mapSource?.path !== "packages/combat/src/rom/actor.ts") {
    issue(issues, "missing_identity", "field_map_source_path", "canonical field-map source path is required");
  }
  try {
    const fieldMap = JSON.parse(fs.readFileSync(fieldMapPath, "utf8"));
    const actorSha = normalizedSha256(fs.readFileSync(actorPath));
    if (fieldMap.source !== "packages/combat/src/rom/actor.ts"
        || fieldMap.source_sha256 !== actorSha) {
      issue(issues, "identity_mismatch", "field_map_source_binding", "current field map is not bound to the current normalized actor.ts source");
    }
  } catch (error) {
    issue(issues, "identity_unavailable", "field_map", `current field map cannot be checked: ${error.message}`);
  }

  const corpusMode = meta.corpus?.mode ?? "replay";
  if (result.corpus?.mode == null) {
    issue(issues, "missing_identity", "corpus", "corpus mode and identity are required");
  } else if (result.corpus.mode !== corpusMode) {
    issue(issues, "identity_mismatch", "corpus", `recorded mode ${result.corpus?.mode ?? "(missing)"}, current mode ${corpusMode}`);
  } else if (corpusMode === "replay") {
    const corpusPath = expectedPaths.corpus ?? path.resolve(harnessDir, meta.fixture ?? "");
    compareFile(result.corpus?.sha256, corpusPath, "corpus", issues);
  } else if (corpusMode === "generate") {
    if (!Number.isInteger(result.corpus?.seed) || !Number.isInteger(result.corpus?.n) || result.corpus.n <= 0) {
      issue(issues, "missing_identity", "corpus", "generated corpus needs integer seed and positive n");
    } else if ((result.corpus.seed >>> 0) !== (meta.corpus.seed >>> 0)) {
      issue(issues, "identity_mismatch", "corpus", "generated corpus seed no longer matches the current spec");
    }
  }

  checkEvidence(result, issues);
  const status = issues.some((entry) => entry.code === "identity_mismatch") ? "superseded"
    : issues.some((entry) => entry.code === "missing_identity" || entry.code === "identity_unavailable" || entry.code === "invalid_evidence") ? "invalid"
    : issues.some((entry) => entry.code === "nonpass_evidence") ? "rejected"
    : "current";
  return { valid: status === "current", status, issues };
}
