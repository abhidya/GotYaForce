// result-integrity.test.mjs — Phase 1 evidence-integrity gate.
// Run: node --test research/decomp/oracle-harness/tests/
//
// The property under test: a tracked result JSON counts as current pass coverage
// ONLY while every identity it recorded still recomputes against the working tree.
// File presence is never a verdict.
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import {
  validateResult,
  validateResultFile,
  countsAsPassCoverage,
  resolveRecordedPath,
  REPO_ROOT,
} from "../lib/result-integrity.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const resultsDir = path.join(REPO_ROOT, "research", "decomp", "data", "oracle-results");
const readResult = (unit) => JSON.parse(fs.readFileSync(path.join(resultsDir, `${unit}.json`), "utf8"));
const clone = (o) => JSON.parse(JSON.stringify(o));

// A hex sha with one nibble changed — "one byte flipped" in the recorded identity.
function flipSha(sha) {
  const last = sha.slice(-1);
  return sha.slice(0, -1) + (last === "0" ? "1" : "0");
}

test("tracked damage-core evidence validates against the working tree", () => {
  const v = validateResultFile(path.join(resultsDir, "damage-core.json"));
  assert.equal(v.status, "current", `damage-core evidence must validate; reasons: ${v.reasons.join(" | ")}`);
  // The three identities every damage-core result carries must actually have been
  // recomputed — a validator that silently checked nothing would also say "current".
  for (const id of ["wasm", "spec", "corpus"]) {
    assert.ok(v.checked.includes(id), `expected identity '${id}' to be recomputed, got [${v.checked}]`);
  }
});

test("damage-core counts as current pass coverage", () => {
  const c = countsAsPassCoverage(readResult("damage-core"));
  assert.equal(c.ok, true, c.reasons.join(" | "));
});

test("the two stale pilot results are rejected as superseded", () => {
  for (const unit of ["auto-c0034-018", "auto-c0035-002"]) {
    const v = validateResultFile(path.join(resultsDir, `${unit}.json`));
    assert.equal(v.status, "superseded", `${unit} must not count: got ${v.status}`);
    assert.ok(
      v.reasons.some((r) => r.startsWith("wasm rebuilt")),
      `${unit} should be superseded by its rebuilt wasm, got: ${v.reasons.join(" | ")}`,
    );
    assert.equal(countsAsPassCoverage(readResult(unit)).ok, false);
  }
});

test("flipping one byte of any recorded identity yields superseded", () => {
  const base = readResult("damage-core");
  assert.equal(validateResult(base).status, "current");

  const mutations = {
    wasm: (r) => { r.wasm.sha256 = flipSha(r.wasm.sha256); },
    spec: (r) => { r.spec_sha256 = flipSha(r.spec_sha256); },
    corpus: (r) => { r.corpus.sha256 = flipSha(r.corpus.sha256); },
    field_map: (r) => {
      r.field_map = {
        path: "research/decomp/oracle-harness/actor-field-map.json",
        sha256: "0".repeat(64),
        source_sha256: "0".repeat(64),
      };
    },
    harness: (r) => {
      r.harness = { ...r.harness, sha256: "0".repeat(64) };
    },
  };

  for (const [name, mutate] of Object.entries(mutations)) {
    const r = clone(base);
    mutate(r);
    const v = validateResult(r);
    assert.equal(v.status, "superseded", `${name} drift must supersede, got ${v.status}`);
    assert.equal(countsAsPassCoverage(r).ok, false, `${name} drift must not count as pass coverage`);
  }
});

