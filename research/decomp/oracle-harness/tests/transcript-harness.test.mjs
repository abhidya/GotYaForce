// transcript-harness.test.mjs — transcript_green self-test WITHOUT Dolphin,
// mirroring spine-harness.test.mjs (the boundary_green self-test) exactly.
//
// Fixtures under tests/fixtures/transcript-synth/: a synthetic RETURNING
// function with NO MEMORY WRITES AT ALL (transcript_synth.c — three out-of-unit
// calls, one read of a cell a callee delta wrote, one return value), compiled
// with the pinned emsdk, plus four mutants and a hand-authored
// transcript_schema 1 capture of two independent cases.
//
// What this proves:
//   1. run-transcript.mjs reaches TRANSCRIPT_GREEN on the correct module;
//   2. the result artifact is UNMISTAKABLE for the other two standards —
//      standard:"transcript_green", its own filename namespace, and a
//      machine-readable claim block that names oracle_green as stronger;
//   3. INDUCED FAILURE, one mutant per divergence class the standard claims to
//      catch: wrong call order, wrong argument, wrong return value, extra call.
//      A verifier that cannot fail is worse than none. The wrong-RETURN mutant
//      is the one boundary_green structurally cannot catch — it is the reason
//      the return value joins the claim;
//   4. the NON-VACUITY GUARD: a capture of a function that observes nothing
//      FAILS rather than handing out a free green. Without this, a standard
//      aimed at write-free functions would be trivially green on the do-nothing
//      ones.
// Nothing here claims game equivalence; real Dolphin captures
// (capture_transcript.py) plug into the same schema.
//
// Run: node research/decomp/oracle-harness/tests/run-oracle-tests.mjs
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.resolve(here, "..");
const fixtures = path.join(here, "fixtures", "transcript-synth");
const capture = path.join(fixtures, "transcript-synth.capture.jsonl");
const vacuousCapture = path.join(fixtures, "transcript-synth-vacuous.capture.jsonl");

