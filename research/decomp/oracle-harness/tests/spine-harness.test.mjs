// spine-harness.test.mjs — boundary_green self-test WITHOUT Dolphin (design v5
// I3 + step-8 subtask). Fixtures under tests/fixtures/spine-synth/: a synthetic
// nonterminating spine (spine_synth.c — do/while(true) calling 3 stubs, one
// spine-owned write) compiled with the pinned emsdk in an exported-memory
// build AND a threads-target build (imported SHARED env.memory), plus a
// hand-authored spine_schema 1 capture of K=2 iterations. Proves the harness
// SHAPE end-to-end:
//   1. run-spine.mjs reaches BOUNDARY_GREEN on the correct module — on BOTH
//      memory models, so the lib/wasm.mjs imported-shared-memory path is the
//      one under test, not a special case;
//   2. a call-order mutant fails naming the first divergent call (index,
//      expected vs actual callee/args);
//   3. a wrong-owned-write mutant fails naming the first divergent owned byte;
//   4. the threads fixture really declares an imported shared memory (a
//      non-shared host memory must be REJECTED at link) — the fixture cannot
//      silently decay into a plain exported-memory module.
// Real Dolphin captures plug into the same schema later; nothing here claims
// game equivalence.
//
// Run: node --test research/decomp/oracle-harness/tests/
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";
import { importedMemoryLimits } from "../lib/wasm.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.resolve(here, "..");
const fixtures = path.join(here, "fixtures", "spine-synth");
const capture = path.join(fixtures, "spine-synth.capture.jsonl");

const runSpine = (wasm) => {
  const scratch = fs.mkdtempSync(path.join(os.tmpdir(), "oracle-spine-"));
  const argv = ["run-spine.mjs", "--capture", capture];
  if (wasm) argv.push("--wasm", path.join(fixtures, wasm));
  const res = spawnSync(process.execPath, argv, {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: scratch },
    encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  const resultPath = path.join(scratch, "spine-synth.boundary.json");
  const result = fs.existsSync(resultPath) ? JSON.parse(fs.readFileSync(resultPath, "utf8")) : null;
  return { status: res.status, log, result };
};

test("boundary_green: correct spine passes on the exported-memory build", () => {
  const { status, log, result } = runSpine(null); // header default: spine_synth.wasm
  assert.equal(status, 0, log);
  assert.match(log, /SPINE TOTAL calls=6\/6 iterations=2 DIVERGENCE: none VERDICT: BOUNDARY_GREEN/, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.standard, "boundary_green"); // never mistakable for oracle_green
  assert.equal(result.wasm.memory_model, "exported");
  assert.equal(result.divergence, null);
});

test("boundary_green: correct spine passes on the threads build (imported shared memory)", () => {
  const { status, log, result } = runSpine("spine_synth.threads.wasm");
  assert.equal(status, 0, log);
  assert.match(log, /VERDICT: BOUNDARY_GREEN/, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.wasm.memory_model, "imported_shared");
});

test("threads fixture declares imported SHARED memory; non-shared host memory is rejected", () => {
  const bytes = fs.readFileSync(path.join(fixtures, "spine_synth.threads.wasm"));
  const lim = importedMemoryLimits(bytes);
  assert.ok(lim, "threads build must import env.memory");
  assert.equal(lim.shared, true);
  assert.equal(lim.initial, 256); // 16MB fixture arena
  const module = new WebAssembly.Module(bytes);
  const stubs = { stub_alpha: () => 0, stub_beta: () => {}, stub_gamma: () => 0 };
  assert.throws(() => new WebAssembly.Instance(module, {
    env: { memory: new WebAssembly.Memory({ initial: lim.initial, maximum: lim.maximum ?? lim.initial }), ...stubs },
  }), /shared/i, "a non-shared memory must fail the link check");
  // and the exported-memory fixture must NOT import memory — the detection is real
  assert.equal(importedMemoryLimits(fs.readFileSync(path.join(fixtures, "spine_synth.wasm"))), null);
});

test("boundary_green: call-order mutant fails naming the first divergent call", () => {
  const { status, log, result } = runSpine("spine_synth_badorder.wasm");
  assert.equal(status, 1, log);
  assert.match(log, /call divergence at i=1 \(iter 0\): expected stub_beta@0x1002\(10\), got stub_gamma\(10\)/, log);
  assert.doesNotMatch(log, /BOUNDARY_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.i, 1);
  assert.equal(result.divergence.kind, "callee");
});

test("boundary_green: wrong-owned-write mutant fails naming the first divergent byte", () => {
  const { status, log, result } = runSpine("spine_synth_badwrite.wasm");
  assert.equal(status, 1, log);
  assert.match(log, /owned-write divergence at call i=3: addr 0x104000 expected 0x01 got 0x02/, log);
  assert.doesNotMatch(log, /BOUNDARY_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.i, 3);
  assert.equal(result.divergence.kind, "owned_write");
});