test("missing or malformed identities fail closed as invalid", () => {
  const base = readResult("damage-core");
  const cases = {
    "no wasm block": (r) => { delete r.wasm; r.spec_sha256 = "x".repeat(64); },
    "no wasm sha": (r) => { delete r.wasm.sha256; },
    "no spec sha": (r) => { delete r.spec_sha256; },
    "no corpus block": (r) => { delete r.corpus; },
    "replay corpus without sha": (r) => { delete r.corpus.sha256; },
    "unknown corpus mode": (r) => { r.corpus = { mode: "telepathy" }; },
    "generate corpus without seed": (r) => { r.corpus = { mode: "generate", n: 10 }; },
    "unknown schema": (r) => { r.result_schema = 2; },
    "unknown verdict": (r) => { r.verdict = "probably fine"; },
    "malformed field_map": (r) => { r.field_map = { sha256: 12 }; },
    "unreadable wasm path": (r) => { r.wasm.path = "research/decomp/port-units/no-such-unit/unit.wasm"; },
  };
  for (const [name, mutate] of Object.entries(cases)) {
    const r = clone(base);
    mutate(r);
    const v = validateResult(r);
    assert.equal(v.status, "invalid", `${name}: expected invalid, got ${v.status} (${v.reasons.join(" | ")})`);
    assert.equal(countsAsPassCoverage(r).ok, false);
  }
});

test("a result file that does not exist is invalid, not absent", () => {
  const v = validateResultFile(path.join(resultsDir, "no-such-unit.json"));
  assert.equal(v.status, "invalid");
});

test("malformed JSON is invalid rather than throwing", () => {
  const p = path.join(here, "..", "..", "..", "..", ".tmp", "oracle-test-malformed.json");
  fs.mkdirSync(path.dirname(p), { recursive: true });
  fs.writeFileSync(p, "{ not json");
  try {
    assert.equal(validateResultFile(p).status, "invalid");
  } finally {
    fs.rmSync(p, { force: true });
  }
});

test("a rehearsal-stamped pass never counts as coverage", () => {
  const r = readResult("damage-core");
  assert.equal(countsAsPassCoverage(r).ok, true);
  r.rehearsal = { flip_arena_byte: "0x0", note: "deliberate-red rehearsal" };
  const c = countsAsPassCoverage(r);
  assert.equal(c.ok, false, "a rehearsal artifact must never be mistaken for a verdict");
  // It is the rehearsal stamp doing the work here, not stale evidence.
  assert.equal(c.status, "current");
});

test("a non-pass verdict with current evidence is still not pass coverage", () => {
  for (const verdict of ["fail", "partial", "blocked_codec"]) {
    const r = readResult("damage-core");
    r.verdict = verdict;
    const c = countsAsPassCoverage(r);
    assert.equal(c.status, "current", "evidence is current; only the verdict differs");
    assert.equal(c.ok, false, `${verdict} must not count as pass coverage`);
  }
});

test("a crash stub carries no identities and can never be current", () => {
  const v = validateResult({
    result_schema: 1,
    unit: "damage-core",
    generated_at: "2026-01-01T00:00:00.000Z",
    verdict: "blocked_codec",
    detail: "codec blocked",
  });
  assert.equal(v.status, "superseded");
  assert.deepEqual(v.checked, []);
});

test("recorded absolute paths from a foreign checkout re-anchor to this root", () => {
  const foreign = "C:\\\\somewhere\\\\else\\\\research\\\\decomp\\\\port-units\\\\damage-core\\\\unit.wasm";
  const resolved = resolveRecordedPath(foreign);
  assert.ok(resolved, "a foreign absolute path must re-anchor by its repo-relative suffix");
  assert.ok(fs.existsSync(resolved));

  const r = readResult("damage-core");
  r.wasm.path = foreign;
  assert.equal(validateResult(r).status, "current", "re-anchoring must keep a clean checkout valid");
});

test("non-object and unresolvable inputs are handled without throwing", () => {
  assert.equal(validateResult(null).status, "invalid");
  assert.equal(validateResult([]).status, "invalid");
  assert.equal(validateResult("nope").status, "invalid");
  assert.equal(resolveRecordedPath(""), null);
  assert.equal(resolveRecordedPath(undefined), null);
  assert.equal(resolveRecordedPath("/no/anchor/here.wasm"), null);
});