const runTranscript = (wasm, { capturePath = capture, unit = "transcript-synth",
  fn = "fn_nowrite", extra = [] } = {}) => {
  const scratch = fs.mkdtempSync(path.join(os.tmpdir(), "oracle-transcript-"));
  const argv = ["run-transcript.mjs", "--capture", capturePath, ...extra];
  if (wasm) argv.push("--wasm", path.join(fixtures, wasm));
  const res = spawnSync(process.execPath, argv, {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: scratch },
    encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  const resultPath = path.join(scratch, `${unit}.${fn}.transcript.json`);
  const result = fs.existsSync(resultPath) ? JSON.parse(fs.readFileSync(resultPath, "utf8")) : null;
  return { status: res.status, log, result, scratch };
};

test("transcript_green: the correct no-write function passes", () => {
  const { status, log, result } = runTranscript(null); // header default wasm
  assert.equal(status, 0, log);
  assert.match(log, /TRANSCRIPT TOTAL cases=2\/2 calls=6\/6 rets=2 DIVERGENCE: none VERDICT: TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.cases_passed, 2);
  assert.equal(result.calls_matched, 6);
  assert.equal(result.returns_checked, 2);
  assert.equal(result.divergence, null);
  // The fixture function writes nothing — the standard's whole reason to exist.
  assert.equal(result.owned_bytes, 0);
  assert.equal(result.wasm.memory_model, "exported");
});

test("transcript_green evidence is unmistakable for oracle_green or boundary_green", () => {
  const { log, result, scratch } = runTranscript(null);
  // 1. explicit standard field
  assert.equal(result.standard, "transcript_green");
  // 2. its own filename namespace — never <unit>.json, never <unit>.boundary.json
  const written = fs.readdirSync(scratch);
  assert.deepEqual(written, ["transcript-synth.fn_nowrite.transcript.json"]);
  assert.ok(!written.includes("transcript-synth.json"));
  assert.ok(!written.includes("transcript-synth.boundary.json"));
  // 3. the log can never be mistaken for either other harness's anchored total
  assert.doesNotMatch(log, /ORACLE TOTAL/, log);
  assert.doesNotMatch(log, /VERDICT: PASS/, log);
  assert.doesNotMatch(log, /BOUNDARY_GREEN/, log);
  // 4. the artifact states, machine-readably, that it is the weaker claim
  assert.equal(result.claim.weaker_than, "oracle_green");
  assert.match(result.claim.weaker_because, /never be recorded, counted or reported as oracle_green/);
  assert.ok(result.claim.does_not_verify.some((s) => /memory writes outside/.test(s)),
    "the artifact must say in so many words that writes are not compared");
  assert.deepEqual(result.claim.bounded_by_corpus, { cases: 2, calls: 6 });
});

test("transcript_green: call-order mutant fails naming the first divergent call", () => {
  const { status, log, result } = runTranscript("transcript_synth_badorder.wasm");
  assert.equal(status, 1, log);
  assert.match(log, /call divergence in case n=0 at i=1: expected stub_beta@0x80002100\(8, 100\), got stub_gamma\(100\)/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "callee");
  assert.equal(result.divergence.n, 0);
  assert.equal(result.divergence.i, 1);
});

test("transcript_green: wrong-argument mutant fails naming the argument", () => {
  const { status, log, result } = runTranscript("transcript_synth_badarg.wasm");
  assert.equal(status, 1, log);
  assert.match(log, /arg divergence in case n=0 at i=1 stub_beta@0x80002100: expected \(8, 100\), got \(7, 100\)/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "args");
});

test("transcript_green: wrong-RETURN mutant fails — the class boundary_green cannot catch", () => {
  const { status, log, result } = runTranscript("transcript_synth_badret.wasm");
  assert.equal(status, 1, log);
  // identical call transcript; only the returned value differs by one
  assert.match(log, /return divergence in case n=0: expected 105, got 106/, log);
  assert.doesNotMatch(log, /call divergence/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "ret");
  assert.equal(result.returns_checked, 0);
});

test("transcript_green: an EXTRA call fails — a returning capture is complete", () => {
  const { status, log, result } = runTranscript("transcript_synth_extracall.wasm");
  assert.equal(status, 1, log);
  assert.match(log, /extra call in case n=0 at i=3: capture ends after 3 calls, port called stub_alpha\(7\)/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "extra_call");
});

test("non-vacuity guard: a case that observes nothing can never pass", () => {
  const { status, log, result } = runTranscript(null,
    { capturePath: vacuousCapture, unit: "transcript-synth-vacuous", fn: "fn_vacuous" });
  assert.equal(status, 1, log);
  assert.match(log, /TRANSCRIPT VACUITY: 2 VACUOUS case\(s\)/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.deepEqual(result.vacuous_cases, [0, 1]);
  assert.equal(result.divergence, null, "vacuity is not a divergence — it is an empty claim");
});

test("non-vacuity guard: a corpus below the --min-cases floor can never pass", () => {
  const { status, log, result } = runTranscript(null, { extra: ["--min-cases", "5"] });
  assert.equal(status, 1, log);
  assert.match(log, /corpus has 2 cases, below the --min-cases floor of 5/, log);
  assert.doesNotMatch(log, /TRANSCRIPT_GREEN/, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence, null);
});

test("capture integrity: a header count that disagrees with the body is refused", () => {
  const scratch = fs.mkdtempSync(path.join(os.tmpdir(), "oracle-transcript-"));
  const lines = fs.readFileSync(capture, "utf8").split("\n").filter((l) => l);
  const header = JSON.parse(lines[0]);
  header.counts.call = 5; // the body has 6
  const tampered = path.join(scratch, "tampered.capture.jsonl");
  // the tampered capture must still resolve its wasm/arena, so copy them over
  for (const f of ["transcript_synth.wasm", "transcript-synth.arena.json"]) {
    fs.copyFileSync(path.join(fixtures, f), path.join(scratch, f));
  }
  fs.writeFileSync(tampered, [JSON.stringify(header), ...lines.slice(1)].join("\n") + "\n");
  const res = spawnSync(process.execPath, ["run-transcript.mjs", "--capture", tampered], {
    cwd: harnessDir, env: { ...process.env, ORACLE_RESULTS_DIR: scratch }, encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  assert.notEqual(res.status, 0, log);
  assert.match(log, /capture count mismatch: 6 call records != header counts\.call 5/, log);
});
