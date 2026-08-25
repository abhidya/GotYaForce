// replay-gate.test.mjs — Phase 1 acceptance: the damage-core corpus replay, its
// determinism, and the deliberate-red rehearsal.
// Run: node --test research/decomp/oracle-harness/tests/
//
// Every run here writes into a D:-backed scratch results directory. The tracked
// artifacts under research/decomp/data/oracle-results/ are read-only to this file,
// and one test asserts that explicitly: a rehearsal must never be able to clobber
// real evidence.
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import { createHash } from "node:crypto";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";
import { validateOracleResult } from "../lib/result-integrity.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.join(here, "..");
const runUnit = path.join(harnessDir, "run-unit.mjs");
// result-integrity.mjs no longer exports REPO_ROOT; derive the checkout root the
// same way run-oracle-tests.mjs does (tests -> oracle-harness -> decomp -> research -> root).
const REPO_ROOT = path.resolve(here, "..", "..", "..", "..");
const trackedResults = path.join(REPO_ROOT, "research", "decomp", "data", "oracle-results");
// Scratch placement is explicit: run-oracle-tests.mjs pins it to the checkout drive.
// Fall back to the repo-local .tmp for direct `node --test` runs.
const scratchRoot = process.env.ORACLE_TEST_TMP_ROOT ?? path.join(REPO_ROOT, ".tmp", "oracle-test");

const PASS_LINE = "ORACLE TOTAL functions=4/4 cases=26232 UNEXPLAINED: 0 VERDICT: PASS";
const REPLAY_TIMEOUT_MS = 600_000;

const sha256 = (buf) => createHash("sha256").update(buf).digest("hex");

function runReplay({ dir, env = {} }) {
  const outDir = path.join(scratchRoot, dir);
  fs.rmSync(outDir, { recursive: true, force: true });
  fs.mkdirSync(outDir, { recursive: true });
  const proc = spawnSync(process.execPath, [runUnit, "--unit", "damage-core"], {
    cwd: REPO_ROOT,
    encoding: "utf8",
    timeout: REPLAY_TIMEOUT_MS,
    env: { ...process.env, ORACLE_RESULTS_DIR: outDir, ...env },
  });
  const resultPath = path.join(outDir, "damage-core.json");
  return {
    status: proc.status,
    stdout: proc.stdout ?? "",
    stderr: proc.stderr ?? "",
    resultPath,
    result: fs.existsSync(resultPath) ? JSON.parse(fs.readFileSync(resultPath, "utf8")) : null,
  };
}

/** Result identity modulo the one field that is expected to differ between runs. */
function determinismKey(result) {
  const { generated_at, ...rest } = result;
  return JSON.stringify(rest);
}

test("clean damage-core replay reproduces the pinned gate exactly", { timeout: REPLAY_TIMEOUT_MS }, async () => {
  const run = runReplay({ dir: "clean-1" });
  assert.equal(run.status, 0, `replay must exit 0\n${run.stdout}\n${run.stderr}`);
  assert.ok(run.stdout.includes(PASS_LINE), `missing anchored total line\n${run.stdout}`);

  const r = run.result;
  assert.ok(r, "replay must write a result artifact");
  assert.equal(r.verdict, "pass");
  assert.equal(r.corpus.mode, "replay");
  assert.equal(r.corpus.n, 26232);

  // Gate terms 1-4: the exact per-function splits, not thresholds.
  const expected = {
    zz_003cd5c_: { cases: 20000, exact: 19998, rounding_explained: 2, unexplained: 0 },
    zz_0066298_: { cases: 232, exact: 232, rounding_explained: 0, unexplained: 0 },
    zz_003d344_: { cases: 4000, exact: 4000, rounding_explained: 0, unexplained: 0 },
    FUN_80031634: { cases: 2000, exact: 2000, rounding_explained: 0, unexplained: 0 },
  };
  assert.equal(r.functions.length, 4);
  for (const fn of r.functions) {
    const want = expected[fn.name];
    assert.ok(want, `unexpected function in result: ${fn.name}`);
    assert.equal(fn.verdict, "pass", `${fn.name} must pass`);
    for (const [k, v] of Object.entries(want)) {
      assert.equal(fn[k], v, `${fn.name}.${k}: expected ${v}, got ${fn[k]}`);
    }
  }

  // Gate term 5: coverage clean.
  assert.equal(r.coverage.offsets_read_unwritten, 0);
  assert.equal(r.coverage.sentinel_reads_detected, false);
  assert.deepEqual(r.coverage.stray_writes, []);
  assert.deepEqual(r.coverage.class_mismatches, []);
  assert.deepEqual(r.unexplained_cases, []);
  assert.equal(r.export_coverage.uncovered.length, 0, "damage-core must have full export coverage");

  // A fresh run must validate as current pass coverage against the live checkout.
  // (validateOracleResult recomputes every file-backed identity itself; the per-identity
  // mutation sweep lives in result-integrity.test.mjs.)
  const v = await validateOracleResult(r, { root: REPO_ROOT });
  assert.equal(v.status, "current", JSON.stringify(v.issues));
  assert.equal(v.valid, true);
});

