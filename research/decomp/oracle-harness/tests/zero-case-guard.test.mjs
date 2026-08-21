// zero-case-guard.test.mjs — P2 pilot review P1: the zero-case pass hole.
//
// Before the guard, a spec could list every export (satisfying the coverage
// self-audit) while routing 0 cases to some function — its per-function counters
// would read 0/0/0, verdict "pass", and the run could print PASS / exit 0 having
// proven nothing about that function. The guard: any covered function with
// cases below its floor (spec min_cases, default 1) is forced to
// fail_min_cases, which fails the run.
//
// Demonstration uses the committed auto-c0035-002 spec with --n 1: the generator
// alternates phase/wrap records, so a 1-record corpus routes 1 case to
// zz_01316e0_ and ZERO cases to FUN_80131688 — exactly the hole. Both functions
// sit below their declared min_cases: 1000 floors, so both must report
// fail_min_cases and the run must exit nonzero with a FAIL total.
//
// Run: node --test research/decomp/oracle-harness/tests/
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.resolve(here, "..");

test("a function routed 0 cases (or below min_cases) can never pass", () => {
  const scratch = fs.mkdtempSync(path.join(os.tmpdir(), "oracle-zero-case-"));
  const res = spawnSync(process.execPath, ["run-unit.mjs", "--unit", "auto-c0035-002", "--n", "1"], {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: scratch },
    encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  assert.notEqual(res.status, 0, `zero-case run must exit nonzero; log:\n${log}`);
  // FUN_80131688 received 0 cases — the exact hole the guard closes.
  assert.match(log, /\[FUN_80131688\] cases=0 .* verdict: fail_min_cases/, log);
  // zz_01316e0_ got 1 case, below its declared 1000 floor.
  assert.match(log, /\[zz_01316e0_\] cases=1 .* verdict: fail_min_cases/, log);
  assert.doesNotMatch(log, /VERDICT: PASS/, log);
  assert.doesNotMatch(log, /VERDICT: PARTIAL/, log);
  const result = JSON.parse(fs.readFileSync(path.join(scratch, "auto-c0035-002.json"), "utf8"));
  assert.equal(result.verdict, "fail");
  for (const f of result.functions) assert.equal(f.verdict, "fail_min_cases", f.name);
});