test("two clean replays are byte-identical modulo generated_at", { timeout: REPLAY_TIMEOUT_MS }, () => {
  const a = runReplay({ dir: "det-a" });
  const b = runReplay({ dir: "det-b" });
  assert.equal(a.status, 0, a.stderr);
  assert.equal(b.status, 0, b.stderr);
  assert.equal(
    determinismKey(a.result),
    determinismKey(b.result),
    "two replays of the same inputs must produce identical evidence",
  );
  assert.notEqual(a.result.generated_at, undefined);
});

test("the deliberate-red rehearsal fails loudly and cannot masquerade as a pass", { timeout: REPLAY_TIMEOUT_MS }, async () => {
  // Snapshot the tracked evidence: a rehearsal must not be able to touch it.
  const trackedBefore = fs.readdirSync(trackedResults).sort().map((f) => [
    f,
    sha256(fs.readFileSync(path.join(trackedResults, f))),
  ]);

  // 0x802f2e28 is the category remap table. It must be a byte whose corruption the
  // comparison machinery can actually SEE: the references for zz_003cd5c_ and
  // zz_0066298_ are TS ports that do not read the arena, so a flip there makes the
  // two sides genuinely disagree. Flipping a byte behind a spec-embedded jsRef
  // instead (e.g. FUN_80031634's chTab at 0x802cffc8) corrupts both sides equally
  // and diverges nothing — the run would still "fail", but only because rehearsals
  // are forced to, which would make this test prove nothing about detection.
  const run = runReplay({ dir: "red", env: { ORACLE_FLIP_ARENA_BYTE: "802f2e28" } });

  assert.notEqual(run.status, 0, "a rehearsal must exit nonzero");
  assert.ok(
    run.stdout.includes("DELIBERATE-RED REHEARSAL"),
    `rehearsal must announce itself\n${run.stdout}`,
  );
  assert.ok(!run.stdout.includes("VERDICT: PASS"), "a rehearsal must never print the PASS total line");

  const r = run.result;
  assert.ok(r, "a rehearsal must still write its artifact");
  assert.equal(r.verdict, "fail");
  assert.ok(r.rehearsal, "the artifact must be stamped as a rehearsal");
  assert.equal(r.rehearsal.flip_arena_byte, "0x802f2e28");

  // The point of the rehearsal: the differential machinery DETECTED the corruption
  // on its own, rather than the verdict merely being forced. Assert real divergence
  // in both arena-reading functions, and that the failing cases were recorded for
  // replay — an undiagnosable failure is not evidence.
  const byName = Object.fromEntries(r.functions.map((f) => [f.name, f]));
  for (const name of ["zz_003cd5c_", "zz_0066298_"]) {
    assert.ok(byName[name].unexplained > 0, `${name} must detect the corrupted table`);
    assert.equal(byName[name].verdict, "fail");
  }
  assert.ok(r.unexplained_cases.length > 0, "diverging cases must be recorded for replay");
  // Functions whose reference shares the arena cannot see the flip; they must stay
  // clean, which is what makes the two assertions above meaningful.
  assert.equal(byName.FUN_80031634.unexplained, 0);

  // The stamp alone disqualifies it, even though its identities are current.
  const c = await validateOracleResult(r, { root: REPO_ROOT });
  assert.equal(c.valid, false, "a rehearsal artifact must never count as pass coverage");
  assert.equal(c.status, "rejected", JSON.stringify(c.issues));

  const trackedAfter = fs.readdirSync(trackedResults).sort().map((f) => [
    f,
    sha256(fs.readFileSync(path.join(trackedResults, f))),
  ]);
  assert.deepEqual(trackedAfter, trackedBefore, "a rehearsal must not touch tracked evidence");
});
